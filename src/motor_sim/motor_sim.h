#pragma once

#include "../../lib/led/QwiicLedStick.h"
#include <Animation.h>
#include <LedFrame.h>
#include <cstdbool>
#include <cstdint>

enum class MotorStatus : uint8_t
{
    MovingUp,
    MovingDown,
    UpperLimit,
    LowerLimit,
    Stopped,
};

class MotorSim
{
  public:
    MotorSim(LED &leds, Animation &animation) : leds_(leds), animation_(animation)
    {
    }

    MotorStatus run();
    void up();
    void down();
    void stop();

  private:
    LED &leds_;
    Animation &animation_;
    Frame currentFrame_ = {};
    uint32_t frameIndex_ = 0;
    bool isRunning_ = false;
    bool movingUp_ = false;

    bool isAtUpperLimit() const;
    bool isAtLowerLimit() const;
};
