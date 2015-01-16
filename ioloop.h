#ifndef IOLOOP_H
#define IOLOOP_H

#include <iostream>
#include <string>
#include "image.h"
#include "desaturate.h"

#define MAX_CLIENT 10
#define ever (;;)

class IOLoop
{
    public:
        IOLoop(int port) : listen_port(port){}
        void loop();
    private:
        int listen_port;
        int start_listen();
};

#endif
