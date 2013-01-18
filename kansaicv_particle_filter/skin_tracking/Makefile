CC = $(CXX)
CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES)
INCLUDES = -I/usr/include/opencv
LDFLAGS =
LDLIBS = -lopencv_highgui -lopencv_legacy -lopencv_core


TARGET = skin_tracking

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

.PHONY : all clean
