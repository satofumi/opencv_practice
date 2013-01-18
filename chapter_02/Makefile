# chapter_02

CXXFLAGS = -g -O0 -Wall -Werror $(INCLUDES)
INCLUDES = -I/usr/include/opencv
LDFLAGS =
LDLIBS = -lopencv_highgui -lopencv_imgproc -lopencv_core


TARGET = \
	example_2-1 \
	example_2-2 \
	example_2-3 \
	example_2-4 \
	example_2-5 \
	example_2-6 \
	example_2-9 \
	example_2-10 \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES) -- $(wildcard *.h *.c)

# DO NOT DELETE
