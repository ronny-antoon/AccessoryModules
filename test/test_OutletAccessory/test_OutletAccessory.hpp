#ifndef OUTLET_ACCESSORY_TEST_HPP
#define OUTLET_ACCESSORY_TEST_HPP

#include <gtest/gtest.h>
#include <Arduino.h>

#include <RelayModule.hpp>
#include <ButtonModule.hpp>

#include "OutletAccessory/OutletAccessory.hpp"

class OutletAccessoryTest : public ::testing::Test
{
protected:
    uint32_t initialFreeHeap = 0; // Initial free heap size
    uint8_t relayPin = 14;        // Pin assigned to the relay
    uint8_t buttonPin = 22;       // Pin assigned to the button

    // Components used in the test
    RelayModule *relay;
    ButtonModule *button;
    OutletAccessory *outletAccessory;

    // Set up function to run before each test case
    void SetUp() override
    {
        delay(10);                                            // Introduce a delay of 10ms to allow ESP32 to complete booting
        initialFreeHeap = ESP.getFreeHeap();                  // Record the initial free heap size
        relay = new RelayModule(relayPin);                    // Create an instance of the RelayModule
        button = new ButtonModule(buttonPin);                 // Create an instance of the ButtonModule
        outletAccessory = new OutletAccessory(relay, button); // Create an instance of the OutletAccessory
    }

    // Tear down function to run after each test case
    void TearDown() override
    {
        delete relay;           // Delete the relay instance
        delete button;          // Delete the button instance
        delete outletAccessory; // Delete the OutletAccessory instance
        delay(10);              // Introduce a delay of 10ms to allow ESP32 to release resources
        if (ESP.getFreeHeap() != initialFreeHeap)
            FAIL() << "Memory leak of " << initialFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }
};

// Test Notification Callback
TEST_F(OutletAccessoryTest, NotificationCallback)
{
    // Mock callback function, that recive a void pointer(should be pointer to char), check if it "A", then change it to "B"
    void (*mockCallback)(void *) = [](void *pParameter)
    {
        char *_pChar = static_cast<char *>(pParameter);
        if (*_pChar == 'A')
            *_pChar = 'B';
    };

    // create a new pointer char variable, and set it to 'A'.
    char *pChar = new char('A');

    // Set the callback function
    outletAccessory->setNotifyCallback(mockCallback, pChar);

    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100); // debounce
    digitalWrite(buttonPin, LOW);
    delay(100); // debounce

    // Check if the char is changed to 'B'
    EXPECT_EQ(*pChar, 'B');

    // Delete the pointer char variable
    delete pChar;
};

// Test setStatus
TEST_F(OutletAccessoryTest, SetStatus)
{
    // Set the status to true
    outletAccessory->setStatus(true, false);

    // Check if the status is true
    EXPECT_EQ(outletAccessory->getStatus(), true);

    // Set the status to false
    outletAccessory->setStatus(false, false);

    // Check if the status is false
    EXPECT_EQ(outletAccessory->getStatus(), false);
};

// Test setStatus with notification
TEST_F(OutletAccessoryTest, SetStatusWithNotification)
{
    // Mock callback function, that recive a void pointer(should be pointer to char), check if it "A", then change it to "B"
    void (*mockCallback)(void *) = [](void *pParameter)
    {
        char *_pChar = static_cast<char *>(pParameter);
        if (*_pChar == 'A')
            *_pChar = 'B';
    };

    // create a new pointer char variable, and set it to 'A'.
    char *pChar = new char('A');

    // Set the callback function
    outletAccessory->setNotifyCallback(mockCallback, pChar);

    // Set the status to true
    outletAccessory->setStatus(true, true);

    // delay to allow the callback function to be called
    delay(100);

    // Check if the status is true
    EXPECT_EQ(outletAccessory->getStatus(), true);

    // Check if the char is changed to 'B'
    EXPECT_EQ(*pChar, 'B');

    // Set the status to false
    outletAccessory->setStatus(false, true);

    // delay to allow the callback function to be called
    delay(100);

    // Check if the status is false
    EXPECT_EQ(outletAccessory->getStatus(), false);

    // Check if the char is changed to 'B'
    EXPECT_EQ(*pChar, 'B');

    // Delete the pointer char variable
    delete pChar;
};

// Test button press to turn on/off
TEST_F(OutletAccessoryTest, ButtonPressToTurnOnOff)
{
    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100); // debounce
    digitalWrite(buttonPin, LOW);
    delay(100); // debounce

    // Check if the status is true
    EXPECT_EQ(outletAccessory->getStatus(), true);

    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100); // debounce
    digitalWrite(buttonPin, LOW);
    delay(100); // debounce

    // Check if the status is false
    EXPECT_EQ(outletAccessory->getStatus(), false);
};

// test max alloc free heap
TEST_F(OutletAccessoryTest, MaxAllocFreeHeap)
{
    void (*mockCallback)(void *) = [](void *pParameter) {
    };
    outletAccessory->setNotifyCallback(mockCallback, outletAccessory);
    outletAccessory->setStatus(true, true);
    outletAccessory->getStatus();

    // simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100); // debounce
    digitalWrite(buttonPin, LOW);
    delay(100); // debounce

    int maxAllocFreeHeap = ESP.getMaxAllocHeap();
    for (int i = 0; i < 20; i++)
    {
        outletAccessory->setStatus(true, true);
        outletAccessory->getStatus();
        outletAccessory->setStatus(false, true);
        outletAccessory->getStatus();
        outletAccessory->setStatus(true, false);

        pinMode(buttonPin, OUTPUT);
        digitalWrite(buttonPin, HIGH);
        delay(100); // debounce
        digitalWrite(buttonPin, LOW);
        delay(100); // debounce
    }
    EXPECT_EQ(ESP.getMaxAllocHeap(), maxAllocFreeHeap);
};

#endif // OUTLET_ACCESSORY_TEST_HPP