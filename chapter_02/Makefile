# chapter_02

PREFIX = /usr/local

CXXFLAGS = -g -O0 -Wall -Werror $(INCLUDES)
INCLUDES = -I$(PREFIX)/include/opencv
LDFLAGS =
LDLIBS = -lhighgui


TARGET = \
	example_2-1 \
	example_2-2 \
	example_2-3 \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o
