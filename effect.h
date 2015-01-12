#ifndef EFFECT_H
#define EFFECT_H

class Image
{
    public:
        unsigned char *pixels;
        unsigned int bytes, channels;
}

class Effect
{
    public:
        static virtual int process(Image*);
}

#endif //EFFECT_H
