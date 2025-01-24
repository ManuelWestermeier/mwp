#pragma once

#include "./network.hpp"

struct MWP_Network::Pockets::IsHerePacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::IS_HERE);
    uint8_t groupNameLength;
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t answerId;
    std::string groupName;
    uint32_t currentSignHash;
    uint32_t hash;
};

struct MWP_Network::Pockets::HereIsPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::HERE_IS);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t answerId;
    uint16_t groupId;
    uint16_t connectId;
    uint32_t verifyBytes;
    uint16_t salt;
    uint32_t hash;
};

struct MWP_Network::Pockets::JoinPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::JOIN);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t connectId;
    uint32_t verifyBytes;
    uint32_t lastSignValue;
    uint32_t currentSignHash;
    uint32_t hash;
};

struct MWP_Network::Pockets::AcceptPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::ACCEPT);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t connectId;
    uint16_t newUserId;
    uint16_t globalConstant = 111;
    uint32_t currentSalt;
    uint16_t errorIdentifier;
    uint16_t saltModifierPerPacket;
    uint32_t hash;
};

struct MWP_Network::Pockets::JoinedPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::JOINED);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t errorIdentifier;
    uint16_t userId;
    uint32_t currentSalt;
    uint32_t lastSignValue;
    uint32_t currentSignHash;
    uint32_t hash;
};

struct MWP_Network::Pockets::WhoIsInGroupPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::WHO_IS_IN_THE_GROUP);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t userId;
    uint32_t currentSalt;
    uint32_t lastSignValue;
    uint32_t currentSignHash;
    uint32_t hash;
};

struct MWP_Network::Pockets::IAmInGroupPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::I_AM_IN_THE_GROUP);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t userId;
    uint32_t lastSignValue;
    uint32_t currentSignHash;
    uint32_t hash;
};

struct MWP_Network::Pockets::WrongSignPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::WRONG_SIGN);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t userId;
    uint16_t userWithWrongSignId;
    uint16_t wrongSignPacketId;
    uint32_t lastSignValue;
    uint32_t currentSignHash;
    uint32_t hash;
};

struct MWP_Network::Pockets::WrongSignPacketIsCorruptedPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::WRONG_SIGN_PACKET_IS_CORRUPTED);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t userId;
    uint16_t hackerUserWithWrongSignId;
    uint16_t wrongSignPacketId;
    uint32_t lastSignValue;
    uint32_t currentSignHash;
    uint32_t hash;
};

struct MWP_Network::Pockets::SendPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::SEND);
    uint8_t dataLength;
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t userId;
    uint16_t userDestination;
    uint32_t lastSignValue;
    uint32_t currentSignHash;
    uint64_t hash;
    std::vector<uint8_t> data;
};

struct MWP_Network::Pockets::SendToMultipleUsersPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::SEND_TO_MULTIPLE_USERS);
    uint16_t usersLength;
    uint8_t dataLength;
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t userId;
    uint32_t lastSignValue;
    uint32_t currentSignHash;
    uint64_t hash;
    std::vector<uint16_t> userDestinations;
    std::vector<uint8_t> data;
};

struct MWP_Network::Pockets::BroadcastInnerGroupPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::BROADCAST_INNER_GROUP);
    uint8_t dataLength;
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t groupId;
    uint16_t userId;
    uint32_t lastSignValue;
    uint32_t currentSignHash;
    uint64_t hash;
    std::vector<uint8_t> data;
};

struct MWP_Network::Pockets::BroadcastInnerNetworkPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::BROADCAST_INNER_NETWORK);
    uint8_t dataLength;
    uint8_t lfHash;
    uint16_t packetId;
    uint64_t hash;
    std::vector<uint8_t> data;
};

struct MWP_Network::Pockets::SendToMacInnerNetworkPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::SEND_TO_MAC_INNER_NETWORK);
    uint8_t dataLength;
    uint8_t lfHash;
    uint16_t packetId;
    uint32_t macAddress;
    uint64_t hash;
    std::vector<uint8_t> data;
};

struct MWP_Network::Pockets::PacketDataErrorPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::PACKET_DATA_ERROR);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t errorPacketId;
    uint8_t hash;
};

struct MWP_Network::Pockets::PacketIsCorruptedPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::PACKET_IS_CORRUPTED);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t hackerPacketId;
    uint8_t hash;
};

struct MWP_Network::Pockets::PacketReceivedPacket
{
    uint8_t function = static_cast<uint8_t>(NetworkPacketType::PACKET_RECEIVED);
    uint8_t lfHash;
    uint16_t packetId;
    uint16_t rcvPacketId;
    uint8_t hash;
};
