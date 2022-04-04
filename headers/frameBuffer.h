//
// Created by 打工人 on 2022/3/20.
//

#ifndef TINYRENDER_FRAMEBUFFER_H
#define TINYRENDER_FRAMEBUFFER_H
#include "../geometry.h"
#include "../tgaimage.h"
class frameBuffer{
    unsigned  char * color_buffer;
    double  * depth_buffer;
    int channel;
    int height;
    int width;
public:
    frameBuffer(int width,int height) :height(height),width(width),channel(4){
        color_buffer=new unsigned  char [height*width*channel];
        depth_buffer=new double [height*width];
        memset(depth_buffer,MAXFLOAT,sizeof(float)*height*width);
    }
    int getHeight(){
        return height;
    }
    int getWidth(){
        return width;
    }
    void setColor(int x,int y,Vec4f & color);
    void fill(Vec4f & color);
    void generateImage(const char *string);
    double getDepth(int x,int y);
    void setDepth(int x,int y,double  depth);
    unsigned  char * getOutput();

    void clearDepthBuffer();
};


#endif //TINYRENDER_FRAMEBUFFER_H
