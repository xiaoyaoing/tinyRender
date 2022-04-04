//
// Created by 打工人 on 2022/3/20.
//
#include "pipline.h"

static Vec3f computeBarycentric2D(float x, float y, const Vec4f * v){
    float c1 = (x*(v[1][1] - v[2][1]) + (v[2][0] - v[1][0])*y + v[1][0]*v[2][1] - v[2][0]*v[1][1]) / (v[0][0]*(v[1][1] - v[2][1]) + (v[2][0] - v[1][0])*v[0][1] + v[1][0]*v[2][1] - v[2][0]*v[1][1]);
    float c2 = (x*(v[2][1] - v[0][1]) + (v[0][0] - v[2][0])*y + v[2][0]*v[0][1] - v[0][0]*v[2][1]) / (v[1][0]*(v[2][1] - v[0][1]) + (v[0][0] - v[2][0])*v[1][1] + v[2][0]*v[0][1] - v[0][0]*v[2][1]);
//    float c3 = (x*(v[0][1] - v[1][1]) + (v[1][0] - v[0][0])*y + v[0][0]*v[1][1] - v[1][0]*v[0][1]) / (v[2][0]*(v[0][1] - v[1][1]) + (v[1][0] - v[0][0])*v[2][1] + v[0][0]*v[1][1] - v[1][0]*v[0][1]);
    return {c1,c2,1-c1-c2};
}

static void transform(Pipeline *pipeline, VertexOut &source,VertexOut & target ) {

}
bool flag=0;
static void  tofile(unsigned  char * data,int width,int height){
    if(flag==1)
        return ;
    std::ofstream of("data.txt");
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            int idx=(i*width+j)*4;
            of<<(int)data[idx]<<" "<<(int)data[idx+1]<<" "<<(int)data[idx+2]<<" "<<(int)data[idx+3]<<" ";
        }
    of.close();
    flag=1;

}

Vec3f barycentric(const Vec2f tri[3], const Vec2f P) {
    mat<3,3,float> ABC;
    ABC[0]=embed<3>(tri[0]);
    ABC[1]=embed<3>(tri[1]);
    ABC[2]=embed<3>(tri[2]);
     ;
    if (ABC.det()<1e-3) return Vec3f (-1,1,1); // for a degenerate triangle generate negative coordinates, it will be thrown away by the rasterizator
    return ABC.invert_transpose() * embed<3>(P);
}


static void  clipWithPlane(clip_plane plane,std::vector<VertexOut> & in){
    int idx1,idx2;
    int numVertex=in.size();
    std::vector<VertexOut> res;
    for( idx1=0;idx1<numVertex;idx1++){
        idx2=(idx1-1+numVertex)%numVertex;
        VertexOut  v1=in[idx1];
        VertexOut  v2=in[idx2];
        bool inside1=isInsideClipPlane(plane,v1.posH);
        bool inside2=isInsideClipPlane(plane,v2.posH);
        if(inside1 ^ inside2){
            double ratio= LineIntersectionPlane(v1.posH,v2.posH,plane);
            VertexOut v=linearInterpolation(v1,v2,ratio);
            res.push_back(v);
        }
        if(inside1)
            res.push_back(v1);
    }
    in=res;
}
//投影变换后 视锥体是[-1,-1]的单位立方体 在这个空间下对三角形进行裁剪
static std::vector<VertexOut> clipTriangleUnitCube(VertexOut v1, VertexOut v2, VertexOut v3) {
    std::vector<VertexOut> in={v1,v2,v3};
//    clipWithPlane(W_PLANE,in);
    clipWithPlane(X_LEFT,in);
    clipWithPlane(X_RIGHT,in);
    clipWithPlane(Y_TOP,in);
    clipWithPlane(Y_BOTTOM,in);
    clipWithPlane(Z_NEAR,in);
    clipWithPlane(Z_FAR,in);
    return in;
}


 Pipeline::Pipeline(int width, int height) :width(width),height(height){
     frontBuffer=new frameBuffer(width,height);
     backBuffer=new frameBuffer(width,height);
//     shader=new textureShader();
//     models.push_back(Model("../obj/african_head/african_head.obj"));
     models.push_back(Model("../obj/diablo3_pose/diablo3_pose.obj"));
//     models.push_back( Model("../obj1/qiyana/qiyanabody.obj" ));
//     models.push_back(Model("../obj1/qiyana/qiyanaface.obj"));
//     models.push_back(Model("../obj1/qiyana/qiyanahair.obj"));
//        models.push_back(Model("../obj1/gun/Cerberus.obj"));

//     models.push_back(Model("../obj1/fuhua/fuhuabody.obj"));
//     models.push_back(Model("../obj1/fuhua/fuhuaface.obj"));
//     models.push_back(Model("../obj1/fuhua/fuhuahair.obj"));
//     models.push_back(Model("../obj1/fuhua/fuhuacloak.obj"));
////
//     models.push_back(Model("../obj1/yayi/yayibody.obj"));
//     models.push_back(Model("../obj1/yayi/yayiarmour1.obj"));
//     models.push_back(Model("../obj1/yayi/yayiarmour2.obj"));
//     models.push_back(Model("../obj1/yayi/yayiface.obj"));
//     models.push_back(Model("../obj1/yayi/yayihair.obj"));
//     models.push_back(Model("../obj1/yayi/yayidecoration.obj"));
//     models.push_back(Model("../obj1/yayi/yayisword.obj"));

     setViewPort(width,height);
    vis=  std::vector<bool> (width*height,false);
 }

 void Pipeline::setViewPort(int screen_width, int screen_height) {
    viewMatrix=Matrix4f ::identity();
    viewMatrix[0][0]=screen_width/2;
    viewMatrix[0][3]=screen_width/2;
    viewMatrix[1][1]=-screen_height/2;
    viewMatrix[1][3]=screen_width/2;
}

void Pipeline::draw() {
    time_t start,end;
    start=time(NULL);

    shader->updateViewMatrix();
//    std::cout<<shader->payload.view[0][0]<<shader->payload.view[1][1]<<shader->payload.view[1][2];
    Vertex *v1,*v2,* v3;
    VertexOut p1,p2,p3;
//    return ;
    for(auto model:models) {
        shader->texture = model.texture;
        for (int i = 0; i < model.m_indices.size() / 3; ++i) {

            v1 =& model.m_vertex[3 * i];
            v2 =& model.m_vertex[3 * i + 1];
            v3 = &model.m_vertex[3 * i + 2];

            p1 = shader->vertexShader(*v1);
            p2 = shader->vertexShader(*v2);
            p3 = shader->vertexShader(*v3);
//            continue;

//            std::vector<VertexOut> clip = clipTriangleUnitCube(p1, p2, p3);//齐次空间裁剪
            std::vector<VertexOut> clip={p1,p2,p3};
            if (clip.size() > 2) {
                for(int idx=0;idx<2;idx++)
                {
                clip[idx].posH.x=0.5*(width-1)*(clip[idx].posH.x + 1.0);
                clip[idx].posH.y =  0.5*(height-1)*(clip[idx].posH.y + 1.0);
                }

            }
            for (int idx = 0; idx < clip.size() - 2; idx++) {
                clip[idx+2].posH.x=0.5*(width-1)*(clip[idx+2].posH.x + 1.0);
                clip[idx+2].posH.y =  0.5*(height-1)*(clip[idx+2].posH.y + 1.0);
                Triangle triangle(&clip[idx], &clip[idx + 1], &clip[idx + 2]);
                drawTriangle(triangle);
            }
        }
    }
   tofile(backBuffer->getOutput(),800,800);
}

void Pipeline::drawLine(VertexOut &  v1,VertexOut & v2){
    int x1=v1.posH[0];
    int y1=v1.posH[1];
    int x2=v2.posH[0];
    int y2=v2.posH[1];
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    int stepX=x2-x1>0?1:-1;
    int stepY=y2-y1>0?1:-1;
    int x=x1;
    int y=y1;
    int d2x=2*dx,d2y=2*dy;
    int d2y_minus_d2x=d2y-d2x;
    VertexOut temp;
    if(dy<=dx){
        int flag=dy-2*dx;
        for(int i=0;i<=dx;i++){
            temp= linearInterpolation(v1,v2,1.0-(double)i/(dx-dy));
            Vec4f color=shader->fragmentShader(temp);
            std::cout<<x<<"  ";
            this->backBuffer->setColor(x,y,color);
            x+=stepX;
            if(flag<0){
                flag+=d2y;
            }
            else{
                y+=stepY;
                flag+=d2y_minus_d2x;
            }
        }
    }
    else {
        int flag=d2x-dy;
        for(int i=0;i<dy;i++){
            temp=linearInterpolation(v1,v2,1.0-(double)i/(dy-dx));
            Vec4f  color=shader->fragmentShader(temp);
            this->backBuffer->setColor(x,y,color);
            y+=stepY;
            if(flag<0)
                flag+=d2x;
            else{
                x+=stepX;
                flag-=d2y_minus_d2x;
            }
        }
    }
}



void Pipeline::setIndicesBuffer(std::vector<unsigned int> &buffer)  {
//    this->m_indices=buffer;
}

void Pipeline::setVertexBuffer(std::vector<Vertex> &buffer) {
//    this->m_vertices=buffer;
}

void Pipeline::fill(Vec4f color){
    backBuffer->fill(color);

}

void Pipeline::swapBuffer() {
    frameBuffer * tempBuffer;
    tempBuffer=frontBuffer;
    frontBuffer=backBuffer;
    backBuffer=tempBuffer;
}

void Pipeline::generateImage(const char * name) {
    backBuffer->generateImage(name);
//    memcpy((void *)frontBuffer,(void *)backBuffer,width*height*4);
}

static int is_inside_triangle(float alpha, float beta, float gamma)
{
    float EPSILON=1e-5;
    int flag = 0;
    // here epsilon is to alleviate precision bug
    if (alpha > -EPSILON && beta > -EPSILON && gamma > -EPSILON)
        flag = 1;

    return flag;
}







void Pipeline:: drawTriangle(Triangle & triangle){
    Vec4f  pos1=triangle.v1->posH;
    Vec4f  pos2=triangle.v2->posH;
    Vec4f  pos3=triangle.v3->posH;
    Vec4f poss[3]={pos1,pos2,pos3};
    pos1.z=pos1.w;
    pos2.z=pos2.w;
    pos3.z=pos3.w;
    float min_x = std::min(pos1[0], std::min(pos2[0], pos3[0]));
    float min_y = std::min(pos1[1], std::min(pos2[1], pos3[1]));
    float max_x = std::max(pos1[0], std::max(pos2[0], pos3[0]));
    float max_y = std::max(pos1[1], std::max(pos2[1], pos3[1]));
    MSAA= false;
    for(int x=int(min_x);x<=int(max_x);x++)
        for(int y=int(min_y);y<=int(max_y);y++){

            auto temp=computeBarycentric2D(x+0.5,y+0.5,poss);
            float  alpha=temp.x;float beta=temp.y;float gamma=temp.z;
            if(!is_inside_triangle(alpha,beta,gamma))
                continue;
              float correction= 1.0/ (alpha/pos1.z+beta/pos2.z+gamma/pos3.z); //透视矫正深度
              auto depth=linearInterpolation(pos1.z,pos2.z,pos3.z,alpha/pos1.z,beta/pos2.z,gamma/pos3.z);
              depth*=correction;
              if(depth>backBuffer->getDepth(x,y))
              {
                  Vec4f color;
                  if(MSAA){
                      float xx[2]={0.25,0.75};
                      float yy[2]={0.25,0.75};
                      for(float i : xx)
                          for(float j : yy)
                          { temp=computeBarycentric2D(x+i,y+j,poss);
                            alpha=temp.x;beta=temp.y;gamma=temp.z;
                              auto payLoad=linearInterpolation(*triangle.v1,*triangle.v2,*triangle.v3,
                                                               alpha/pos1.z,beta/pos2.z,gamma/pos3.z,correction); //透视矫正插值
                              color=color+ shader->fragmentShader(payLoad);
                          }
                      color=color/4.0f;
                  }
                  else
                  {
                      auto payLoad=linearInterpolation(*triangle.v1,*triangle.v2,*triangle.v3,
                                                 alpha/pos1.z,beta/pos2.z,gamma/pos3.z,correction); //透视矫正插值
                      color= shader->fragmentShader(payLoad);
                  }
                  backBuffer->setColor(x,y,color);
                  backBuffer->setDepth(x,y,depth);
              }
        }

}

void Pipeline::setShader(BaseShader * shader) {
    this->shader=shader;
}

void Pipeline::perspectiveDivision(VertexOut &target)
{
    target.posH.x /= target.posH.w;
    target.posH.y /= target.posH.w;
    target.posH.z /= target.posH.w;
    target.posH.w = 1.0f;
    // map from [-1,1] to [0,1]
    target.posH.z = (target.posH.z+1.0f) * 0.5f;
}

unsigned char *Pipeline::output() {
    return  frontBuffer->getOutput();
}

void Pipeline::clearBuffer() {
    Vec4f  color(131,122,155,0);
    backBuffer->fill(color);
    backBuffer->clearDepthBuffer();
}






