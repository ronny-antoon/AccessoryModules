#include <Arduino.h>
#include <MultiPrinterLogger.hpp>
#include <RelayModule.hpp>
#include <ButtonModule.hpp>
#include <LightBulbAccessory/LightBulbAccessory.hpp>

void notifyCallback(void *notifyCallbackParameter)
{
    Serial.println("Notify Callback");

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());
    Serial.printf("min heap: %d\n", ESP.getMinFreeHeap());
    Serial.printf("High Water mark %d\n", uxTaskGetStackHighWaterMark(NULL));
}

LightBulbAccessory *doorLockAccessory;

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
    doorLockAccessory = new LightBulbAccessory(relayModule, buttonModule, logger);

    doorLockAccessory->setNotifyCallback(notifyCallback, doorLockAccessory);
}

void loop()
{
    delay(5000);

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());
    xTASK_LIST_PRINT();
    delay(10000);
}