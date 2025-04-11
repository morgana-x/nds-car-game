#include "cell.h"
#include "util.h"
#include "resource.h"
Cell* Cell_Create(int x, int y, int size)//, NE_Material *material)
{
    Cell *ent = calloc(1, sizeof( Cell));
    ent->numProps = 0;
    ent->x = x*size;
    ent->y = y*size;
    ent->size = size;
    //ent->TerrainMaterial = material;
    return ent;
}
void Cell_Load(Cell *cell)
{
    cell->loaded = false;
    cell->TerrainMaterial = Resource_LoadMaterial("grass.img.bin", 128, 128);

    Entity *ent = Entity_Create();
    Entity_LoadModel(ent, "model/nature/tree/tree01.bin");
    Entity_LoadTexture_Transperant(ent, "model/nature/tree/tree01_spring.img.bin", 256,  256);
    
    Entity_SetPos(ent, 5, 0, 10);
    Cell_Prop_Add(cell,ent);

    
    /*Entity *ent2 = Entity_Create();
    Entity_LoadModel(ent2, "cube.bin");
    Entity_LoadTexture(ent2, "grass.img.bin", 128,  128);

    NE_ModelScaleI(ent2->Model,  cell->size,  20, cell->size);

    Cell_Prop_Add(cell,ent2);*/


    cell->loaded = true;
}
void Cell_Unload(Cell *cell)
{
    cell->loaded = false;
    for (int i=0; i<cell->numProps;i++)
    {
        Entity_Destroy(cell->Props[i]);
    }
    cell->numProps = 0;
}
bool Cell_IsLoaded(Cell *cell)
{
    return cell->loaded;
}
void Cell_Destroy(Cell *cell)
{
    free(cell);
}
void Cell_Prop_Add(Cell *cell, Entity* mdl)
{
    if ( cell->numProps >= 9)
    {
        printf("Too many props! %i", cell->numProps);
        return;
    }
    mdl->Model->x += cell->x;
    mdl->Model->z += cell->y;
    cell->Props[cell->numProps] = mdl;
    cell->numProps++;
}
void Cell_DrawTerrain(Cell *cell, int lod)
{
    
    // This set material's color to drawing color (default = white)
    NE_MaterialUse(cell->TerrainMaterial);

    int quadSize = cell->size /lod;
    for (int x=0;x<lod;x++)
    {
        for (int y=0; y<lod;y++)
        {
            draw_quad(cell->x + (x*quadSize), 0, cell->y + (y*quadSize), quadSize);
        }
    }
}
void Cell_DrawTerrain_Simple(Cell *cell)
{
    
    // This set material's color to drawing color (default = white)
    NE_MaterialUse(cell->TerrainMaterial);
    draw_quad(cell->x, 0,cell->y, cell->size);
}
void Cell_Render(Cell *cell, int dist)
{
    if (dist < 3)
        Cell_DrawTerrain(cell, 2);
    else
        Cell_DrawTerrain_Simple(cell);
    for(int i=0; i <cell->numProps;i++)
    {
        NE_ModelDraw(cell->Props[i]->Model);
        //printf("Rendering prop %i", i);
    }
}