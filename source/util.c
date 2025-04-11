#include "util.h"
#include <math.h>
int util_dist(int x1, int y1, int z1, int x2, int y2, int z2)
{
    int dx = (x1-x2);
    int dy = (y1-y2);
    int dz = (z1-z2);
    return sqrt( (dx*dx) + (dy*dy) + (dz*dz));
}
float util_dist_float(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float dx = (x1-x2);
    float dy = (y1-y2);
    float dz = (z1-z2);
    return sqrt( (dx*dx) + (dy*dy) + (dz*dz));
}

void draw_quad(int x, int y, int z, int scale)
{
    MATRIX_PUSH = 0;
    MATRIX_TRANSLATE = x;
    MATRIX_TRANSLATE = y;
    MATRIX_TRANSLATE = z;
    MATRIX_SCALE = scale;
    MATRIX_SCALE = 1;
    MATRIX_SCALE = scale;
    NE_PolyBegin(GL_QUAD);

      //  NE_PolyColor(NE_Red);    // Set next vertices color
        NE_PolyTexCoord(0, 0);   // Texture coordinates
        NE_PolyVertex(0, 0, 0); // Send new vertex

       // NE_PolyColor(NE_Blue);
        NE_PolyTexCoord(0, 128);
        NE_PolyVertex(0, 0, 1);

       // NE_PolyColor(NE_Green);
        NE_PolyTexCoord(128, 128);
        NE_PolyVertex(1, 0, 1);

      //  NE_PolyColor(NE_Yellow);
        NE_PolyTexCoord(128, 0);
        NE_PolyVertex(1, 0, 0);

    NE_PolyEnd();
    MATRIX_POP = 1;
}
/*
int util_dist(NE_Camera *cam, NE_Model *model)
{
   return util_dist(cam->x, cam->y, cam->z, model->x, model->y, model->z);
}
int util_dist(NE_Model *model, NE_Model *model2)
{
   return util_dist(model->x, model->y, model->z, model2->x, model2->y, model2->z);
}*/