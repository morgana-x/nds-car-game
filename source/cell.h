#include <NEMain.h>

typedef struct {
    NE_Model* Props[10];
    int numProps;
    int x;
    int y;
}Cell;

Cell* Cell_Create(int x, int y);
void Cell_AddProp(Cell *cell, NE_Model* mdl);
void Cell_Render(Cell *cell);