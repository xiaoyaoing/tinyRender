//
// Created by 打工人 on 2022/3/20.
//

#ifndef TINYRENDER_VERTEX_H
#define TINYRENDER_VERTEX_H
#include "geometry.h"
class Vertex{
    //顶点类 顶点坐标 颜色 纹理坐标 法线
public:
    Vec4f  position;
    Vec4f  color;
    Vec2f  texcoord;
    Vec3f  normal;

    Vertex(const Vec4f &position, const Vec4f &color, const Vec2f &texcoord, const Vec3f &normal)
    : position(position),color(color),texcoord(texcoord),normal(normal) {}
    Vertex(){}
    Vertex(const Vec4f & position,const Vec4f & color):position(position),color(color){

    }

};
class VertexOut{
public:
    Vec4f  posTrans; //世界变换后坐标
    Vec4f  posH; //投影变换后
    Vec4f  color;
    Vec2f  texcoord;
    Vec3f  normal;
    double  divZ;
  VertexOut  operator *(double  val){
      VertexOut r;
      r.posTrans=posTrans*val;
      r.posH=posH*val;
      r.color=color*val;
      r.texcoord=texcoord*val;
      r.normal=normal*val;
      return r;
  }

  VertexOut operator +(VertexOut another){
      VertexOut r;
      r.posTrans=another.posTrans+posTrans;
      r.posH=another.posH+posH;
      r.color=another.color+color;
      r.texcoord=another.texcoord+texcoord;
      r.normal=another.normal+normal;
      return  r;
  }



};

class Triangle{
public:
    VertexOut * v1,*v2,*v3;
    bool  insideTriangle(double  x,double  y);
    Triangle(VertexOut * v1,VertexOut * v2,VertexOut * v3):v1(v1),v2(v2),v3(v3){
    }
};

#endif //TINYRENDER_VERTEX_H
