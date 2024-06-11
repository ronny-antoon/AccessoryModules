#include <Arduino.h>
#include <MultiPrinterLogger.hpp>
#include <RelayModule.hpp>
#include <ButtonModule.hpp>
#include <BlindAccessory/BlindAccessory.hpp>

void notifyCallback(void *notifyCallbackParameter)
{
    Serial.println("Notify Callback");

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());
    Serial.printf("min heap: %d\n", ESP.getMinFreeHeap());
    Serial.printf("High Water mark %d\n", uxTaskGetStackHighWaterMark(NULL));
}

BlindAccessory *blindAccessory;

void setup()
{
    Serial.begin(115200);

    MultiPrinterLogger *logger = new MultiPrinterLogger();
    logger->addPrinter(&Serial);
    logger->setLogLevel(MultiPrinterLoggerInterface::LogLevel::VERBOSE);
    logger->setColorEnabled(true);

    RelayModule *motorUp = new RelayModule(2, logger);
    RelayModule *motorDown = new RelayModule(33, logger);
    ButtonModule *buttonUp = new ButtonModule(5, logger);
    ButtonModule *buttonDown = new ButtonModule(27, logger);

    xTASK_LIST_PRINT();

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());

    blindAccessory = new BlindAccessory(motorUp, motorDown, buttonUp, buttonDown, 20, 20, logger);

    blindAccessory->setNotifyCallback(notifyCallback, blindAccessory);
}

void loop()
{
    delay(5000);

    Serial.printf("Heap: %d\n", ESP.getFreeHeap());
    xTASK_LIST_PRINT();
    delay(20000);
}