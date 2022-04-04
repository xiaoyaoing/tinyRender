//
// Created by 打工人 on 2022/3/20.
//

#include "vertex.h"
bool Triangle::insideTriangle(double x,double y){
//    Vector3f v[3];
//    for(int i=0;i<3;i++)
//        v[i] = {_v[i].x(),_v[i].y(), 1.0};
    Vec3f f0,f1,f2;
     Vec3f  v[3];
     v[0]={v1->posH.x,v1->posH.y,1.0};
     v[1]={v2->posH.x,v2->posH.y,1.0};
     v[2]={v3->posH.x,v3->posH.y,1.0};
    f0 = cross(v[1],v[0]);
    f1 = cross(v[2],v[1]);
    f2 = cross(v[0],v[2]);
    Vec3f p(x,y,1.);
    if(     (dot(p,f0)*dot(f0,v[2])>0)
        &&  (dot(p,f1)*dot(f1,v[0])>0)
        &&  (dot(p,f2)*dot(f2,v[1])>0)   )
        return true;
    return false;
}

