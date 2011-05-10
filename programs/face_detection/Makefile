# face_detection

CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES)
INCLUDES = -I/usr/local/include/opencv
LDFLAGS =
#LDLIBS = -lopencv_highgui
LDLIBS = -lhighgui -L/usr/X11/lib -lGL -lglut

TARGET = face_detection teapot_perspective

all : $(TARGET)

clean :
	$(RM) *.o $(TARGET)

depend :
	makedepend -Y -- $(INCLUDES) -- $(wildcard *.h *.cpp)
