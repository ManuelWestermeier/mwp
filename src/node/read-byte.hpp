#pragma once
#include <Arduino.h>

uint8_t rawReadByte(uint8_t pin, int delayTime)
{
    // Wait for the start signal (HIGH state)
    while (digitalRead(pin) != HIGH)
        ;

    // Record the start time
    unsigned long startTime = micros();

    uint8_t value = 0;

    // Read each bit
    for (uint8_t i = 0; i < 8; i++)
    {
        // Calculate the target time for this bit
        unsigned long bitStartTime = startTime + ((i + 1.5) * delayTime);

        // Wait for the correct time
        while (micros() < bitStartTime)
            ;

        // Sample the bit
        if (digitalRead(pin) == HIGH)
        {
            value |= (1 << i); // Set bit in LSB-first order
        }
    }

    // Wait for the end of the transmission
    while (digitalRead(pin) == HIGH)
        ;

    return value;
}

struct RawPocket
{
    bool isFollowing;
    uint8_t data;
};

RawPocket rawReadByteWF(uint8_t pin, int delayTime)
{
    RawPocket pocket;
    pocket.data = 0;

    // Wait for the start signal (HIGH state)
    while (digitalRead(pin) != HIGH)
        ;

    delayMicroseconds(delayTime * 1.5);

    pocket.isFollowing = (digitalRead(pin) == HIGH);
    delayMicroseconds(delayTime);

    // Read each bit
    for (uint8_t i = 0; i < 8; i++)
    {
        // Sample the bit
        if (digitalRead(pin) == HIGH)
        {
            pocket.data |= (1 << i); // Set bit in LSB-first order
        }
        delayMicroseconds(delayTime);
    }

    return pocket;
}