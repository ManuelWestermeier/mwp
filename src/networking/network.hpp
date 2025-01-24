#pragma once

#include "../user.hpp"
#include "../node/node.hpp"
#include <map>
#include <vector>
#include <functional>

namespace Networking
{

    enum NetworkPacketTypes
    {
        IS_HERE = 1,                        // Used to discover network groups
        HERE_IS = 2,                        // Confirms the group's existence
        JOIN = 3,                           // Request to join a group
        ACCEPT = 4,                         // Response to a join request
        JOINED = 5,                         // Acknowledges successful group joining
        WHO_IS_IN_THE_GROUP = 6,            // Ask who is in the group
        I_AM_IN_THE_GROUP = 7,              // Say that you are in the group
        WRONG_SIGN = 8,                     // Indicate if a user sends the wrong sign hash
        WRONG_SIGN_PACKET_IS_CORRUPTED = 9, // Indicate a hacker's false claim about a valid sign
        SEND = 10,                          // Send data to a specific user
        SEND_TO_MULTIPLE_USERS = 11,        // Broadcast data to multiple specific users
        BROADCAST_INNER_GROUP = 12,         // Broadcast data within a group
        BROADCAST_INNER_NETWORK = 20,       // Broadcast data to all devices in the network
        SEND_TO_MAC_INNER_NETWORK = 21      // Send a message to a user in the network by MAC address
    };

    // Packet handler type
    typedef std::function<void(const Networking::Network &)> PacketHandlerFunction;

    // Initialization of packetHandlers map
    std::map<Networking::NetworkPacketTypes, Networking::PacketHandlerFunction> packetHandlers = {
        {IS_HERE, ([](const Networking::Network &net)
                   {
                       // Default handler for IS_HERE
                       // std::cout << "Default handler for IS_HERE\n";
                   })},
        {HERE_IS, ([](const Networking::Network &net)
                   {
                       // Default handler for HERE_IS
                       // std::cout << "Default handler for HERE_IS\n";
                   })},
        {JOIN, ([](const Networking::Network &net)
                {
                    // Default handler for JOIN
                    // std::cout << "Default handler for JOIN\n";
                })},
        {ACCEPT, ([](const Networking::Network &net)
                  {
                      // Default handler for ACCEPT
                      // std::cout << "Default handler for ACCEPT\n";
                  })},
        {JOINED, ([](const Networking::Network &net)
                  {
                      // Default handler for JOINED
                      // std::cout << "Default handler for JOINED\n";
                  })},
        {WHO_IS_IN_THE_GROUP, ([](const Networking::Network &net)
                               {
                                   // Default handler for WHO_IS_IN_THE_GROUP
                                   // std::cout << "Default handler for WHO_IS_IN_THE_GROUP\n";
                               })},
        {I_AM_IN_THE_GROUP, ([](const Networking::Network &net)
                             {
                                 // Default handler for I_AM_IN_THE_GROUP
                                 // std::cout << "Default handler for I_AM_IN_THE_GROUP\n";
                             })},
        {WRONG_SIGN, ([](const Networking::Network &net)
                      {
                          // Default handler for WRONG_SIGN
                          // std::cout << "Default handler for WRONG_SIGN\n";
                      })},
        {WRONG_SIGN_PACKET_IS_CORRUPTED, ([](const Networking::Network &net)
                                          {
                                              // Default handler for WRONG_SIGN_PACKET_IS_CORRUPTED
                                              // std::cout << "Default handler for WRONG_SIGN_PACKET_IS_CORRUPTED\n";
                                          })},
        {SEND, ([](const Networking::Network &net)
                {
                    // Default handler for SEND
                    // std::cout << "Default handler for SEND\n";
                })},
        {SEND_TO_MULTIPLE_USERS, ([](const Networking::Network &net)
                                  {
                                      // Default handler for SEND_TO_MULTIPLE_USERS
                                      // std::cout << "Default handler for SEND_TO_MULTIPLE_USERS\n";
                                  })},
        {BROADCAST_INNER_GROUP, ([](const Networking::Network &net)
                                 {
                                     // Default handler for BROADCAST_INNER_GROUP
                                     // std::cout << "Default handler for BROADCAST_INNER_GROUP\n";
                                 })},
        {BROADCAST_INNER_NETWORK, ([](const Networking::Network &net)
                                   {
                                       // Default handler for BROADCAST_INNER_NETWORK
                                       // std::cout << "Default handler for BROADCAST_INNER_NETWORK\n";
                                   })},
        {SEND_TO_MAC_INNER_NETWORK, ([](const Networking::Network &net)
                                     {
                                         // Default handler for SEND_TO_MAC_INNER_NETWORK
                                         // std::cout << "Default handler for SEND_TO_MAC_INNER_NETWORK\n";
                                     })},
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
        std::function<void(uint8_t errorType)> onError = nullptr;

        void init(uint8_t inpPin, uint8_t outPin, int sendDelay)
        {
            connection.inpPin = inpPin;
            connection.outPin = outPin;
            connection.sendDelay = sendDelay;
            connection.init();
        }

        std::map<String, Group> groupsJoined;
        TaskHandle_t updateTaskHandle = nullptr; // Handle for the FreeRTOS task
        bool isRunning = false;

        // Start function: creates a new FreeRTOS task
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

        // End function: deletes the task
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

    private:
        std::vector<std::vector<uint8_t>> pocketsToSend;

        void SendPocket(const std::vector<uint8_t> &data)
        {
            pocketsToSend.push_back(data);
        }

        void waitForBytePacketEnd()
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
                    auto timeToWait = now + (connection.sendDelay * 12);
                }
            }
        }

        void onPacketEnd()
        {
            if (pocketsToSend.size() != 0)
            {
            }
        }

        void update()
        {
            auto currentPocket = connection.readByteWF();

            if (currentPocket.isFollowing)
            {
                return;
            }

            if (Networking::packetHandlers.find(static_cast<Networking::NetworkPacketTypes>(currentPocket.data)) == Networking::packetHandlers.end())
            {
                if (!onError)
                    return;
                onError(currentPocket.data);
            }
        }

        void run()
        {
            // wait for byte end
            waitForBytePacketEnd();

            // update
            while (isRunning)
                update();
        }
    };

}