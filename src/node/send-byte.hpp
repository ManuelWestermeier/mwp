#pragma once
#include <Arduino.h>

void rawSendByte(uint8_t value, int pin, int delayTime)
{
    // Send start signal
    digitalWrite(pin, HIGH);
    delayMicroseconds(delayTime);

    unsigned long startTime = micros() + delayTime;

    // Send each bit (LSB-first)
    for (uint8_t i = 0; i < 8; i++)
    {
        bool bit = (value & (1 << i)) != 0; // Extract bit `i`
        digitalWrite(pin, bit ? HIGH : LOW);

        // Wait for the bit duration
        unsigned long bitEndTime = startTime + (i * delayTime);
        while (micros() < bitEndTime)
            ;
    }

    // Send end signal
    digitalWrite(pin, LOW);
    delayMicroseconds(delayTime);
}

// SEND BYTE WITH FALG (FLAG=IS_FOLLOWING)
void rawSendByteWF(uint8_t value, int pin, int delayTime, bool isFollowing)
{
    // Send start signal
    digitalWrite(pin, HIGH);
    delayMicroseconds(delayTime); // Wait for start signal duration

    // Prepare for the first bit (handle isFollowing logic)
    digitalWrite(pin, isFollowing ? HIGH : LOW);
    delayMicroseconds(delayTime); // Wait for the bit duration

    // Send each bit (LSB-first)
    for (uint8_t i = 0; i < 8; i++)
    {
        // Extract bit `i`
        bool bit = (value & (1 << i)) != 0;
        digitalWrite(pin, bit ? HIGH : LOW);

        // Wait for the bit duration
        delayMicroseconds(delayTime);
    }

    // Send end signal
    digitalWrite(pin, LOW);
    delayMicroseconds(delayTime); // Wait for the end signal duration
}