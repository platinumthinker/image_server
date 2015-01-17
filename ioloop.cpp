#include "ioloop.h"
#include <cstring>

int IOLoop::start_listen()
{
    struct sockaddr_in servaddr;

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(listen_port);

    int optval = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    if(bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)))
    {
        perror("bind");
        exit(2);
    }

    listen(listen_fd, MAX_CLIENT);
    std::cout << "Start listen on " << listen_port << " port\n";

    return listen_fd;
}

void IOLoop::loop()
{
    int fd, listen_fd;
    listen_fd = start_listen();

    CL_Helper helper;
    helper.init();
    helper.buildProgramFromFile("cl/desaturate.cl");

    for ever
    {
        fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
        Image *im = new Desaturate();
        if( im->receive(fd) )
        {
            std::cout << "Don't receive image from " << fd << "\n";
            continue;
        }
        std::cout << "Receive image from " << fd << "\n";
        im->debug_print();
        /* im->process(); */
        if ( im->process_gpu(&helper) )
        {
            std::cout << "Don't process image!" << "\n";
            continue;
        }

        std::cout << "Process image from " << fd << "\n";
        im->debug_print();
        im->send_im(fd);
        std::cout << "Send image in " << fd << "\n";
        delete im;
    }
}
