#pragma once

#include "./network.hpp"

void MWP_Network::waitForBytePacketEnd()
{
    auto timeToWait = micros() + (connection.sendDelay * 13);
    while (true)
    {
        auto now = micros();
        if (now > timeToWait)
        {
            return;
        }
        else if (digitalRead(connection.inpPin) == HIGH)
        {
            auto timeToWait = now + (connection.sendDelay * 13);
        }
    }
}