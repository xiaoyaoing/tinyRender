#include <iostream>
#include <fstream>
#include <sstream>
#include "model.h"


#include "model.h"
void Model::loadTexture(const char * filename,const char * suffix){
    std::string textureFile(filename);
    int idx=textureFile.find_last_of('.');
    if(idx!=std::string::npos){
        textureFile= textureFile.substr(0,idx)+std::string(suffix);
        this->texture=new Texture(textureFile.data());
    }
}

Model::Model(const char *filename) {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail())
    {   std::cout<<filename<<" Model loaded fail";
        return;}

    loadTexture(filename,"_diffuse.tga");
    std::string line;
    std::vector<Vec4f> pos;
    std::vector<Vec3f> normal;
    std::vector<Vec2f> uvs;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec4f v;
            for (int i=0;i<3;i++) iss >> v[i];
            v[3]=1;
            pos.push_back(v);
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec3f n;
            for (int i=0;i<3;i++) iss >> n[i];
            normal.push_back(n);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec2f uv;
            for (int i=0;i<2;i++) iss >> uv[i];
            uvs.push_back(uv);
        }  else if (!line.compare(0, 2, "f ")) {
            int index[3];
            iss>>trash;
            for(int i=0;i<3;i++)
            {   iss>>index[0]>>trash>>index[1]>>trash>>index[2];
                Vertex v;
                v.position=pos[index[0]-1];
                v.normal=normal[index[2]-1].normalize();
                v.texcoord=uvs[index[1]-1];
                v.color=Vec4f(i==0?1:0,i==1?1:0,i==2?1:0,1);
                m_indices.push_back(m_vertex.size());
                m_vertex.push_back(v);
            }
        }
    }
//    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << " vt# " << uv_.size() << " vn# " << norms_.size() << std::endl;
//    load_texture(filename, "_diffuse.tga", diffusemap_);
//    load_texture(filename, "_nm_tangent.tga",      normalmap_);
//    load_texture(filename, "_spec.tga",    specularmap_);
}

//Model::~Model() {}
//
//int Model::nverts() {
//    return (int)verts_.size();
//}
//
//int Model::nfaces() {
//    return (int)faces_.size();
//}
//
//std::vector<int> Model::face(int idx) {
//    std::vector<int> face;
//    for (int i=0; i<(int)faces_[idx].size(); i++) face.push_back(faces_[idx][i][0]);
//    return face;
//}
//
//Vec3f Model::vert(int i) {
//    return verts_[i];
//}
//
//Vec3f Model::vert(int iface, int nthvert) {
//    return verts_[faces_[iface][nthvert][0]];
//}
//
//void Model::load_texture(std::string filename, const char *suffix, TGAImage &img) {
//    std::string texfile(filename);
//    size_t dot = texfile.find_last_of(".");
//    if (dot!=std::string::npos) {
//        texfile = texfile.substr(0,dot) + std::string(suffix);
//        std::cerr << "texture file " << texfile << " loading " << (img.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
//        img.flip_vertically();
//    }
//}
//
//TGAColor Model::diffuse(Vec2f uvf) {
//    Vec2i uv(uvf[0]*diffusemap_.get_width(), uvf[1]*diffusemap_.get_height());
//    return diffusemap_.get(uv[0], uv[1]);
//}
//
//Vec3f Model::normal(Vec2f uvf) {
//    Vec2i uv(uvf[0]*normalmap_.get_width(), uvf[1]*normalmap_.get_height());
//    TGAColor c = normalmap_.get(uv[0], uv[1]);
//    Vec3f res;
//    for (int i=0; i<3; i++)
//        res[2-i] = (float)c[i]/255.f*2.f - 1.f;
//    return res;
//}
//
//Vec2f Model::uv(int iface, int nthvert) {
//    return uv_[faces_[iface][nthvert][1]];
//}
//
//float Model::specular(Vec2f uvf) {
//    Vec2i uv(uvf[0]*specularmap_.get_width(), uvf[1]*specularmap_.get_height());
//    return specularmap_.get(uv[0], uv[1])[0]/1.f;
//}
//
//Vec3f Model::normal(int iface, int nthvert) {
//    int idx = faces_[iface][nthvert][2];
//    return norms_[idx].normalize();
//}

