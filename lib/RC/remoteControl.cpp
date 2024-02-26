#ifndef _RC_H_
#define _RC_H_

#include "remoteControl.hpp"


RemoteControll::RemoteControll()
{
    isStop=false;
    enableTrackingColor=false;
    lastButton=-1;
    isnewColorRGB=false;
    init();
    hsv_upper_l=cv::Scalar(255, 255, 255);
    hsv_upper_h=cv::Scalar(0, 0, 0);

    pthread_attr_init(&tattr);
    pthread_attr_getschedparam(&tattr, &param);
    param.sched_priority = newprio;
    pthread_attr_setschedparam(&tattr, &param);
    pthread_create(&tid, &tattr, &RemoteControll::connectionTask, (RemoteControll *)this);
}

RemoteControll::~RemoteControll() {
    stop();
}

void RemoteControll::stop(){
    isStop=true;
    shutdown(socket_,SHUT_RDWR);
    close(socket_);
}

void RemoteControll::getPos(int *px, int *py){
    *px=moveX;
    *py=moveY;
}

int RemoteControll::getButton(){
    int btn=lastButton;
    lastButton=-1;
    return btn;
}

void RemoteControll::getColorRGB(bool *is, cv::Scalar *nColorRGB){
    *is=isnewColorRGB;
    *nColorRGB=newColorRGB;
    isnewColorRGB=false;
}

int RemoteControll::init()
{
    struct sockaddr_in serwer =
    {
        .sin_family = AF_INET,
        .sin_port = htons(SERWER_PORT)
    };

    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1) 
    {
        perror("getifaddrs");
        return -1;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
    {
        if (ifa->ifa_addr == NULL)
            continue;  

        s=getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
        if((strcmp(ifa->ifa_name,INTERFACE)==0)&&(ifa->ifa_addr->sa_family==AF_INET))
        {
            if (s != 0)
            {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                return -1;
            }
            serwer.sin_addr=((struct sockaddr_in *)(ifa->ifa_addr))->sin_addr;
            // printf("\tInterface : <%s>\n",ifa->ifa_name );
            // printf("\t  Address : <%s>\n", host); 
        }
    }

    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        return 2;
    }
    int option = 1; 
    setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    len = sizeof(serwer);
    if (bind(socket_, (struct sockaddr *)&serwer, len) < 0)
    {
        perror("bind() ERROR");
        return 3;
    }

    if (listen(socket_, MAX_CONNECTION) < 0)
    {
        perror("listen() ERROR");
        return 4;
    }
    return 0;
}

void RemoteControll::run()
{
    PackRec prec;
    while (!isStop)
    {
        printf("Waiting for connection...\n");

        struct sockaddr_in client = {};

        const int clientSocket = accept(socket_, (struct sockaddr *)&client, &len);
        if (clientSocket < 0)
        {
            shutdown(socket_,SHUT_RDWR);
            close(socket_);
            init();
            perror("accept1() ERROR");
            continue;
        }
        while (!isStop)
        {
            char buffer[MAX_MSG_LEN] = {};

            if (recv(clientSocket,  (char *)&prec, sizeof(PackRec), 0) <= 0)
            {
                perror("recv() ERROR");
                break;
            }

            if(prec.mode==1){
                moveX=prec.X;
                moveY=prec.Y;
            }

            if(prec.mode==2){
                lastButton=prec.data;
            }

            if(prec.mode==3){
                newColorRGB[0]=prec.r;
                newColorRGB[1]=prec.g;
                newColorRGB[2]=prec.b;
                isnewColorRGB=true;
            }

            if(prec.mode==4){
                enableTrackingColor=true;
            }

            if(prec.mode==5){
                //pos middle mouse
                enableTrackingColor=false;
                cv::GaussianBlur(frame0,frame0,cv::Size(9,9),0.5);
                cv::cvtColor(frame0, hsv, cv::COLOR_BGR2HSV);
                cout<<hsv.at<cv::Vec3b>(320,240)<<endl;
                cv::Vec3b color=hsv.at<cv::Vec3b>(prec.Y*2,prec.X*2);
                if(hsv_upper_l[0]>color[0])
                    hsv_upper_l[0]=color[0];
                if(hsv_upper_l[1]>color[1])
                    hsv_upper_l[1]=color[1];
                if(hsv_upper_l[2]>color[2])
                    hsv_upper_l[2]=color[2];     
                if(hsv_upper_h[0]<color[0])
                    hsv_upper_h[0]=color[0];
                if(hsv_upper_h[1]<color[1])
                    hsv_upper_h[1]=color[1];
                if(hsv_upper_h[2]<color[2])
                    hsv_upper_h[2]=color[2];     
                std::cout<<"["<<(int)color[0]<<", "<<(int)color[1]<<", "<<(int)color[2]<<"] "<<hsv_upper_l<<" "<<hsv_upper_h<<std::endl;
            }

            strcpy(buffer, "Message from server:OK");
            if (send(clientSocket, buffer, strlen(buffer), 0) <= 0)
            {
                perror("send() ERROR");
                break;
            }
        }
        shutdown(clientSocket, SHUT_RDWR);
    }

    shutdown(socket_, SHUT_RDWR);
}

#endif  // _RC_H_