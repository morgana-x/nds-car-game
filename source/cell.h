#include <NEMain.h>
#include "car.h"
typedef struct {
    Entity* Props[10];
    NE_Material* TerrainMaterial;
    int numProps;
    int x;
    int y;
    int size;
    bool loaded;
}Cell;

Cell* Cell_Create(int x, int y);
void Cell_Prop_Add(Cell *cell, Entity* mdl);
void Cell_Render(Cell *cell);
void Cell_Destroy(Cell *cell);
void Cell_Load(Cell *cell);
void Cell_Unload(Cell *cell);
bool Cell_IsLoaded(Cell *cell);
void Cell_DrawTerrain(Cell *cell);