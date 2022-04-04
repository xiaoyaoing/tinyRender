//
// Created by 打工人 on 2022/3/20.
//
#include "../headers/frameBuffer.h"


void frameBuffer::setColor(int x, int y, Vec4f & color) {

    int index=((height-y-1)*width+x)*4;
    color_buffer[index]=color[0]*255.f;
    color_buffer[index+1]=color[1]*255.f;
    if(color_buffer[index]==190 && color_buffer[index+1]==190)
        int k=1;
    color_buffer[index+2]=color[2]*255.f;
    color_buffer[index+3]=255;
}

void frameBuffer::fill(Vec4f & color) {

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            int index=(i*width+j)*4;
            color_buffer[index]=color[0];
            color_buffer[index+1]=color[1];
            color_buffer[index+2]=color[2];
            color_buffer[index+3]=255;
        }
}



void frameBuffer::generateImage(const char * name) {
    TGAImage frame(width, height, TGAImage::RGBA);
    frame.setbuffer(this->color_buffer);
    frame.write_tga_file(name);
}
double frameBuffer::getDepth(int x, int y) {
    return depth_buffer[y*width+x];
}

void frameBuffer::setDepth(int x, int y, double depth) {
    depth_buffer[y*width+x]=depth;
}

unsigned  char * frameBuffer::getOutput() {
    return color_buffer;
}

void frameBuffer::clearDepthBuffer() {
    for(int i=0;i<height*width;i++)
        depth_buffer[i]=-10000;
}



