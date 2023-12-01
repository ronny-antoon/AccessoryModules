#include <Arduino.h>
#include <MultiPrinterLogger.hpp>
#include <RelayModule.hpp>
#include <ButtonModule.hpp>
#include <DoorLockAccessory/DoorLockAccessory.hpp>

void notifyCallback(void *notifyCallbackParameter)
{
    Serial.println("Notify Callback");

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());
    Serial.printf("min heap: %d\n", ESP.getMinFreeHeap());
    Serial.printf("High Water mark %d\n", uxTaskGetStackHighWaterMark(NULL));
}

DoorLockAccessory *doorLockAccessory;

void setup()
{
    Serial.begin(115200);

    MultiPrinterLogger *logger = new MultiPrinterLogger();
    logger->addPrinter(&Serial);
    logger->setLogLevel(MultiPrinterLoggerInterface::LogLevel::VERBOSE);
    logger->setColorEnabled(true);

    RelayModule *relayModule = new RelayModule(2, true, logger);
    ButtonModule *buttonModule = new ButtonModule(5, true, logger);
    xTASK_LIST_PRINT();

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());
    doorLockAccessory = new DoorLockAccessory(relayModule, buttonModule, 12, logger);

    doorLockAccessory->setNotifyCallback(notifyCallback, doorLockAccessory);
}

void loop()
{
    delay(5000);

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());
    xTASK_LIST_PRINT();
    delay(5000);

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());
    xTASK_LIST_PRINT();
    delay(5000);

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());
    xTASK_LIST_PRINT();

    if (doorLockAccessory != nullptr)
    {
        delete doorLockAccessory;
        doorLockAccessory = nullptr;
    }
    // put your main code here, to run repeatedly:
}