#ifndef SWITCH_ACCESSORY_TEST_HPP
#define SWITCH_ACCESSORY_TEST_HPP

#include <gtest/gtest.h>
#include <Arduino.h>

#include <RelayModule.hpp>
#include <ButtonModule.hpp>

#include "SwitchAccessory/SwitchAccessory.hpp"

class SwitchAccessoryTest : public ::testing::Test
{
protected:
    uint32_t initialFreeHeap = 0; // Initial free heap size
    uint8_t relayPin = 14;        // Pin assigned to the relay
    uint8_t buttonPin = 22;       // Pin assigned to the button

    // Components used in the test
    RelayModule *relay;
    ButtonModule *button;
    SwitchAccessory *switchAccessory;

    // Set up function to run before each test case
    void SetUp() override
    {
        delay(10);                                            // Introduce a delay of 10ms to allow ESP32 to complete booting
        initialFreeHeap = ESP.getFreeHeap();                  // Record the initial free heap size
        relay = new RelayModule(relayPin);                    // Create an instance of the RelayModule
        button = new ButtonModule(buttonPin);                 // Create an instance of the ButtonModule
        switchAccessory = new SwitchAccessory(relay, button); // Create an instance of the SwitchAccessory
    }

    // Tear down function to run after each test case
    void TearDown() override
    {
        delete relay;           // Delete the relay instance
        delete button;          // Delete the button instance
        delete switchAccessory; // Delete the SwitchAccessory instance
        delay(10);              // Introduce a delay of 10ms to allow ESP32 to release resources
        if (ESP.getFreeHeap() != initialFreeHeap)
            FAIL() << "Memory leak of " << initialFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }
};

// Test Notification Callback
TEST_F(SwitchAccessoryTest, NotificationCallback)
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
    switchAccessory->setNotifyCallback(mockCallback, pChar);

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
TEST_F(SwitchAccessoryTest, SetStatus)
{
    // Set the status to true
    switchAccessory->setStatus(true, false);

    // Check if the status is true
    EXPECT_EQ(switchAccessory->getStatus(), true);

    // Set the status to false
    switchAccessory->setStatus(false, false);

    // Check if the status is false
    EXPECT_EQ(switchAccessory->getStatus(), false);
};

// Test setStatus with notification
TEST_F(SwitchAccessoryTest, SetStatusWithNotification)
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
    switchAccessory->setNotifyCallback(mockCallback, pChar);

    // Set the status to true
    switchAccessory->setStatus(true, true);

    // delay to allow the callback function to be called
    delay(100);

    // Check if the status is true
    EXPECT_EQ(switchAccessory->getStatus(), true);

    // Check if the char is changed to 'B'
    EXPECT_EQ(*pChar, 'B');

    // Set the status to false
    switchAccessory->setStatus(false, true);

    // delay to allow the callback function to be called
    delay(100);

    // Check if the status is false
    EXPECT_EQ(switchAccessory->getStatus(), false);

    // Check if the char is changed to 'B'
    EXPECT_EQ(*pChar, 'B');

    // Delete the pointer char variable
    delete pChar;
};

// Test button press to turn on/off
TEST_F(SwitchAccessoryTest, ButtonPressToTurnOnOff)
{
    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100); // debounce
    digitalWrite(buttonPin, LOW);
    delay(100); // debounce

    // Check if the status is true
    EXPECT_EQ(switchAccessory->getStatus(), true);

    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100); // debounce
    digitalWrite(buttonPin, LOW);
    delay(100); // debounce

    // Check if the status is false
    EXPECT_EQ(switchAccessory->getStatus(), false);
};

#endif // SWITCH_ACCESSORY_TEST_HPP