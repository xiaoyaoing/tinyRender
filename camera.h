//
// Created by 打工人 on 2022/3/25.
//

#ifndef TINYRENDER_CAMERA_H
#define TINYRENDER_CAMERA_H

#include "geometry.h"
#include <SDL2//SDL.h>
class Camera{
public:
    Camera(Vec3f e, Vec3f t, Vec3f up);
    ~Camera();
    void handleCameraEvent();
    Vec3f eye;
    Vec3f center;
    Vec3f up;
    Vec3f x;
    Vec3f y;
    Vec3f z;

    void handleForward();

    void handeBack();

    void update();
};

#endif //TINYRENDER_CAMERA_H
