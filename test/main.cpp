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
#include "BlindAccessory.hpp"

BlindAccessory *myBlind;

void setup()
{
    Serial.begin(115200);

    RelayModule *motorUp = new RelayModule(23);
    ButtonModule *buttonUp = new ButtonModule(14);

    RelayModule *motorDown = new RelayModule(22);
    ButtonModule *buttonDown = new ButtonModule(27);

    myBlind = new BlindAccessory(motorUp, motorDown, buttonUp, buttonDown, 10, 10);

    myBlind->setNotifyCallback(
        [](void *pParameter)
        {
            BlindAccessory *thisPointer = (BlindAccessory *)pParameter;
            Serial.printf("Blind position: %d\n", thisPointer->getBlindPosition());
        },
        myBlind);

    // delay(3000);
    // Serial.println("Opening door...");
    // doorLockAccessory->openDoor();
}

void loop()
{
    delay(2000);
    Serial.printf("Get Free Heap: %d\n", ESP.getFreeHeap());
    Serial.printf("Blind position: %d\n", myBlind->getBlindPosition());
}
