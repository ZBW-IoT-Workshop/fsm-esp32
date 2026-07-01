#include "garage_door.h"

using namespace fsm;

typedef enum GarageDoorState_e
{
    STATE_STOPPED_OPENING = 0,
    STATE_CLOSING,
    // Add state enum for other states here
    STATE_COUNT, // Sentinel
} GarageDoorState;

static bool stateStoppedOpening(FSM &fsm, FSM::Reason reason, void *context);
static bool stateClosing(FSM &fsm, FSM::Reason reason, void *context);
// Add declaration of other state function here

static void button_wait_for_press(QwiicButton *const button);

static const FSM::State states[] = {
    {"StoppedOpening", stateStoppedOpening},
    {"Closing", stateClosing},
    // Add other states here
};

FSM *garage_door_create(GarageDoorContext *const context)
{
    return new FSM(states, STATE_COUNT, STATE_STOPPED_OPENING, context, "Garage Door");
}

static bool stateStoppedOpening(FSM &fsm, FSM::Reason reason, void *context)
{
    GarageDoorContext *garageDoor = (GarageDoorContext *)context;

    switch (reason)
    {
    case FSM::Reason::Do:
        button_wait_for_press(garageDoor->button);
        fsm.transitionTo(STATE_CLOSING);
        break;

    default:
        break;
    }

    return true;
}

static bool stateClosing(FSM &fsm, FSM::Reason reason, void *context)
{
    GarageDoorContext *garageDoor = (GarageDoorContext *)context;

    switch (reason)
    {
    case FSM::Reason::Enter:
        garageDoor->motorSim->down();
        break;

    case FSM::Reason::Do:
        Serial.println("Closing Do");

        if (garageDoor->motorSim->run() == MotorStatus::LowerLimit)
        {
        }
        else if (garageDoor->button->hasBeenClicked())
        {
        }
        break;

    default:
        break;
    }

    return true;
}


static void button_wait_for_press(QwiicButton *const button)
{
    button->clearEventBits();

    while (!button->hasBeenClicked())
    {
        delay(20);
    }

    button->clearEventBits();
    Serial.println("Button pressed");
}
