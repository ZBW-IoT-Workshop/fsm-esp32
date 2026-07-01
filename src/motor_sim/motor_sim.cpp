#include "motor_sim.h"
#include <Arduino.h>

MotorStatus MotorSim::run()
{
    if (isRunning_)
    {
        if (movingUp_)
        {
            if (frameIndex_ > 0)
                frameIndex_--;
        }
        else
        {
            if (frameIndex_ < LED_COUNT)
                frameIndex_++;
        }
    }

    animation_.render(&currentFrame_, frameIndex_);
    showFrame(&currentFrame_, &leds_);

    if (isAtUpperLimit())
    {
        isRunning_ = false;
        return MotorStatus::UpperLimit;
    }

    if (isAtLowerLimit())
    {
        isRunning_ = false;
        return MotorStatus::LowerLimit;
    }

    if (isRunning_)
    {
        return movingUp_ ? MotorStatus::MovingUp : MotorStatus::MovingDown;
    }

    return MotorStatus::Stopped;
}

void MotorSim::up()
{
    if (isAtUpperLimit())
    {
        isRunning_ = false;
        return;
    }

    movingUp_ = true;
    isRunning_ = true;
}

void MotorSim::down()
{
    if (isAtLowerLimit())
    {
        isRunning_ = false;
        return;
    }

    movingUp_ = false;
    isRunning_ = true;
}

void MotorSim::stop()
{
    isRunning_ = false;
}

bool MotorSim::isAtUpperLimit() const
{
    return frameIndex_ == 0;
}

bool MotorSim::isAtLowerLimit() const
{
    return frameIndex_ >= LED_COUNT;
}
