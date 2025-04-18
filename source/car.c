#include "car.h"
#include <NEMain.h>
#include <math.h>
void Car_Accelerate(Car *car, int amount)
{
    if (car->Speed + amount >= car->MaxSpeed)
        return;
    if (car->Speed + amount <= -(car->MaxSpeed))
        return;
    car->Speed+=amount;
}
float Car_SteeringAmount(Car *car)
{
    float proportion = ((car->Speed*1.5)/car->MaxSpeed)*2;
    if (proportion > 0)
        proportion = -proportion;
    return proportion;
}
void Car_Left(Car *car)
{
    NE_ModelRotate(car->Entity->Model, 0, -2 * Car_SteeringAmount(car), 0);
}
void Car_Right(Car *car)
{
    NE_ModelRotate(car->Entity->Model, 0, 2 * Car_SteeringAmount(car), 0);
}
void Car_Tick_Ai(Car *car)
{
    if (car->aiType == AI_NONE) return;

    float ty = car->Entity->Model->z - car->targetZ;
    float tx = car->Entity->Model->x - car->targetX;
    float dist = sqrt((tx*tx) + (ty*ty));
    printf("Distance %f\n", dist);
    if (dist < 1000) return;
    float targetAngle = 3 + (atan2(ty,tx));
    float currentAngle = Entity_GetAngle_Radians(car->Entity);
    printf("Angle: %f Target: %f\n", currentAngle, targetAngle);
    float difference = sqrt((targetAngle - currentAngle) * (targetAngle - currentAngle));
    //printf("Difference %f\n", difference);
    if (difference > 0.1)
    {
        if (currentAngle < targetAngle)
            Car_Left(car);
        else
            Car_Right(car);
    }
    //car->Entity->Model->ry = (((targetAngle*(180/M_PI))/360/2)*1000); //((float)entity->Model->ry/1000)*360 * 2
    Car_Accelerate(car, 20);
}
void Car_Tick(Car *car)
{
    Car_Tick_Ai(car);
    if (car->Speed == 0)
        return;
    if (car->Speed > 0)
    {
        car->Speed-=1;
        if (car->Speed < 0)
            car->Speed = 0;
    }
    if (car->Speed < 0)
    {
        car->Speed+=1;
        if (car->Speed > 0)
            car->Speed = 0;
    }
    float direction = ((float)car->Entity->Model->ry/1000)*360 * 2;
    float angle = (M_PI * direction /180);
  //  printf("Direction %f Angle %f ", direction, angle);
    car->Entity->Model->x += sin(angle) * 2 * car->Speed;
    car->Entity->Model->z += cos(angle) * 2 * car->Speed;   
}
void Car_Init(Car *car)
{
    car->aiType = AI_NONE;
    car->MaxSpeed = 500;
    car->Entity->Model = NE_ModelCreate(NE_Static);
    car->targetX = 20000;
    car->targetZ = 10000;
    Entity_LoadModel(    car->Entity,"model/cars/car/car.bin");
    Entity_LoadTexture(  car->Entity,"model/cars/car/car_blue.img.bin", 128, 128);
}
Car *Entity_Car_Create()
{
    Car *ent = calloc(1, sizeof( Car));
    ent->Entity = Entity_Create();
    Car_Init(ent);
    return ent;
}