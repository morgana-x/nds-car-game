#include "scene.h"
#include "math.h"
#include "resource.h"
void Scene_Draw_Skybox(SceneData *Scene)
{
        // This set material's color to drawing color (default = white)
        NE_MaterialUse(Scene->SkyboxMaterial);

       // glMatrixMode(GL_PROJECTION);
        //glLoadIdentity();
       // gluPerspective(70, 256.0 / 192.0, 0.1, 40);
    
        gluLookAt(0.0, 0.0, 2.0,  // Position
                  0.0, 0.0, 0.0,  // Look at
                  0.0, 1.0, 0.0); // Up
        // In general you should avoid using the functions below for drawing models
        // because they have a much lower performance than precompiled models.
        glMatrixMode(GL_MODELVIEW);
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

        glPushMatrix();
        //glOrthof32(0,0,1,1,100,1000);
        // Begin drawing
        float z = -1; //Scene->Camera->to[0] - 1000;
        glBegin(GL_TRIANGLES);
    
            //NE_PolyColor(NE_Red);    // Set next vertices color
            NE_PolyTexCoord(0, 0);   // Texture coordinates
            glVertex3f(0, 2, z); // Send new vertex
    
            //NE_PolyColor(NE_Blue);
            NE_PolyTexCoord(0, 128);
            glVertex3f(3, -1, z);
    
            //NE_PolyColor(NE_Green);
            NE_PolyTexCoord(128, 128);
            glVertex3f(-3, -1, z);
        glEnd();
        glPopMatrix(1);
        glMatrixMode(GL_MODELVIEW);
}
void Scene_Draw3d(void *arg)
{
    SceneData *scene = arg;

   // Scene_Draw_Skybox(scene);
   
    NE_CameraUse(scene->Camera);
    
    
    // This has to be used to use fog
    NE_PolyFormat(31, 0, NE_LIGHT_ALL, NE_CULL_BACK, NE_FOG_ENABLE);
    
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
    float angle = Entity_GetAngle_Radians(Scene->PlayerCar->Entity);
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
    NE_ClippingPlanesSetI(1000, 350000);
    // We set up a light and its color
    NE_LightSet(0, NE_White, -0.5, -0.5, -0.5);

    //NE_FogEnable(shift, color, 31, mass, depth);
    NE_FogEnable(5, NE_White, 31, 1, 0x7C00);

    // Set coordinates for the camera
    NE_CameraSet(Scene->Camera,
        -8, 3, 0,  // Position
        0, 3, 0,  // Look at
        0, 1, 0); // Up direction

    Scene->SkyboxMaterial = Resource_LoadMaterial("grass.img.bin", 128, 128);
    // Init world
    Scene->GameWorld = World_Init();

    Scene->PlayerCar = Entity_Car_Create();
    World_AddCar(Scene->GameWorld, Scene->PlayerCar);

    Car *testCar = Entity_Car_Create();
    Entity_SetPos(testCar->Entity, 10,0,-5);
    testCar->aiType = AI_TRAFFIC;
    World_AddCar(Scene->GameWorld, testCar);

   
  
}