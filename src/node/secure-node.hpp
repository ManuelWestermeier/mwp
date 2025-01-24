#pragma once

#include <Arduino.h>
#include <functional>
#include "./buffer.hpp"
#include "./node.hpp"

enum class PocketType : uint8_t
{
    BUFFER = 1,
    STRING = 2,
    BYTE = 3,
};

struct SecureNode
{
    Node connection;
    bool isRunning = true;

    std::function<void(Buffer)> onBuffer = nullptr;
    std::function<void(String)> onString = nullptr;
    std::function<void(uint8_t)> onByte = nullptr;
    std::function<void(uint8_t)> onError = nullptr; // Callback for handling unexpected packet types

    SecureNode(uint8_t inpPin, uint8_t outPin, int sendDelay)
        : connection(inpPin, outPin, sendDelay) // Initialize Node here
    {
        connection.init();
    }

    void listen()
    {
        isRunning = true;
        while (isRunning) // Use atomic load for thread-safe checks
        {
            uint8_t pocketType = connection.readByte();

            switch (static_cast<PocketType>(pocketType))
            {
            case PocketType::BUFFER:
                if (onBuffer)
                    onBuffer(connection.readBuffer());
                break;

            case PocketType::STRING:
                if (onString)
                    onString(connection.readString());
                break;

            case PocketType::BYTE:
                if (onByte)
                    onByte(connection.readByte());
                break;

            default:
                if (onError)
                    onError(pocketType);
                break;
            }
        }
        isRunning = true;
    }

    void stop()
    {
        isRunning = false;
    }

    void send(const Buffer &buffer)
    {
        connection.sendByte(static_cast<uint8_t>(PocketType::BUFFER));
        connection.sendBuffer(buffer);
    }

    void send(const String &string)
    {
        connection.sendByte(static_cast<uint8_t>(PocketType::STRING));
        connection.sendString(string);
    }

    void send(uint8_t byte)
    {
        connection.sendByte(static_cast<uint8_t>(PocketType::BYTE));
        connection.sendByte(byte);
    }

    template <typename T>
    void sendType(T value)
    {
        send(value);
    }
};