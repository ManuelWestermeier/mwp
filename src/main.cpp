#include <Arduino.h>

#include "./node/debug-test.hpp"
#include "./networking/network.hpp"

#define OUT_PIN 27
#define INP_PIN 26

#define SEND_DELAY 25

Networking::Network network;

void setup()
{
    Serial.begin(115200);
    Serial.println(IS_SENDING ? "SENDER" : "RECEIVER");

    network.init(INP_PIN, OUT_PIN, SEND_DELAY);
    network.start();
}

void loop()
{
    return;
#if IS_SENDING
    auto start = micros();
    network.connection.sendByteWF(111, true);
    auto end = micros();
    Serial.println(end - start);
    Serial.println((end - start) / network.connection.sendDelay);
    delay(1000);
#else
    auto pocket = network.connection.readByteWF();
    Serial.println(pocket.isFollowing ? "is f" : "is n f");
    Serial.println(pocket.data);
#endif
}