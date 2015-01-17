#ifndef DESATURATE_H
#define DESATURATE_H

#include "image.h"

class Desaturate : public Image
{
    public:
        int process();
        int process_gpu(CL_Helper *helper);
};

#endif // DESATURATE_H
