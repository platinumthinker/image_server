#include "desaturate.h"

#define R 0.2126
#define G 0.7152
#define B 0.0722

int Desaturate::process()
{
    unsigned char* pix = pixels;
    int i, count_pixel = bytes/channels;

    for (i = 0; i < count_pixel; i++, pix += channels)
    {
        unsigned char gray = (*pix) * R + (*pix + 1) * G + (*pix + 2) * B;
        *pix = gray;
        *(pix + 1) = gray;
        *(pix + 2) = gray;
    }

    return 0;
}

int Desaturate::process_gpu(CL_Helper *helper)
{
    return helper->kernel_proc(pixels, bytes, channels);
}
