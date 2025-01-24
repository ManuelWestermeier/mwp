#pragma once

#include <Arduino.h>

#include "./read-byte.hpp"

String rawReadString(uint8_t pin, uint16_t delayTime)
{
    uint8_t receivedHash = rawReadByte(pin, delayTime);
    uint16_t length = (rawReadByte(pin, delayTime) << 8) + rawReadByte(pin, delayTime);

    // basic hash for the length
    uint8_t lengthHash = ((length >> 8) & 0x0F) ^ (length & 0x0F);

    if (lengthHash != receivedHash)
        return "";

    char *string = new char[length];

    uint8_t dataHash = 0;

    for (uint16_t i = 0; i < length; i++)
    {
        uint8_t value = rawReadByte(pin, delayTime);
        string[i] = value;
        dataHash ^= value;
    }

    uint8_t receivedDataHash = rawReadByte(pin, delayTime);
    if (dataHash != receivedDataHash)
    {
        delete[] string;
        return "";
    }

    String result = String(string, length); // Convert to String
    delete[] string;                        // Free memory
    return result;
}