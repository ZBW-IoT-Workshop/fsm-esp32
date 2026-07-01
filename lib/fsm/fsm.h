#pragma once

#include <cstddef>
#include <cstdint>

namespace fsm
{

class FSM
{
  public:
    enum class Reason : uint8_t
    {
        Enter,
        Do,
        Exit
    };

    using StateId = size_t;

    using Handler = bool (*)(FSM &fsm, Reason reason, void *context);

    struct State
    {
        const char *name;
        Handler handler;
    };

    FSM(const State *const states, size_t stateCount, StateId initial, void *context = nullptr, const char *name = "");

    void reset();
    bool run();

    bool transitionTo(StateId next);
    bool transitionTo(const char *next);

    StateId getCurrentStateId() const;
    const char *getCurrentStateName() const;

  private:
    bool call(StateId id, Reason reason);
    bool isValidState(StateId id) const;
    const char *getStateName(StateId id) const;
    FSM::StateId nameToId(const char *state_name) const;
    void logPrefix() const;

    const char *name_;
    void *context_;
    const State *states_;
    size_t stateCount_;

    StateId initState_;
    StateId currentState_;
    StateId nextState_;
};

} // namespace fsm