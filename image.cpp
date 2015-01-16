#include "image.h"

int Image::receive(int fd)
{
    recv(fd, &(this->bytes), sizeof(int), MSG_WAITALL);
    if (this->bytes == 0)
    {
        return 1;
    }

    this->pixels = new unsigned char[this->bytes];

    return this->bytes != recv(fd, this->pixels, this->bytes, MSG_WAITALL);
}

void Image::send_im(int fd)
{
    send(fd, &(this->bytes), sizeof(int), 0);
    send(fd, this->pixels, this->bytes, 0);
}

Image::~Image()
{
    if (bytes > 0)
        delete[] pixels;
}
