//
// Created by 打工人 on 2022/3/25.
//

#ifndef TINYRENDER_WINDOW_H
#define TINYRENDER_WINDOW_H
#include "SDL2/SDL.h"
#include "string"
#include "camera.h"
#include <iostream>
#include <QWidget>
#include "QKeyEvent"
#include "QDebug"
#include "QPainter"
#include "renderThread.h"
#include <QTimer>
class Window{

    SDL_Window* windowHandle = nullptr;
    SDL_Surface* screenSurface = nullptr;
    SDL_Renderer * renderer;

    int width;
    int height;
    std::string title;
public:

    void processEvent();

    void updateSurface(unsigned  char * buffer);

    bool init(int width,int height,Camera * camera,const char *);

    bool isClose();
    void setClose(bool c);
    bool close=false;
    SDL_Event  events;
};

extern Window * windowApp;

class windows : public QWidget{
    Q_OBJECT;
    QImage * image;
    int height;
    int width;
    QThread * loopThread;
    renderThread * loop;
    Camera * camera ;
    QTimer * timer;
    int fpsCount=0;
    void keyPressEvent(QKeyEvent * ev) override{

        if(ev->key()==Qt::Key_W){
            camera->handleForward();
        }
        else if(ev->key()==Qt::Key_S)
            camera->handeBack();
        camera->update();
    };
public:
    windows(int width,int height,Camera * camera,Pipeline * pipeline):width(width),height(height){
        this->camera=camera;
        this->resize(width,height);
        this->loopThread=new QThread;
        this->loop=new renderThread(pipeline);
        this->image= nullptr;
        loop->moveToThread(loopThread);
        connect(loop,&renderThread::frameOut,this,&windows::updateSurface);
        connect(loopThread,&QThread::started,loop,&renderThread::loop);
        loopThread->start();
        timer=new QTimer();
        connect(timer,&QTimer::timeout,this,&windows::fpsTimeOut);
        timer->start(1000);
    }

public slots:
    void updateSurface(unsigned  char * data){
        if(image) delete image;
        this->image=new QImage(data,width,height,QImage::Format_RGBA8888);
//        std::cout<<"update";
//        update();
        repaint();
        image->save("output_dispose.png","png");
        fpsCount++;
    }

     void fpsTimeOut(){
        std::cout<<"fps:"<<fpsCount<<"\n";
        fpsCount=0;
    }
protected:
    void paintEvent(QPaintEvent *event) override {
//        if(image) delete image;
//        canvas = new QImage(image, width(), height(), QImage::Format_RGBA8888);
//        update();
//        QWidget::paintEvent(event);

        if(!image) return ;
        QPainter draw(this);        //创建QPainter，将指针传入该设备
        QRect rect(0,0,this->width,this->height);
        draw.drawImage(rect,*image);//创建绘图区域
    }


};


#endif //TINYRENDER_WINDOW_H
