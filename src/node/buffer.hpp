#pragma once

#include <Arduino.h>

struct Buffer
{
    uint8_t *data = nullptr;
    uint16_t length = 0;

    // Constructor to initialize buffer
    Buffer(uint8_t *data = nullptr, uint16_t length = 0) : data(data), length(length) {}

    // Destructor to free allocated memory
    ~Buffer()
    {
        if (data)
        {
            delete[] data;
        }
        data = nullptr; // Ensure pointer is reset
    }

    // Copy constructor (to handle copying safely)
    Buffer(const Buffer &other) : data(nullptr), length(other.length)
    {
        if (other.data)
        {
            data = new uint8_t[length];
            memcpy(data, other.data, length);
        }
    }

    // Move constructor (for efficient transfers)
    Buffer(Buffer &&other) noexcept : data(other.data), length(other.length)
    {
        other.data = nullptr;
        other.length = 0;
    }

    // Copy assignment operator
    Buffer &operator=(const Buffer &other)
    {
        if (this != &other)
        {
            delete[] data;
            length = other.length;
            data = new uint8_t[length];
            memcpy(data, other.data, length);
        }
        return *this;
    }

    // Move assignment operator
    Buffer &operator=(Buffer &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    // Getter for []
    uint8_t operator[](uint16_t index) const
    {
        if (index >= length || index < 0)
        {
            // Optionally, handle out-of-bounds access gracefully
            return 0; // Default value
        }
        return data[index];
    }

    // Setter for []
    uint8_t &operator[](uint16_t index)
    {
        if (index >= length || index < 0)
        {
            // Optionally, handle out-of-bounds access
            static uint8_t dummy = 0;
            return dummy; // Return a dummy variable for invalid index
        }
        return data[index];
    }

    String toString(uint8_t outNumberTypeBase = 10)
    {
        if (!length || !data)
            return "Buffer<NULL>";

        String out = "Buffer<";

        for (uint16_t i = 0; i < length; i++)
        {
            out += String(data[i], outNumberTypeBase) + (i == (length - 1) ? "" : ", ");
        }

        return out + ">";
    }
};

// Function to convert a String to a Buffer
Buffer str2Buff(const String &str)
{
    uint16_t length = str.length();
    uint8_t *data = new uint8_t[length];

    for (uint16_t i = 0; i < length; i++)
    {
        data[i] = str.charAt(i);
    }

    return Buffer(data, length);
}