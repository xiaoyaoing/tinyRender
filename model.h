#ifndef __MODEL_H__
#define __MODEL_H__
#include <vector>
#include <string>
#include "geometry.h"
#include "tgaimage.h"
#include "vertex.h"
#include "texture.h"

class Model {
private:
     bool  loadObjFile(const char * path);

public:
    Texture * texture;
    explicit Model(const char * path);
    std::vector<Vertex> m_vertex;
    std::vector<unsigned  int> m_indices;

    void loadTexture(const char *filename, const char *suffix);
};
#endif //__MODEL_H__

