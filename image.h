#ifndef IMAGE_H
#define IMAGE_H

class Image
{
    private:
        unsigned char *pixels;
        unsigned int bytes, channels;
    public:
        int receive(int fd);
        void send(int fd);
        static virtual int process(Image*);
}

#endif //IMAGE_H
