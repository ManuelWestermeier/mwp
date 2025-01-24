#include <Arduino.h>

#include "./node/debug-test.hpp"
#include "./networking/network.hpp"

#define OUT_PIN 27
#define INP_PIN 26

#define SEND_DELAY 50

MWP_Network network;

void setup()
{
    Serial.begin(115200);
    Serial.println(IS_SENDING ? "SENDER" : "RECEIVER");

    network.init(INP_PIN, OUT_PIN, SEND_DELAY);
    network.start();
}

void loop()
{
}