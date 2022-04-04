//
// Created by 打工人 on 2022/3/19.
//

#ifndef TINYRENDER_PIPLINE_H
#define TINYRENDER_PIPLINE_H

#include "shader/shader.h"
#include "headers/frameBuffer.h"
#include "model.h"

class Pipeline{
private:
    int width,height;
    BaseShader * shader;
    frameBuffer * frontBuffer;
    frameBuffer * backBuffer;
    Matrix4f viewMatrix;
    bool MSAA ;//抗锯齿
    float * MSAAx;
    float * MSAAy;
    int k=0;
//    std::vector<Vertex>  m_vertices;     // vertex buffer.
//    std::vector<unsigned int> m_indices; // indices buffer;
    std::vector<Model> models;
    std:: vector<bool>vis ;
public:

    Pipeline(int width,int height);
    void setViewPort(int screen_width,int screen_height);
    void draw();
    void setVertexBuffer(std::vector<Vertex> & buffer);
    void setIndicesBuffer(std::vector<unsigned int> & buffer);
    void swapBuffer();
    void drawLine(VertexOut &v1, VertexOut &v2);
    void fill(Vec4f color);
    void generateImage(const char string[6]);
    void drawTriangle(Triangle &triangle);
    void setShader(BaseShader * shader);
    void perspectiveDivision(VertexOut &target);

    unsigned char *output();

    void clearBuffer();
};
#endif //TINYRENDER_PIPLINE_H
