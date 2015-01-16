.PHONY: all clean
CFLAGS := -std=c++11 -Wall -g -lm

SRC := desaturate.cpp image.cpp ioloop.cpp main.cpp

all: image_server

image_server: $(SRC)
	g++ $(CFLAGS) -o image_server $(SRC)

clean:
	-rm image_server
