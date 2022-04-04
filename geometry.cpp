#include "geometry.h"

template <> template <> vec<3,int>  ::vec(const vec<3,float> &v) : x(int(v.x+.5f)),y(int(v.y+.5f)),z(int(v.z+.5f)) {}



template <> template <> vec<3,float>::vec(const vec<3,int> &v)   : x(v.x),y(v.y),z(v.z) {}
template <> template <> vec<2,int>  ::vec(const vec<2,float> &v) : x(int(v.x+.5f)),y(int(v.y+.5f)) {}
template <> template <> vec<2,float>::vec(const vec<2,int> &v)   : x(v.x),y(v.y) {}

float dot(Vec3f x,Vec3f y){
    return x[0]*y[0]+x[1]*y[1]+x[2]*y[2];
}

Matrix4f lookat(Vec3f eye, Vec3f center, Vec3f up) {

    Matrix4f  m =Matrix4f ::identity();

//    m[0][3]=-eye[0];
//    m[1][3]=-eye[1];
//    m[2][3]=-eye[2];
//    return m;
//    return m;
    auto z=(eye-center).normalize();
    auto x=cross(up,z).normalize();
    auto y=cross(z,x).normalize();

    m[0][0]=x[0];
    m[0][1]=x[1];
    m[0][2]=x[2];

    m[1][0]=y[0];
    m[1][1]=y[1];
    m[1][2]=y[2];

    m[2][0]=z[0];
    m[2][1]=z[1];
    m[2][2]=z[2];

    m[0][3]=-dot(x,eye);
    m[1][3]=-dot(y,eye);
    m[2][3]=-dot(z,eye);


    return m;
}

Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                               float zNear, float zFar)
{
    //实际上这里应该是压缩 平移 缩放 三步 这里直接把三步变换的最终结果给出
    Matrix4f m = Matrix4f ::identity();
//    return m;
    eye_fov = eye_fov / 360.0 * MY_PI;
    float temp=tan(eye_fov);
    float t = fabs(zNear) * tan(eye_fov);
    float r = aspect_ratio * t;

    m[0][0] = zNear /r;
    m[1][1] = zNear / t;
    m[2][2] = (zNear+zFar)/(zNear-zFar);
    m[2][3] = 2*zNear*zFar / (zFar-zNear);
    m[3][2] = 1;
    m[3][3] = 0;
    return m;
}


void  HomogeneousDiv(Vec4f & vec)
{
vec.x/=vec.w;
vec.y/=vec.w;
vec.z/=vec.w;
}

//判断点在不在投影平面内
bool isInsideClipPlane(clip_plane plane,Vec4f pos){
    switch (plane) {
        case W_PLANE:
            return pos.w>1e-5 ;
        case X_LEFT:
            return pos.x>-1;
        case X_RIGHT:
            return pos.x<1;
        case Y_TOP:
            return pos.y<1;
        case Y_BOTTOM:
            return pos.y>-1;
        case Z_FAR:
            return pos.z<1;
        case Z_NEAR:
            return pos.z>-1;

    }
}

double LineIntersectionPlane(Vec4f prev,Vec4f curv,clip_plane plane){
    switch (plane) {
        case X_RIGHT:
            return (prev.w - prev.x) / ((prev.w - prev.x) - (curv.w - curv.x));
        case X_LEFT:
            return (prev.w + prev.x) / ((prev.w + prev.x) - (curv.w + curv.x));
        case Y_TOP:
            return (prev.w - prev.y) / ((prev.w - prev.y) - (curv.w - curv.y));
        case Y_BOTTOM:
            return (prev.w + prev.y) / ((prev.w + prev.y) - (curv.w + curv.y));
        case Z_NEAR:
            return (prev.w - prev.z) / ((prev.w - prev.z) - (curv.w - curv.z));
        case Z_FAR:
            return (prev.w + prev.z) / ((prev.w + prev.z) - (curv.w + curv.z));
        default:
            return 0;}
}
bool help(unsigned char * data,int length)
{
for(int i=0;i<length;i++)
 if(data[i]!=255 && data[i]!=0)
    return true;
  return false;
}

