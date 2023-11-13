/**
 * @file example.ino
 * @brief Example of how to use the BlindAccessory class.
 */

#include <Arduino.h>
#include "BlindAccessory.hpp"
#include "ButtonModule.hpp"
#include "RelayModule.hpp"

void createBlindAccessory(uint8_t buttonUp, uint8_t buttonDown, uint8_t motorUp, uint8_t motorDown)
{
    RelayModule *relayModuleUp = new RelayModule(motorUp);
    RelayModule *relayModuleDown = new RelayModule(motorDown);
    ButtonModule *buttonModuleUp = new ButtonModule(buttonUp);
    ButtonModule *buttonModuleDown = new ButtonModule(buttonDown);

    BlindAccessory *blindAccessory = new BlindAccessory(relayModuleUp, relayModuleDown, buttonModuleUp, buttonModuleDown);

    blindAccessory->setNotifyCallback(
        [](void *pParameter)
        {
            BlindAccessoryInterface *blindAccessory = (BlindAccessoryInterface *)pParameter;
            Serial.printf("the current postion %d, and the target position is %d \n", blindAccessory->getCurrentPosition(), blindAccessory->getTargetPosition());
        },
        blindAccessory);
}

void setup()
{
    Serial.begin(115200);

    int allButtonsPin[] = {14, 27, 26, 25, 33, 32, 35, 34};
    int allRelaysPin[] = {23, 22, 21, 19, 18, 17, 16, 4};

    createBlindAccessory(allButtonsPin[0], allButtonsPin[1], allRelaysPin[0], allRelaysPin[1]);
    createBlindAccessory(allButtonsPin[2], allButtonsPin[3], allRelaysPin[2], allRelaysPin[3]);
    createBlindAccessory(allButtonsPin[4], allButtonsPin[5], allRelaysPin[4], allRelaysPin[5]);
    createBlindAccessory(allButtonsPin[6], allButtonsPin[7], allRelaysPin[6], allRelaysPin[7]);
}

void loop()
{
    delay(5000);
}