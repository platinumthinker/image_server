#ifndef IMAGE_H
#define IMAGE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Image
{
    protected:
        unsigned char *pixels;
        unsigned int bytes, channels = 4;
    public:
        int receive(int fd);
        void send_im(int fd);
        virtual int process() = 0;
        virtual ~Image();
};

#endif //IMAGE_H
