#include "cell.h"
#include "resource.h"
Cell* Cell_Create(int x, int y)//, NE_Material *material)
{
    Cell *ent = calloc(1, sizeof( Cell));
    ent->numProps = 0;
    ent->x = x;
    ent->y = y;
    //ent->TerrainMaterial = material;
    return ent;
}
void Cell_Load(Cell *cell)
{
    cell->loaded = false;
    cell->TerrainMaterial = Resource_LoadMaterial("grass.img.bin", 128, 128);
    cell->size = 140000;

    Entity *ent = Entity_Create();
    Entity_LoadModel(ent, "model/nature/tree/tree01.bin");
    Entity_LoadTexture(ent, "model/nature/tree/tree01_spring.img.bin", 256,  256);
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
void Cell_DrawTerrain(Cell *cell)
{
    
    // This set material's color to drawing color (default = white)
    NE_MaterialUse(cell->TerrainMaterial);

    // In general you should avoid using the functions below for drawing models
    // because they have a much lower performance than precompiled models.

    // Begin drawing
    int size = 1;//cell->size; //100;
    int x = 0;//cell->x;// * size;
    int y = 0;//cell->y;// * size;
    int height = 0;
    int x2 = x + size;
    int y2 = y + size;
    MATRIX_PUSH = 0;
    MATRIX_TRANSLATE = cell->x;
    MATRIX_TRANSLATE = height;
    MATRIX_TRANSLATE = cell->y;
    MATRIX_SCALE = cell->size;
    MATRIX_SCALE = 1;
    MATRIX_SCALE = cell->size;
    NE_PolyBegin(GL_QUAD);

      //  NE_PolyColor(NE_Red);    // Set next vertices color
        NE_PolyTexCoord(0, 0);   // Texture coordinates
        NE_PolyVertex(x, height, y); // Send new vertex

       // NE_PolyColor(NE_Blue);
        NE_PolyTexCoord(0, 128);
        NE_PolyVertex(x, height, y2);

       // NE_PolyColor(NE_Green);
        NE_PolyTexCoord(128, 128);
        NE_PolyVertex(x2, height, y2);

      //  NE_PolyColor(NE_Yellow);
        NE_PolyTexCoord(128, 0);
        NE_PolyVertex(x2, height, y);

    NE_PolyEnd();
    MATRIX_POP = 1;
}
void Cell_Render(Cell *cell)
{
    Cell_DrawTerrain(cell);
    for(int i=0; i <cell->numProps;i++)
    {
        NE_ModelDraw(cell->Props[i]->Model);
        //printf("Rendering prop %i", i);
    }
}