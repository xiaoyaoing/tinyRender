//
// Created by 打工人 on 2022/3/25.
//
#include "camera.h"
#include "window.h"

void handleKeyEvent(Camera & camera){

}
 void handleMouseEvent(Camera & camera){
    const unsigned char* keyMap = SDL_GetKeyboardState(NULL);
    float distance=(camera.center-camera.eye).norm();
    if(keyMap[SDL_SCANCODE_W]){
        {std::cout<<"s"; camera.eye=camera.eye+camera.z*(-0.1*distance);}

    }
    if(keyMap[SDL_SCANCODE_S]){
        { std::cout<<"w"; camera.eye=camera.eye+camera.z*0.1;}
    }
    if(keyMap[SDL_SCANCODE_SPACE])
    { windowApp->setClose(true);}
}

void Camera::handleCameraEvent() {
//     std::cout<<eye.x<<" "<<eye.y<<" "<<eye.z<<" ";
     z=(eye-center).normalize();
     x=cross(up,z).normalize();
     y=cross(z,x).normalize();

     while(SDL_PollEvent(&windowApp->events)){
     handleKeyEvent(*this);
     handleMouseEvent(*this);
     }
}

Camera::Camera(Vec3f eye, Vec3f center, Vec3f up) {
    this->eye=eye;
    this->center=center;
    this->up=up;
}

Camera::~Camera() {

}

void Camera::update(){
    z=(eye-center).normalize();
    x=cross(up,z).normalize();
    y=cross(z,x).normalize();
}

void Camera::handleForward() {
    float distance=(center-eye).norm();
    eye=eye+z*(-0.1*distance);
    std::cout<<"forward\n";
}

void Camera::handeBack() {
    float distance=(center-eye).norm();
    eye=eye+z*0.1*distance;
    std::cout<<"behind\n";
}

