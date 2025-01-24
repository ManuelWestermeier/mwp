#pragma once

#include <Arduino.h>

#include "./read-byte.hpp"
#include "./buffer.hpp"

Buffer rawReadBuffer(uint8_t pin, uint16_t delayTime)
{
    Buffer result;

    uint8_t receivedHash = rawReadByte(pin, delayTime);
    uint16_t length = (rawReadByte(pin, delayTime) << 8) + rawReadByte(pin, delayTime);

    // basic hash for the length
    uint8_t lengthHash = ((length >> 8) & 0x0F) ^ (length & 0x0F);

    if (lengthHash != receivedHash)
        return Buffer{nullptr, 0};

    uint8_t *data = new uint8_t[length];

    uint8_t dataHash = 0;

    for (uint16_t i = 0; i < length; i++)
    {
        uint8_t value = rawReadByte(pin, delayTime);
        data[i] = value;
        dataHash ^= value;
    }

    uint8_t receivedDataHash = rawReadByte(pin, delayTime);
    if (dataHash != receivedDataHash)
    {
        delete[] data;
        return Buffer{nullptr, 0};
    }

    result.length = length;
    result.data = data;

    return result;
}