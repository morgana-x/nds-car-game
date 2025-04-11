#include "entity.h"
#include <NEMain.h>
#include "resource.h"
#include <math.h>

void Entity_LoadModel(  Entity *entity, const char* path) {
    if (entity->Model == NULL)
        entity->Model = NE_ModelCreate(NE_Static);
     // Load mesh from the filesystem and assign it to the object "Model".
     NE_ModelLoadStaticMeshFAT(entity->Model, path);
}
void Entity_LoadTexture(  Entity *entity, const char* path, int width, int height ) {
    NE_Material *Material = Resource_LoadMaterial(path,width,height);// NE_MaterialCreate();
    NE_ModelSetMaterial(entity->Model, Material);
}
void Entity_LoadTexture_Transperant(  Entity *entity, const char* path, int width, int height ) {
    NE_Material *Material = Resource_LoadMaterialTransperant(path,width,height);// NE_MaterialCreate();
    NE_ModelSetMaterial(entity->Model, Material);
}
void Entity_SetPos(Entity *entity, int x, int y, int z)
{
    NE_ModelSetCoord(entity->Model, x, y,  z);
}
float Entity_GetAngle_Degrees(Entity *entity)
{
    return ((float)entity->Model->ry/1000)*360 * 2;
}
float Entity_GetAngle_Radians(Entity *entity)
{
    return (M_PI * Entity_GetAngle_Degrees(entity) /180);
}
void Entity_Init(  Entity *entity)
{

}
void Entity_Tick(  Entity *entity)
{
    
}
void Entity_Destroy(Entity *entity)
{
    free(entity->Model);
    free(entity);
}
Entity *Entity_Create()
{
    Entity *ent = calloc(1, sizeof( Entity));
    if (ent == NULL)
    {
        printf("Failed to create entity!!!!!!!!");
    }
    /*ent->LoadModel = Entity_LoadModel;
    ent->LoadTexture = Entity_LoadTexture;
    ent->Init = Entity_Init;
    ent->Tick = Entity_Tick;*/
    return ent;
}