//
// Created by 打工人 on 2022/3/29.
//

#ifndef TINYRENDER_RENDERTHREAD_H
#define TINYRENDER_RENDERTHREAD_H
#include "QThread"
#include "pipline.h"

static  unsigned  char * getData(){
    std::ifstream ifstream2("data1.txt");
    auto * data=new unsigned  char [800*800*4];
    for(int i=0;i<800*800*4;i++)
        ifstream2>>data[i];
    return data;
}
static void change(unsigned  char * buffer,unsigned  char * data){
    int r1,r2,g1,g2,b1,b2;
    int count=0;
    for(int i=0;i<800*800;i++){
        int idx=i*4;
        r1=buffer[idx];g1=buffer[idx+1];b1=buffer[idx+2];
        r2=data[idx];g2=data[idx+1];b2=buffer[idx+2];
        if(r1==0 && g1==255){

                buffer[idx]=255;buffer[idx+1]=255;buffer[idx+2]=255;


    }}}

class renderThread: public QThread{
    Q_OBJECT;
    unsigned  char * data;
    Pipeline * pipeline;;
public:
    explicit renderThread(Pipeline * pipeline):pipeline(pipeline){
        data=getData();
    }

signals:
    void frameOut(unsigned char *image);


public slots:
    void loop()  {
        while(true){
            pipeline->clearBuffer();
            pipeline->draw();
//            pipeline->clearBuffer();
//            pipeline->generateImage("output.tga");
            pipeline->swapBuffer();
            auto buffer=pipeline->output();
            emit frameOut(buffer);
        }
    }
};
#endif //TINYRENDER_RENDERTHREAD_H
