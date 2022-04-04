#include <vector>
#include <limits>
#include <QWidget>
#include <QApplication>
#include "pipline.h"
#include "window.h"
#include <SDL2/SDL.h>
#include "QWidget"
#include "QKeyEvent"
#include "QDebug"
#include "QPainter"
using  namespace  std;
const int width  = 800;
const int height = 800;

Vec4f backgroundColor(1,1,1,1);
Vec3f light_dir(1,1,1);
Vec3f       eye(0,1,3);
Vec3f    Center(0,0,0);
Vec3f        up(0,1,0);



void compare()
{
    ifstream  ifstream1("data.txt");
    ifstream ifstream2("data1.txt");

    int r1,r2,g1,g2,b1,b2;
    int count=0;
    for(int i=0;i<800*800;i++){
        ifstream1>>r1>>g1>>b1;
        ifstream2>>r2>>g2>>b2;
        if(r1!=131 && g1!=122){
            int distance=(r2-r1)*(r2-r1)+(g2-g1)*(g2-g1)+(b2-b1)*(b2-b1);
            if(distance>50)
            {   count++;
                int x=i%800;
                int y=799-i/800;
            }
        }
        ifstream1>>r1;ifstream2>>r1;

    }
    std::cout<<count;
}

int main(int argc, char** argv) {
   // test();
//    compare();
//    return 0;
    TGAImage frame(width, height, TGAImage::RGB);
    Pipeline pipeline(width,height);

    //model view projection
    Matrix4f model_mat=Matrix4f::identity();
    Matrix4f view_mat=lookat(eye,Center,up);
    Matrix4f projection_mat=get_projection_matrix(60,1, -0.1, -10000);
    Camera camera(eye,Center,up);
    payload_t  payload;
    payload.model=model_mat;

    payload.view=view_mat;
    payload.projection=projection_mat;
    payload.camera=&camera;
    payload.mvp=projection_mat * view_mat;
    BaseShader *  shader;

    phongShader simpleShader;
    shader=&simpleShader;
    shader->payload=payload;

    auto data=getData();
    pipeline.setShader(shader);
//    windowApp=new Window();
//    windowApp->init(width,height,&camera,"tiny render",);
    QApplication application(argc,argv);
    windows window(width,height,&camera,&pipeline);
    window.show();
    return  QApplication::exec();
    while(true)
    {

      pipeline.clearBuffer();
      pipeline.draw();
//      camera.handleCameraEvent();
//      windowApp.updateSurface(pipeline.output());
        auto buffer=pipeline.output();
        change(buffer,data);
      windowApp->updateSurface(pipeline.output());
}}



