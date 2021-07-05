#ifndef IMAGE_READER_H
#define IMAGE_READER_H
#include <string>
struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

void readFromImage(std::string arg_img_path, Pixel arg_image[][1000], unsigned int& arg_x, unsigned int& arg_y);

#endif