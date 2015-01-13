#ifndef IOLOOP_H
#define IOLOOP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include "effect.h"

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
}

#endif
