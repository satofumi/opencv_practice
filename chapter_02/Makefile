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
	example_2-4 \
	example_2-5 \
	example_2-6 \
	example_2-9 \
	example_2-10 \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o
