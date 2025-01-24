#pragma once

#include <Arduino.h>

int testIndex = 1;
void test()
{
    Serial.println("TEST: " + String(testIndex++));
}