#ifndef FAN_ACCESSORY_TEST_HPP
#define FAN_ACCESSORY_TEST_HPP

#include <gtest/gtest.h>
#include <Arduino.h>

#include <RelayModule.hpp>
#include <ButtonModule.hpp>

#include "FanAccessory/FanAccessory.hpp"

class FanAccessoryTest : public ::testing::Test
{
protected:
    uint32_t initialFreeHeap = 0; // Initial free heap size
    uint8_t relayPin = 14;        // Pin assigned to the relay
    uint8_t buttonPin = 22;       // Pin assigned to the button

    // Components used in the test
    RelayModule *relay;
    ButtonModule *button;
    FanAccessory *fanAccessory;

    // Set up function to run before each test case
    void SetUp() override
    {
        delay(10);                                      // Introduce a delay of 10ms to allow ESP32 to complete booting
        initialFreeHeap = ESP.getFreeHeap();            // Record the initial free heap size
        relay = new RelayModule(relayPin);              // Create an instance of the RelayModule
        button = new ButtonModule(buttonPin);           // Create an instance of the ButtonModule
        fanAccessory = new FanAccessory(relay, button); // Create an instance of the FanAccessory
    }

    // Tear down function to run after each test case
    void TearDown() override
    {
        delete relay;        // Delete the relay instance
        delete button;       // Delete the button instance
        delete fanAccessory; // Delete the FanAccessory instance
        delay(10);           // Introduce a delay of 10ms to allow ESP32 to release resources
        if (ESP.getFreeHeap() != initialFreeHeap)
            FAIL() << "Memory leak of " << initialFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }
};

// Test Notification Callback
TEST_F(FanAccessoryTest, NotificationCallback)
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
    fanAccessory->setNotifyCallback(mockCallback, pChar);

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
TEST_F(FanAccessoryTest, SetStatus)
{
    // Set the status to true
    fanAccessory->setStatus(true, false);

    // Check if the status is true
    EXPECT_EQ(fanAccessory->getStatus(), true);

    // Set the status to false
    fanAccessory->setStatus(false, false);

    // Check if the status is false
    EXPECT_EQ(fanAccessory->getStatus(), false);
};

// Test setStatus with notification
TEST_F(FanAccessoryTest, SetStatusWithNotification)
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
    fanAccessory->setNotifyCallback(mockCallback, pChar);

    // Set the status to true
    fanAccessory->setStatus(true, true);

    // delay to allow the callback function to be called
    delay(100);

    // Check if the status is true
    EXPECT_EQ(fanAccessory->getStatus(), true);

    // Check if the char is changed to 'B'
    EXPECT_EQ(*pChar, 'B');

    // Set the status to false
    fanAccessory->setStatus(false, true);

    // delay to allow the callback function to be called
    delay(100);

    // Check if the status is false
    EXPECT_EQ(fanAccessory->getStatus(), false);

    // Check if the char is changed to 'B'
    EXPECT_EQ(*pChar, 'B');

    // Delete the pointer char variable
    delete pChar;
};

// Test button press to turn on/off
TEST_F(FanAccessoryTest, ButtonPressToTurnOnOff)
{
    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100); // debounce
    digitalWrite(buttonPin, LOW);
    delay(100); // debounce

    // Check if the status is true
    EXPECT_EQ(fanAccessory->getStatus(), true);

    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100); // debounce
    digitalWrite(buttonPin, LOW);
    delay(100); // debounce

    // Check if the status is false
    EXPECT_EQ(fanAccessory->getStatus(), false);
};

// test max alloc free heap
TEST_F(FanAccessoryTest, MaxAllocFreeHeap)
{
    void (*mockCallback)(void *) = [](void *pParameter) {
    };
    fanAccessory->setNotifyCallback(mockCallback, fanAccessory);
    fanAccessory->setStatus(true, true);
    fanAccessory->getStatus();

    // simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100); // debounce
    digitalWrite(buttonPin, LOW);
    delay(100); // debounce

    int maxAllocFreeHeap = ESP.getMaxAllocHeap();
    for (int i = 0; i < 20; i++)
    {
        fanAccessory->setStatus(true, true);
        fanAccessory->getStatus();
        fanAccessory->setStatus(false, true);
        fanAccessory->getStatus();
        fanAccessory->setStatus(true, false);

        pinMode(buttonPin, OUTPUT);
        digitalWrite(buttonPin, HIGH);
        delay(100); // debounce
        digitalWrite(buttonPin, LOW);
        delay(100); // debounce
    }
    EXPECT_EQ(ESP.getMaxAllocHeap(), maxAllocFreeHeap);
};

#endif // FAN_ACCESSORY_TEST_HPP