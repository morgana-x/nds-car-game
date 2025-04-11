//#include "car.h"
#include "cell.h"
#include <NEMain.h>
typedef struct {
    Entity *groundTemp;
    int numCars;
    int numCells;
    Car* cars[20];
    int cells_width;
    int cells_height;
    int cells_max;
    int cell_size;
    Cell* cells[200];
    
} World;

World *World_Init();
void World_Render(World *world,Entity *Camera);
void World_Render_Cell(World *world,Entity *PlayerCar, int x, int y, int dist);
void World_Tick(World *world);
bool World_AddCar(World *world,Car* car);
void World_Cell_Add(World *world, Cell *cell, int x, int y);
void World_Cell_Remove(World *world, int x, int y);
bool World_Cell_Inbounds(World *world, int x, int y);