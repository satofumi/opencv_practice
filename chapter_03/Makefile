# chapter_03

PREFIX = /usr/local

CXXFLAGS = -g -O0 -Wall -Werror $(INCLUDES)
INCLUDES = -I$(PREFIX)/include/opencv
LDFLAGS =
LDLIBS = -lhighgui


TARGET = \
	example_3-11 \
	example_3-12 \
	example_3-13 \
	example_3-14 \
	example_3-17 \
	example_3-19 \
	example_3-20 \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES) -- $(wildcard *.h *.c)

# DO NOT DELETE
