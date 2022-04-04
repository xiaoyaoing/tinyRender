//
// Created by 打工人 on 2022/3/19.
//

#include "shader.h"
void BaseShader::updateViewMatrix() {
    this->payload.view=lookat(this->payload.camera->eye,this->payload.camera->center,this->payload.camera->up);
}

VertexOut textureShader::vertexShader(const Vertex &in) {


    VertexOut result;
    result.posTrans = payload.model* in.position;
    result.posH = payload.projection * payload.view*  result.posTrans;
    HomogeneousDiv(result.posH);
    result.color = in.color;
    result.normal = in.normal;
    result.divZ = 1.0;
    result.texcoord = in.texcoord;
    return result;
}

Vec4f textureShader::fragmentShader(const VertexOut &in) {

    if(this->texture!= nullptr){
        return embed<4,3,float>(texture->getColor(in.texcoord.x,in.texcoord.y),0);
    }
    return in.color;
}

Vec4f phongShader::fragmentShader(const VertexOut &in) {
    Vec3f ambient;
    Vec3f diffuse;
    Vec3f sepcular;

    Vec3f  ka(0.35,0.35,0.35);
    Vec3f  kd=texture->getColor(in.texcoord[0],in.texcoord[1]);
    Vec3f  ks=Vec3f(0.8,0.8,0.8);
    int p=150;

    Vec3f lightPos={0,2,2};

    Vec3f lightPower={1,1,1};

    Vec3f  normal=  in.normal; //法线
    Vec3f  pos= proj<3> (in.posTrans) ; //世界坐标
    double  r=(lightPos-pos).norm();
    Vec3f  eyeDir=(payload.camera->eye-pos).normalize(); //观察角度
    Vec3f  lightDir=(lightPos-pos).normalize();
//    lightDir=Vec3f(1,1,1).normalize();
    Vec3f light_diffuse_intensity = Vec3f(0.9, 0.9, 0.9);
    Vec3f light_specular_intensity = Vec3f(0.15, 0.15, 0.15);


    ambient=cwiseProduct(ka,kd);
    diffuse= cwiseProduct(light_diffuse_intensity , kd)* std::max(0.f,dot(normal,lightDir)) ;
    Vec3f half=(eyeDir+lightDir).normalize();
    auto temp=pow(dot(normal,half),150);
    sepcular=cwiseProduct(light_specular_intensity   ,ks )* pow(std::max(0.f,dot(normal,half)),p) ;
    auto resColor=  embed<4>( ambient+diffuse+sepcular);

    if(resColor.x>1) resColor.x=1;
    if(resColor.y>1) resColor.y=1;
    if(resColor.z>1) resColor.z=1;
    return resColor;
//    Vec3f
}

VertexOut  phongShader::vertexShader(const Vertex &in) {
//    payload.normal=in.normal;
//    payload.uv=in.texcoord;
//    payload.worldCoord=payload.mvp * in.position;
    VertexOut result;
//    return result;
    result.posTrans =in.position;
    result.posH = payload.mvp *  result.posTrans;
    HomogeneousDiv(result.posTrans);
    HomogeneousDiv(result.posH);
    result.normal=  (proj<3> ((payload.view*payload.model).invert_transpose() * embed<4,3,float>( in.normal,0))).normalize();
//    result.normal=in.normal;
    result.divZ=1;
    result.texcoord=in.texcoord;
    return result;
}





