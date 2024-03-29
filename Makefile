SHELL = /bin/sh


OBJDIR := .obj
DEPDIR := .dep
SRCDIR := 

CPP_SOURCES = 	RCCar.cpp \
	struct.cpp \
	lib/camera/RaspiCamControl.cpp \
	lib/camera/RaspiCLI.cpp \
	lib/camera/RaspiCamCV.cpp \
	lib/MJPEGWriter/MJPEGWriter.cpp \
	lib/viewer/viewer.cpp \
	lib/SaraKIT/devices.cpp \
	lib/RC/remoteControl.cpp
	
C_SOURCES =	lib/camera/RaspiHelpers.c \
	lib/camera/RaspiPreview.c \
	lib/camera/RaspiCommonSettings.c \

CFLAGS = -Wl,--no-as-needed -fexceptions -fpermissive -pthread -O3 -mcpu=cortex-a72 -mtune=cortex-a72 -Wno-psabi 

CC = g++
INCLUDES = -I/opt/vc/include \
	-I/opt/vc/include/interface/mmal \
	-I/opt/vc/include/interface/vcos/pthreads \
	-I/opt/vc/include/interface/vmcs_host/linux \
	-I/usr/local/include/opencv4 \
	-I./lib

LIBS =-lpthread \
	-L/opt/vc/lib \
	-lopencv_core \
 	-lopencv_highgui \
 	-lopencv_imgproc \
	-lopencv_imgcodecs \
	-lopencv_videoio \
	-lbcm_host \
	-lmmal \
	-lmmal_core \
	-lmmal_components \
	-lmmal_util \
	-lmmal_vc_client \
	-lvcos \
	-lcrypt

SLIBS=

DEPFLAGS = -MT $@ -MMD -MP -MF  $(DEPDIR)/$*.d 

SOURCES=$(CPP_SOURCES) $(C_SOURCES)
OBJECTS=$(CPP_SOURCES:.cpp=.o) $(C_SOURCES:.c=.o)

mkdirs = $(shell mkdir -p   $(DEPDIR)/$(dir $(path)) $(OBJDIR)/$(dir $(path)))
$(foreach path,$(SOURCES),$(mkdirs))

POBJECTS= $(addprefix $(OBJDIR)/, $(OBJECTS))

PRG=RCCar

all: $(PRG)
$(PRG):$(POBJECTS)
	$(CC)  -Wl,--no-as-needed -o $@ $(POBJECTS) $(LIBS)  $(SLIBS)
$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(CC)  $(DEPFLAGS) $(CFLAGS) $(INCLUDES) -c -o $@ $< 
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d 
	$(CC)  $(DEPFLAGS) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

DEPFILES =  $(C_SOURCES:%.c=%.d)
DEPFILES +=  $(CPP_SOURCES:%.cpp=%.d)
PDEPFILES= $(addprefix $(DEPDIR)/, $(DEPFILES))
$(PDEPFILES):
include $(wildcard $(PDEPFILES))

clean:
	-rm -f $(POBJECTS) $(PDEPFILES) $(PRG) $(OBJDIR)/*.o $(DEPDIR)/*.d