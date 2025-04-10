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
/*
int util_dist(NE_Camera *cam, NE_Model *model)
{
   return util_dist(cam->x, cam->y, cam->z, model->x, model->y, model->z);
}
int util_dist(NE_Model *model, NE_Model *model2)
{
   return util_dist(model->x, model->y, model->z, model2->x, model2->y, model2->z);
}*/