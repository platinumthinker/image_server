#include "desaturate.h"

int Desaturate::process()
{
    unsigned char* pix = pixels;
    int i, count_pixel = bytes/channels;

    for (i = 0; i < count_pixel; i++, pix += count_pixel)
    {
        unsigned char gray = (*pix + *(pix + 1) + *(pix + 2)) / 3;
        *pix = gray;
        *(pix + 1) = gray;
        *(pix + 2) = gray;
    }

    return 0;
}
