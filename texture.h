//
// Created by 打工人 on 2022/3/22.
//

#ifndef TINYRENDER_TEXURE_H
#define TINYRENDER_TEXURE_H

#include "geometry.h"
#include "tgaimage.h"
//纹理类
class Texture{
public:
    Texture(const char * fileName){
        this->image=new TGAImage ;
        image->read_tga_file(fileName);
        height=image->get_height();
        width=image->get_width();
    }
    int width;
    int height;
    TGAImage * image;
    Vec3f  getColor(double  u,double  v){
//        assert(u<=1);
//        assert(v<=1);
        u=fmod(u,1);
        v=fmod(v,1);
        TGAColor color=image->get(u*width,v*height);
        return Vec3f(color[2]/255.0,color[1]/255.0,color[0]/255.0) ;
    }
};


#endif //TINYRENDER_TEXURE_H
