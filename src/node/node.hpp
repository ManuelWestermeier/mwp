#pragma once

#include <Arduino.h>
#include "./buffer.hpp"

// bytes
#include "./read-byte.hpp"
#include "./send-byte.hpp"

// strings
#include "./read-string.hpp"
#include "./send-string.hpp"

// binarys
#include "./read-buffer.hpp"
#include "./send-buffer.hpp"

struct Node
{
    uint8_t inpPin, outPin;
    int sendDelay;

    Node() {}

    Node(uint8_t _inpPin, uint8_t _outPin, int _sendDelay)
    {
        inpPin = _inpPin;
        outPin = _outPin;
        sendDelay = _sendDelay;
    }

    void init()
    {
        pinMode(inpPin, INPUT);
        pinMode(outPin, OUTPUT);
    }

    void sendByte(uint8_t value)
    {
        rawSendByte(value, outPin, sendDelay);
    }

    void sendByteWF(uint8_t value, bool isFollowing)
    {
        rawSendByteWF(value, outPin, sendDelay, isFollowing);
    }

    uint8_t readByte()
    {
        return rawReadByte(inpPin, sendDelay);
    }

    RawPocket readByteWF()
    {
        return rawReadByteWF(inpPin, sendDelay);
    }

    void sendString(String value)
    {
        rawSendString(value, outPin, sendDelay);
    }

    String readString()
    {
        return rawReadString(inpPin, sendDelay);
    }

    void sendBuffer(Buffer buffer)
    {
        rawSendBuffer(buffer, outPin, sendDelay);
    }

    Buffer readBuffer()
    {
        return rawReadBuffer(inpPin, sendDelay);
    }
};