#pragma once

#include "../user.hpp"
#include "../node/node.hpp"
#include <map>
#include <vector>
#include <functional>

namespace Networking
{

    namespace Pockets
    {

    };

    struct User
    {
        uint16_t id;
        uint32_t lastSignHash;
    };

    struct You
    {
        uint16_t id;
        uint32_t lastSignValue;
        uint32_t lastSignHash;
    };

    struct Group
    {
        // public
        String name;
        uint16_t id;

        // users
        std::map<uint16_t, User> users;

        // private
        std::vector<uint8_t> password;
        // salt
        uint32_t salt;
        uint16_t slatModifyerModifyer;
        uint16_t slatModifyerValue;

        You you;
    };

    struct Network
    {
        Node connection;
        std::map<String, Group> groupsJoined;
        TaskHandle_t updateTaskHandle = nullptr; // Handle for the FreeRTOS task
        bool isRunning = false;
        bool isConnected = false;

        void init(uint8_t inpPin, uint8_t outPin, int sendDelay)
        {
            connection.inpPin = inpPin;
            connection.outPin = outPin;
            connection.sendDelay = sendDelay;
            connection.init();
        }

        void start()
        {
            if (!isRunning)
            {
                isRunning = true;
                // Create a new FreeRTOS task to run the update function
                xTaskCreate(
                    [](void *context)
                    {
                        static_cast<Network *>(context)->run();
                    },
                    "NetworkUpdateTask", // Task name
                    4096,                // Stack size (adjust as necessary)
                    this,                // Pass the Network instance as context
                    1,                   // Task priority
                    &updateTaskHandle    // Task handle
                );
            }
        }

        void end()
        {
            if (isRunning)
            {
                isRunning = false;
                if (updateTaskHandle != nullptr)
                {
                    vTaskDelete(updateTaskHandle);
                    updateTaskHandle = nullptr;
                }
            }
        }

        void SendPocket(uint8_t function, const std::vector<uint8_t> &data);

        void waitForBytePacketEnd();

        void onPacketEnd();

        void update();

        void run();
    };

}

#include "./pockets.hpp"

#define MWP_Network Networking::Network