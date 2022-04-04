//
// Created by 打工人 on 2022/3/19.
//

#ifndef TINYRENDER_SHADER_H
#define TINYRENDER_SHADER_H

#include "../geometry.h"
#include "../vertex.h"
#include "../texture.h"
#include "../camera.h"

typedef  struct {
    Matrix4f  model;
    Matrix4f  view;
    Matrix4f  projection;
    Camera * camera;
    Matrix4f  mvp;

    Vec2f uv;
    Vec3f normal;


    Vec4f worldCoord;
} payload_t;
class BaseShader
{
public:
    payload_t  payload;
    virtual ~BaseShader() = default;
    virtual VertexOut vertexShader(const Vertex &in) = 0;
    virtual Vec4f fragmentShader(const VertexOut & in) = 0;
    virtual void updateViewMatrix();
//    virtual void setModelMatrix(const Matrix4f &world) = 0;
//    virtual void setViewMatrix(const Matrix4f &view) = 0;
//    virtual void setProjectMatrix(const Matrix4f &project) = 0;

    Texture * texture= nullptr;
};

class textureShader : public BaseShader{
private:
//    Matrix4f m_modelMatrix;
//    Matrix4f m_viewMatrix;
//    Matrix4f m_projectMatrix;
public:

//    simpleShader()=default;
    virtual VertexOut vertexShader(const Vertex &in) ;
    virtual Vec4f fragmentShader(const VertexOut &in) ;
//    virtual void setModelMatrix(const Matrix4f &world) ;
//    virtual void setViewMatrix(const Matrix4f &view) ;
//    virtual void setProjectMatrix(const Matrix4f &project) ;
};

class phongShader: public BaseShader{
    virtual VertexOut vertexShader(const Vertex &in) ;
    virtual Vec4f fragmentShader(const VertexOut &in) ;
};




#endif //TINYRENDER_SHADER_H
