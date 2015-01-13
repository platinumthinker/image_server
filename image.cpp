#include "image.h"

int Image::receive(int fd)
{
    recv(fd, &(this->bytes), sizeof(int), 0);
    if (this->bytes == 0)
    {
        return 1;
    }

    this->pixels = new unsigned int[this->bytes];

    return this->bytes != recv(fd, this->pixels, this->bytes, 0);
}

void Image::send(int fd)
{
    send(fd, &(this->bytes), sizeof(int), 0);
    send(fd, this->pixels, this->bytes, 0);
}
