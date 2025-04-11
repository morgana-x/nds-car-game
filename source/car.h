#include "entity.h"
#include <NEMain.h>
enum CAR_AI {
    AI_NONE,
    AI_TRAFFIC
};
typedef struct{
    Entity* Entity;
    int Speed;
    int MaxSpeed;
    int Direction;
    enum CAR_AI aiType;
    int targetX;
    int targetZ;
    
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