.PHONY: all clean
CFLAGS := -std=c++11 -Wall -g -lm -lOpenCL

SRC := desaturate.cpp image.cpp ioloop.cpp main.cpp cl_helper.cpp

all: image_server

image_server: $(SRC)
	g++ $(CFLAGS) $(INCLUDE) -o image_server $(SRC)

clean:
	-rm image_server
