#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "ImageReader.h"
 
unsigned int readUntilSpace(char buffer[], unsigned int start, std::vector<char>& output)
{
    using namespace std;

    unsigned int i = start;
    unsigned int counter = 0;
    while(buffer[i] != 32 && buffer[i] != 10)
    {
        output.push_back(buffer[i++]);
    }

    return i;
}

void computeImageSize(char buffer[], unsigned int& arg_x, unsigned int& arg_y)
{
    using namespace std;
    const unsigned int SIZE_SECTION = 3;

    std::vector<char> temp;
    unsigned int lastPosRead = readUntilSpace(buffer, SIZE_SECTION, temp);
    // cout << std::stoi(string(temp.begin(), temp.end())) << std::endl;
    arg_x = std::stoi(string(temp.begin(), temp.end()));

    temp.clear();
    cout << "LastPosRead : " << lastPosRead << endl;
    readUntilSpace(buffer, lastPosRead+1, temp);
    // cout << std::stoi(string(temp.begin(), temp.end())) << std::endl;
    arg_y = std::stoi(string(temp.begin(), temp.end()));
}

unsigned int readDataOffsetFromImage(char buffer[])
{
    unsigned int i = 0;
    unsigned int counter = 0;
    const unsigned int START_DATA_SECTION = 4;
    while(counter < START_DATA_SECTION)
    {
        
        if(buffer[i] != 10 && buffer[i] != 32)
            i++;
        else
        {
            i++;
            counter++;
        }
    }

    return i;
}

void readFromImage(std::string arg_img_path, Pixel arg_image[][1000], unsigned int& arg_x, unsigned int& arg_y)
{
    using namespace std;
    const unsigned int n = 150;
    const unsigned int SIZE_SECTION = 3;
    char buffer[n];
    ifstream istream(arg_img_path, ios_base::in | ios_base::binary);
    istream.read(buffer, n);
    // istream.close();

    unsigned int size_x;
    unsigned int size_y;
    computeImageSize(buffer, size_x, size_y);
    unsigned int startOfData = readDataOffsetFromImage(buffer);    
    cout << "StartOfData = " << startOfData << endl;

    istream.seekg(startOfData, ios_base::beg);
    vector<unsigned char> data(
        (istreambuf_iterator<char>(istream)),
        (istreambuf_iterator<char>())
    );
    cout << data.size() << endl;

    for(int i=0; i<size_x-799; i++)
        for(int j=0; j<size_y-750; j++)
        {
            arg_image[i][j].r = static_cast<unsigned char>(data[(i*size_x)+(j*3)]);
            arg_image[i][j].g = static_cast<unsigned char>(data[(i*size_x)+(j*3)+1]);
            arg_image[i][j].b = static_cast<unsigned char>(data[(i*size_x)+(j*3)+2]);
            cout << (int)arg_image[i][j].r << " , " << (int)arg_image[i][j].g << " , " << (int)arg_image[i][j].b << endl;
        }

    arg_x = size_x;
    arg_y = size_y;
}
