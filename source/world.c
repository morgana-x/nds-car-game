#include "world.h"
#include "resource.h"
#include "util.h"

void World_Render_Cell(World *world,Entity *PlayerCar, int x, int y)
{
    if (x < 0 || x >= world->cells_width || y < 0 || y >= world->cells_height)
        return;
    int index = (x * world->cells_width) + y;
    if (index < 0) return;
    if (index >= world->numCells) return;
    // Dist check is worse for performance in this case
    /*float dist = util_dist_float((float)PlayerCar->Model->x, 0, (float)PlayerCar->Model->z, (float)world->cells[index]->x, 0, (float)world->cells[index]->y);
    printf("Dist %f\n", dist);
    if (dist > 100000) return;*/
    Cell_Render(world->cells[index]);
}
void World_Render(World *world,Entity *PlayerCar)
{
    //NE_ModelDraw(world->groundTemp->Model);
    int cell_size = world->cell_size;
    int cx = (int)PlayerCar->Model->x/cell_size;
    int cz = (int)PlayerCar->Model->z/cell_size;
    //printf("Pos: %i %i\n", cx,cz);
   // printf("Pos: %i %i\n", PlayerCar->Model->x,PlayerCar->Model->z);

    for (int x=-2;x<=2;x++)
    {
        for (int y=-2;y<=2;y++)
        {
            World_Render_Cell(world,PlayerCar, cx + x, cz+y);
        }
    }
    /*for(int i=0; i <world->numCells;i++)
    {
        float dist = util_dist_float((float)PlayerCar->Model->x, 0, (float)PlayerCar->Model->z, (float)world->cells[i]->x, 0, (float)world->cells[i]->y);
        printf("Dist %f\n", dist);
        if (dist < 100000)
            Cell_Render(world->cells[i]);
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
    if (world->numCars >= 99)
        return false;
    world->cars[world->numCars] = car;
    world->numCars++;
   // printf("Added car %i", world->numCars);
    return true;
}
void World_AddCell(World *world, Cell *cell)
{

    if (world->numCells >= 64)
        return;
    world->cells[world->numCells] = cell;
    world->numCells++;
}
World *World_Init()
{
    World *world = calloc(1, sizeof( World));
    //Entity_LoadModel(world->groundTemp, "car.bin");
    world->numCars = 0;
    world->numCells = 0;
    world->cells_width = 10;
    world->cells_height = 10;
    world->cell_size = 100000;
    //NE_Material *grassMat = Resource_LoadMaterial("grass.img.bin", 128, 128);

    int cell_size = world->cell_size;//100000;
    //int cell_quarter_size = cell_size/1.6;
    //int cell_quarter_offset = 10;
    for (int cx=0; cx < world->cells_width;cx++)
    {
        for (int cy=0; cy<world->cells_height; cy++)
        {
            Cell *cell = Cell_Create(cx*cell_size,cy*cell_size);//, grassMat);

            Entity *ent = Entity_Create();
            Entity_LoadModel(ent, "model/nature/tree/tree01.bin");
            Entity_LoadTexture(ent, "model/nature/tree/tree01_spring.img.bin", 256,  256);
            Entity_SetPos(ent, 5, 0, 10);
            Cell_AddProp(cell,ent->Model);

            
            Entity *ent2 = Entity_Create();
            Entity_LoadModel(ent2, "cube.bin");
            Entity_LoadTexture(ent2, "grass.img.bin", 128,  128);
       
            NE_ModelScaleI(ent2->Model,  cell_size,  20, cell_size);
            Cell_AddProp(cell,ent2->Model);
   
            World_AddCell(world, cell);
        }
    }
    /*world->groundTemp = Entity_Create();
    Entity_LoadModel( world->groundTemp, "cube.bin");
    NE_ModelScale(world->groundTemp->Model, 40, 1, 40);
    Entity_LoadTexture( world->groundTemp, "grass.img.bin", 128, 128);
    world->groundTemp->Model->y = -40;*/

    return world;
}