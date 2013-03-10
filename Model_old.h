#ifndef _MODEL_H
#define _MODEL_H

#include "Util.h"

class Model_old
{
public:
	Model();
	~Model();
	void Dibuixa();
        void Dibuixa2();
    void Eixos();
    void LoadTexture(const char *name, const char *name1);
    void zoomIn();
    void zoomOut();

private:
    float scale;
    GLuint textures[2];
};
#endif /* _MODEL_H */
