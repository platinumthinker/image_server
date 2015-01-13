#include "ioloop.h"

int IOLoop::start_listen()
{
    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(listen_port);

    if(bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)))
    {
        perror("bind");
        exit(2);
    }

    listen(listen_fd, MAX_CLIENT);
    std::cout << "Start listen on " << LISTEN_PORT << " port\n";

    return listen_fd;
}

void IOLoop::loop()
{
    int fd, listen_fd;
    listen_fd = listen_port();

    for ever
    {
        fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
        std::thread th([fd]()
            {
                Image im;
                if( im.receive(fd) )
                {
                    std::cout << "Don't receive image from " << fd << "\n";
                    return 0;
                }
                std::cout << "Receive image from " << fd << "\n";

                im.send(fd);
                std::cout << "Send image in " << fd << "\n";
            }
    }
}
