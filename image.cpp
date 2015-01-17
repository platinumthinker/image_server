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

void Image::debug_print()
{
    int pixels_length = bytes / channels;
    std::cout << "Bytes: " << bytes<< "\n";
    std::cout << "Size: " << bytes / channels << "\n";
    std::cout << "Pixels:" << "\n";
    for (int i = 0; i < pixels_length; i++) {
        std::cout << int(pixels[i * 4    ]) << " " <<
                     int(pixels[i * 4 + 1]) << " " <<
                     int(pixels[i * 4 + 2]) << " " <<
                     int(pixels[i * 4 + 3]) << " " << "\n";
    }
}

Image::~Image()
{
    if (bytes > 0)
        delete[] pixels;
}
