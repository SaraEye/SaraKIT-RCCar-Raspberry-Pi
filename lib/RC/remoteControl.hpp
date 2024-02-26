#include <cstring>
#include <iostream>
#include <string>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include <sched.h>
#include "../viewer/viewer.hpp"

#define MAX_MSG_LEN 4096
#define SERWER_PORT 9001
#define INTERFACE "wlan0"
#define MAX_CONNECTION 50


//typ= 1 - gotopoint, 2 - button, 3 - led color, ...
struct PackRec{
    int mode;
    int X;
    int Y;
    int data;
    int r,g,b;
    bool boolean;
};

class RemoteControll{
public:
    RemoteControll();
    ~RemoteControll();
    void stop();    
    void getPos(int *px, int *py);
    int getButton();
    void getColorRGB(bool *is, cv::Scalar *nColorRGB);
    static void *connectionTask(void *context)
    {
        ((RemoteControll *)context)->run();
        return NULL;
    }
    cv::Mat hsv;
    cv::Scalar hsv_upper_l;
    cv::Scalar hsv_upper_h;
    cv::Scalar newColorRGB;
    bool isnewColorRGB;
    bool enableTrackingColor;
private:
    int init();
    void run();
    bool isStop;
    int lastmoveX;
    int lastmoveY;
    int moveX;
    int moveY;
    int lastButton;
    int socket_;
    socklen_t len;
    pthread_attr_t tattr;
    pthread_t tid;
    int newprio = 1; //1-low priority 99-high priority
    sched_param param;
    pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;
};