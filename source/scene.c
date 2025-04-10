#include "scene.h"
#include "math.h"
void Scene_Draw3d(void *arg)
{
    SceneData *scene = arg;

    NE_CameraUse(scene->Camera);
    World_Render(scene->GameWorld,scene->PlayerCar->Entity);
   // NE_ModelDraw(Scene->PlayerCar->Entity->Model);
}
void Input_Tick(SceneData* Scene)
{
    // Get keys information
    scanKeys();
    uint32_t keys = keysHeld();
    if (keys & KEY_RIGHT)
        Car_Right(Scene->PlayerCar);
    if (keys & KEY_LEFT)
        Car_Left(Scene->PlayerCar);
    if (keys & KEY_UP)
        Car_Accelerate(Scene->PlayerCar,10);
    if (keys & KEY_DOWN)
        Car_Accelerate(Scene->PlayerCar,-10);
}
void Scene_Tick(SceneData* Scene)
{
    Input_Tick(Scene);
    World_Tick(Scene->GameWorld);
    float cx = (float)Scene->PlayerCar->Entity->Model->x/4160;
    float cy = 0; //Scene->PlayerCar->Entity->Model->y;
    float cz = (float)Scene->PlayerCar->Entity->Model->z/4160;
    float direction = ((float)Scene->PlayerCar->Entity->Model->ry/1000)*360 * 2;
    float angle = (M_PI * direction /180);
  //  printf("Direction %f Angle %f ", direction, angle);
    float frontX = sin(angle);
    float frontY = cos(angle); 
    //printf("%f %f %f", cx, cy, cz);
    // Set coordinates for the camera
    NE_CameraSet(Scene->Camera,
    cx+(frontX*-10), 5, cz+(frontY*-10),  // Position
    cx+(frontX*10), 3, cz+(frontY*10),  // Look at
    0, 1, 0); // Up direction
    
}
/* ne_znear = floattof32(0.1);
    ne_zfar = floattof32(40.0); */
void Scene_Init(SceneData* Scene)
{
    // Allocate space for the objects we'll use
    Scene->Camera = NE_CameraCreate();
    NE_ClippingPlanesSetI(1000, 280000);
    // We set up a light and its color
    NE_LightSet(0, NE_White, -0.5, -0.5, -0.5);
    
    // Set coordinates for the camera
    NE_CameraSet(Scene->Camera,
        -8, 3, 0,  // Position
        0, 3, 0,  // Look at
        0, 1, 0); // Up direction

    // Init world
    Scene->GameWorld = World_Init();

    Scene->PlayerCar = Entity_Car_Create();
    World_AddCar(Scene->GameWorld, Scene->PlayerCar);

    Car *testCar = Entity_Car_Create();
    Entity_SetPos(testCar->Entity, 10,0,-5);
    World_AddCar(Scene->GameWorld, testCar);

   
  
}