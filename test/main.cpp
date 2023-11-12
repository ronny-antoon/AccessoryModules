// #ifdef GLOBAL_TEST_ENVIRONMENT

// #include <Arduino.h>
// #include <gtest/gtest.h>

// void setup()
// {
//     Serial.begin(115200);
//     ::testing::InitGoogleTest();
// }

// void loop()
// {
//     if (RUN_ALL_TESTS())
//         ;

//     delay(1000);

//     Serial.println("-----------------------------------Finished all tests!-----------------------------------");

//     delay(10000);
// }

// #endif // GLOBAL_TEST_ENVIRONMENT

#include <Arduino.h>

#include "ButtonModule.hpp"
#include "RelayModule.hpp"
#include "DoorLockAccessory.hpp"

void setup()
{
    Serial.begin(115200);

    RelayModule *relayModule = new RelayModule(2);
    ButtonModule *buttonModule = new ButtonModule(5);
    DoorLockAccessory *doorLockAccessory = new DoorLockAccessory(relayModule, buttonModule);

    doorLockAccessory->setNotifyCallback(
        [](void *pParameter)
        {
            Serial.printf("Door lock accessory callback fired! State: %s\n", ((DoorLockAccessory *)pParameter)->isDoorOpen() ? "open" : "closed");
        },
        doorLockAccessory);

    // delay(3000);
    // Serial.println("Opening door...");
    // doorLockAccessory->openDoor();
}

void loop()
{
    delay(5000);
    Serial.printf("Get Free Heap: %d\n", ESP.getFreeHeap());
}
