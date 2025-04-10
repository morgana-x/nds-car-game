#include "cell.h"
Cell* Cell_Create(int x, int y)//, NE_Material *material)
{
    Cell *ent = calloc(1, sizeof( Cell));
    ent->numProps = 0;
    ent->x = x;
    ent->y = y;
    //ent->TerrainMaterial = material;
    return ent;
}
void Cell_AddProp(Cell *cell, NE_Model* mdl)
{
    if ( cell->numProps >= 9)
    {
        printf("Too many props! %i", cell->numProps);
        return;
    }
    mdl->x += cell->x;
    mdl->z += cell->y;
    cell->Props[cell->numProps] = mdl;
    cell->numProps++;
}
void Cell_Render(Cell *cell)
{
    for(int i=0; i <cell->numProps;i++)
    {
        NE_ModelDraw(cell->Props[i]);
        //printf("Rendering prop %i", i);
    }
}