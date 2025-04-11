#include "world.h"
typedef struct {
    NE_Camera *Camera;
    Car *PlayerCar;
    World *GameWorld;
    NE_Material *SkyboxMaterial;
} SceneData;

void Scene_Draw3d(void *arg);
void Scene_Draw_Skybox(SceneData*scene);
void Scene_Tick(SceneData* scene);
void Scene_Init(SceneData* Scene);
void Input_Tick(SceneData* scene);