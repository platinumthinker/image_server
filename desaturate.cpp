#include "desaturate.h"

static int Desaturate:process(Image* image)
{
    unsigned char* pixels = image->pixels;
    int i, count_pixel = image->bytes/channels;

    for (i = 0; i < count_pixel; i++, pixels += count_pixel)
    {
        unsigned char gray = (*pixels + *(pixels + 1) + *(pixels + 2)) / 3;
        *pixels       = gray;
        *(pixels + 1) = gray;
        *(pixels + 2) = gray;
    }

    return 0;
}
