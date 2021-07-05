#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "ImageReader/ImageReader.h" 


int main() {

    Pixel img[1000][1000];
    unsigned int size_x = 0;
    unsigned int size_y = 0;
    readFromImage("./ImageReader/image.ppm", img, size_x, size_y);
    for(int i=0; i<size_x; i++)
    {
        for(int j=0; j<size_y; j++)
        {
            // std::cout << img[i][j].r << " ";
            // std::cout << static_cast<unsigned char>(img[i][j].g) << " ";
            // std::cout << static_cast<unsigned char>(img[i][j].b) << " ";
        }
        break;    
    }
 
    return EXIT_SUCCESS;
}