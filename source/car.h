#include "entity.h"
#include <NEMain.h>
typedef struct{
    Entity* Entity;
    int Speed;
    int MaxSpeed;
    int Direction;
    /*void (*Right)( Car *entity);
    void (*Left)(  Car *entity);
    void (*Accelerate)( Car *entity);*/
}Car ;
void Car_Accelerate( Car *car, int amount);
void Car_Left( Car *car);
void Car_Right( Car *car);
void Car_Tick( Car *entity);
void Car_Init( Car *entity);
Car *Entity_Car_Create();