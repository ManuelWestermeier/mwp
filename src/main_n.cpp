// #include <Arduino.h>
// #include <user.hpp>
// #include <RH_ASK.h> // RadioHead library for ASK modulation
// #include <SPI.h>    // Required by RadioHead

// #define OUT_PIN_SENDER 27
// #define INP_PIN_RECEIVER 26

// // IS_SENDING should be defined somewhere else as per your configuration
// #define IS_SENDING true

// RH_ASK rf_driver;

// bool isSending = IS_SENDING;

// // Non-blocking delay handling
// unsigned long lastMillis = 0;
// unsigned long sendInterval = 1000;

// void setup()
// {
//     Serial.begin(9600);

//     if (isSending)
//     {
//         pinMode(OUT_PIN_SENDER, OUTPUT); // For sender
//         Serial.println("Initializing Transmitter...");
//         if (!rf_driver.init())
//         {
//             Serial.println("RF Initialization Failed");
//             while (1) // If RF initialization fails, stop the code to debug
//             {
//                 delay(1000);
//             }
//         }
//         else
//         {
//             Serial.println("RF Initialized for Transmitter");
//         }
//     }
//     else
//     {
//         pinMode(INP_PIN_RECEIVER, INPUT); // For receiver
//         Serial.println("Initializing Receiver...");
//         if (!rf_driver.init())
//         {
//             Serial.println("RF Initialization Failed");
//             while (1) // If RF initialization fails, stop the code to debug
//             {
//                 delay(1000);
//             }
//         }
//         else
//         {
//             Serial.println("RF Initialized for Receiver");
//         }
//     }
// }

// void loop()
// {
//     unsigned long currentMillis = millis();

//     if (isSending && (currentMillis - lastMillis >= sendInterval))
//     {
//         lastMillis = currentMillis; // Update the lastMillis timestamp

//         uint8_t data[] = {0x01, 0x02, 0x03, 0x04};

//         Serial.println("Attempting to send data...");
//         if (rf_driver.send(data, sizeof(data)))
//         {
//             Serial.println("Data Sent");
//         }
//         else
//         {
//             Serial.println("Failed to send data");
//         }
//     }
//     else if (!isSending)
//     {
//         uint8_t data[4];
//         uint8_t len = sizeof(data);

//         Serial.println("Attempting to receive data...");
//         if (rf_driver.recv(data, &len))
//         {
//             Serial.print("Received Data: ");
//             for (uint8_t i = 0; i < len; i++)
//             {
//                 Serial.print(data[i], HEX);
//                 Serial.print(" ");
//             }
//             Serial.println();
//         }
//         else
//         {
//             Serial.println("No Data Received");
//         }
//     }
// }
