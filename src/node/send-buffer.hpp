#pragma once

#include <Arduino.h>
#include "./send-byte.hpp"
#include "./buffer.hpp"

void rawSendBuffer(Buffer buffer, uint8_t pin, uint16_t delayTime)
{
    if (!buffer.data || !buffer.length)
        return;

    // Get the size of the buffer
    uint16_t length = buffer.length;

    // Generate a simple hash for the length
    uint8_t lengthHash = ((length >> 8) & 0x0F) ^ (length & 0x0F);
    rawSendByte(lengthHash, pin, delayTime);
    delayMicroseconds(delayTime);

    // Send the length of the Buffer as two bytes
    rawSendByte((length >> 8) & 0xFF, pin, delayTime); // Correct mask for high byte
    delayMicroseconds(delayTime);
    rawSendByte(length & 0xFF, pin, delayTime); // Correct mask for low byte
    delayMicroseconds(delayTime);

    // Initialize the data hash
    uint8_t dataHash = 0;

    // Send the data bytes
    for (uint16_t i = 0; i < length; i++)
    {
        uint8_t value = buffer[i];
        dataHash ^= value; // Update the hash
        rawSendByte(value, pin, delayTime);
        delayMicroseconds(delayTime);
    }

    // Send the data hash
    rawSendByte(dataHash, pin, delayTime);
    delayMicroseconds(delayTime);
}