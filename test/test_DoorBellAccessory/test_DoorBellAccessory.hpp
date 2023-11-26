#ifndef DOORBELL_ACCESSORY_TEST_HPP
#define DOORBELL_ACCESSORY_TEST_HPP

#include <Arduino.h>
#include <gtest/gtest.h>

#include <ButtonModule.hpp>

#include "DoorBellAccessory/DoorBellAccessory.hpp"

class DoorBellAccessoryTest : public ::testing::Test
{
protected:
    uint32_t initialFreeHeap = 0; // Initial free heap size
    uint8_t buttonPin = 14;       // Pin assigned to the button

    // Components used in the test
    ButtonModule *button;
    DoorBellAccessory *doorBellAccessory;

    // Set up function to run before each test case
    void SetUp() override
    {
        delay(10);                                                  // Introduce a delay of 10ms to allow ESP32 to complete booting
        initialFreeHeap = ESP.getFreeHeap();                        // Record the initial free heap size
        button = new ButtonModule(buttonPin);                       // Create an instance of the ButtonModule
        doorBellAccessory = new DoorBellAccessory(button, nullptr); // Create an instance of the DoorBellAccessory
    }

    // Tear down function to run after each test case
    void TearDown() override
    {
        delete button;            // Delete the button instance
        delete doorBellAccessory; // Delete the DoorBellAccessory instance
        delay(10);                // Introduce a delay of 10ms to allow ESP32 to release resources
        if (ESP.getFreeHeap() != initialFreeHeap)
            FAIL() << "Memory leak of " << initialFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }
};

// Test Notification Callback
TEST_F(DoorBellAccessoryTest, NotificationCallback)
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
    doorBellAccessory->setNotifyCallback(mockCallback, pChar);

    // Simulate a single press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(150); // Wait for debounce
    digitalWrite(buttonPin, LOW);
    delay(150);

    delay(500); // Wait for the double press timeout

    // Check if the callback function changed the char to 'B'
    EXPECT_EQ(*pChar, 'B');

    // Delete the char pointer
    delete pChar;
};

// test max alloc free heap
TEST_F(DoorBellAccessoryTest, MaxAllocFreeHeap)
{
    void (*mockCallback)(void *) = [](void *pParameter) {
    };
    doorBellAccessory->setNotifyCallback(mockCallback, doorBellAccessory);

    // simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    delay(6000);
    int maxAllocFreeHeap = ESP.getMaxAllocHeap();
    for (int i = 0; i < 20; i++)
    {
        // simulate a button press
        pinMode(buttonPin, OUTPUT);
        digitalWrite(buttonPin, HIGH);
        delay(100);
        digitalWrite(buttonPin, LOW);
        delay(100);

        delay(6000);
    }
    EXPECT_EQ(ESP.getMaxAllocHeap(), maxAllocFreeHeap);
}

#endif // DOORBELL_ACCESSORY_TEST_HPP