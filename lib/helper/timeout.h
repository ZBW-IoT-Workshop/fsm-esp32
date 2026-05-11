#pragma once

#include <Arduino.h>
#include <cstdint>

namespace helper
{

class Timeout
{
  public:
    Timeout(uint32_t timeout_ms = 0) : timeout_ms_(timeout_ms) {};
    virtual ~Timeout() = default;

    void start()
    {
        startTime_ms_ = millis();
    }

    void start(uint32_t timeout_ms)
    {
        timeout_ms_ = timeout_ms;
        start();
    }

    bool has_timed_out()
    {
        return (millis() - startTime_ms_) >= timeout_ms_;
    }

  private:
    uint32_t startTime_ms_;
    uint32_t timeout_ms_;
};

} // namespace helper
