#include "world.h"
#include "resource.h"
#include "util.h"
#include "math.h"
void World_Render_Cell(World *world,Entity *PlayerCar, int x, int y)
{
    if (!World_Cell_Inbounds(world, x, y))
        return;
    int index = (x * world->cells_width) + y;
    if (index < 0) return;
    if (index >= world->numCells) return;
    if (!Cell_IsLoaded(world->cells[index]))
    {
        Cell_Load(world->cells[index]);
        return; // Dont waste more time drawing, will only cause more stutter
    }
    // Dist check is worse for performance in this case
    /*float dist = util_dist_float((float)PlayerCar->Model->x, 0, (float)PlayerCar->Model->z, (float)world->cells[index]->x, 0, (float)world->cells[index]->y);
    printf("Dist %f\n", dist);
    if (dist > 100000) return;*/
    Cell_Render(world->cells[index]);
}
void World_Render(World *world,Entity *PlayerCar)
{
    float direction = ((float)PlayerCar->Model->ry/1000)*360 * 2;
    float angle = (M_PI * direction /180);
    float frontX = sin(angle);
    float frontY = cos(angle);

    int cell_size = world->cell_size;
    int cx = (int)((int)PlayerCar->Model->x + frontX*200000)/cell_size;
    int cz = (int)((int)PlayerCar->Model->z + frontY*200000)/cell_size;
    for (int x=-2;x<=2;x++)
    {
        for (int y=-2;y<=2;y++)
        {
            World_Render_Cell(world,PlayerCar, cx + x, cz+y);
        }
    }
    /*for (int x=-4;x<=4;x++)
    {
        if (x >= -2 && x <=2) continue;
        for (int y=-4;y<=4;y++)
        {
            if (y >= -2 && y <=2) continue;
            if (!World_Cell_Inbounds(world, cx+x, cz+y)) continue;
            int index = (x * world->cells_width) + y;
            if (index < 0) continue;
            if (index >= world->numCells) continue;
            if (!Cell_IsLoaded(world->cells[index])) continue;
            Cell_Unload(world->cells[index]);
        }
    }*/
    for(int i=0; i <world->numCars;i++)
    {
       // printf("Render car %i",i);
        NE_ModelDraw(world->cars[i]->Entity->Model);
    }
}
void World_Tick(World *world)
{
    for(int i=0; i <world->numCars;i++)
    {
       // printf("Tick car %i",i);
        Car_Tick(world->cars[i]);
    }
}
bool World_AddCar(World *world, Car* car)
{
    if (world->numCars >= world->cells_max)
        return false;
    world->cars[world->numCars] = car;
    world->numCars++;
   // printf("Added car %i", world->numCars);
    return true;
}
void World_Cell_Add(World *world, Cell *cell, int x, int y)
{
    if (world->numCells > world->cells_max)
    {
        printf("Too many cells! aborting!");
        return;
    }
    if (x < 0 || x >= world->cells_width || y < 0 || y >= world->cells_height)
        return;
    int index = (x * world->cells_width) + y;
    world->cells[index] = cell;
    world->numCells++;
}
void World_Cell_Remove(World *world, int x, int y)
{
    if (x < 0 || x >= world->cells_width || y < 0 || y >= world->cells_height)
        return;
    int index = (x * world->cells_width) + y;
    if (index < 0) return;
    if (index >= world->numCells) return;
    Cell_Destroy(world->cells[index]);
    world->numCells--;
}
bool World_Cell_Inbounds(World *world, int x, int y)
{
    return !(x < 0 || x >= world->cells_width || y < 0 || y >= world->cells_height);
}
World *World_Init()
{
    World *world = calloc(1, sizeof( World));
    //Entity_LoadModel(world->groundTemp, "car.bin");
    world->numCars = 0;
    world->numCells = 0;
    world->cells_width = 10;
    world->cells_height = 10;
    world->cells_max = world->cells_width*world->cells_height;
    world->cell_size = 140000;
    //NE_Material *grassMat = Resource_LoadMaterial("grass.img.bin", 128, 128);

    int cell_size = world->cell_size;//100000;
    //int cell_quarter_size = cell_size/1.6;
    //int cell_quarter_offset = 10;
    for (int cx=0; cx < world->cells_width;cx++)
    {
        for (int cy=0; cy<world->cells_height; cy++)
        {
            Cell *cell = Cell_Create(cx*cell_size,cy*cell_size);//, grassMat);
            //Cell_Load(cell);
            World_Cell_Add(world, cell, cx, cy);
        }
    }
    return world;
}