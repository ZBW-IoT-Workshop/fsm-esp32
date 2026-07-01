#pragma once

#include "../motor_sim/motor_sim.h"
#include <Sparkfun_Qwiic_Button.h>
#include <fsm.h>

typedef struct GarageDoorContext_s
{
    QwiicButton *button;
    MotorSim *motorSim;
} GarageDoorContext;

fsm::FSM *garage_door_create(GarageDoorContext *const context);