#include <string>
#include <iostream>
#include "ioloop.h"

int main(int argc, const char *argv[])
{
    int port = 2000;
    if (argc == 2)
    {
        port = std::stoi(std::string(argv[1]));
    }

    IOLoop listener(port);
    listener.loop();
    return 0;
}
