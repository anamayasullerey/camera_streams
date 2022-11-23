CXX = g++
LDLIBS = \
    -lopencv_core \
    -lopencv_imgcodecs \
    -lopencv_highgui \
    -lopencv_imgproc
INCLUDES = \
    /usr/local/include/opencv4

CPPFLAGS = -g -I $(INCLUDES)

OBJS = \
    iTime.o \
    read-jpeg.o

all: a.out
a.out: ${OBJS}
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

%.o: %.c
	$(CXX) -c -o $@ $< $(CPPFLAGS)


.PHONY: clean
clean:
	rm *.o a.out
