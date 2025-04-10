#include <NEMain.h>
typedef struct {
    NE_Material *Material;
    NE_Model *Model;
    /*void (*Init)( Entity *entity);
    void (*Tick)( Entity *entity);
    void (*LoadModel)( Entity *entity, const char* path);
    void (*LoadTexture)( Entity *entity,const char* path, int width, int height);
*/
}Entity;

Entity *Entity_Create();
void Entity_LoadModel(  Entity *entity, const char* path);
void Entity_LoadTexture(  Entity *entity, const char* path, int width, int height );
void Entity_Init(  Entity *entity);
void Entity_Tick(  Entity *entity);
void Entity_SetPos(Entity *entity, int x, int y, int z);