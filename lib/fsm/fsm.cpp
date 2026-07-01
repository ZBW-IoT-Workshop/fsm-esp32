#include "fsm.h"
#include <Arduino.h>
#include <cstring>

namespace fsm
{

FSM::FSM(const State *const states, size_t stateCount, StateId initial, void *context, const char *name)
    : context_(context), states_(states), stateCount_(stateCount), initState_(initial), currentState_(initial),
      nextState_(initial), name_(name)
{
    if (isValidState(currentState_))
    {
        logPrefix();
        Serial.print("Initial state ");
        Serial.println(getCurrentStateName());s
        call(currentState_, Reason::Enter);
    }
}

void FSM::reset()
{
    if (!isValidState(currentState_))
    {
        return;
    }

    call(currentState_, Reason::Exit);

    currentState_ = initState_;
    nextState_ = initState_;

    if (isValidState(currentState_))
    {
        call(currentState_, Reason::Enter);
    }
}

bool FSM::run()
{
    if (!isValidState(currentState_))
    {
        return false;
    }

    if (nextState_ != currentState_)
    {
        logPrefix();
        Serial.print("Exit state ");
        Serial.println(getCurrentStateName());
        call(currentState_, Reason::Exit);

        if (isValidState(nextState_))
        {
            logPrefix();
            Serial.print("FSM: Enter state ");
            Serial.println(getStateName(nextState_));
            call(nextState_, Reason::Enter);
        }

        currentState_ = nextState_;
    }

    return call(currentState_, Reason::Do);
}

bool FSM::transitionTo(StateId next)
{
    if (!isValidState(next))
    {
        return false;
    }

    nextState_ = next;

    logPrefix();
    Serial.print("Transition from ");
    Serial.print(getCurrentStateName());
    Serial.print(" to ");
    Serial.println(getStateName(nextState_));

    return true;
}

bool FSM::transitionTo(const char *state_name)
{
    return transitionTo(nameToId(state_name));
}

FSM::StateId FSM::getCurrentStateId() const
{
    return currentState_;
}

const char *FSM::getCurrentStateName() const
{
    return getStateName(currentState_);
}

const char *FSM::getStateName(StateId id) const
{
    return isValidState(id) ? states_[id].name : "";
}

bool FSM::call(StateId id, Reason reason)
{
    auto handler = states_[id].handler;
    return handler ? handler(*this, reason, context_) : false;
}

bool FSM::isValidState(StateId id) const
{
    return id < stateCount_;
}

FSM::StateId FSM::nameToId(const char *state_name) const
{
    if (state_name == "")
    {
        return stateCount_;
    }

    for (StateId id = 0; id < stateCount_; id++)
    {
        const char *name = states_[id].name;

        if (name && std::strcmp(name, state_name) == 0)
        {
            return id;
        }
    }

    return stateCount_;
}

void FSM::logPrefix() const
{
    if (name_ != "")
    {
        Serial.print(name_);
        Serial.print(" FSM: ");
    }
    else
    {
        Serial.print("FSM: ");
    }
}

} // namespace fsm