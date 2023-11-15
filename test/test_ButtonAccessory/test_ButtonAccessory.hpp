#ifndef BUTTON_ACCESSORY_TEST_HPP
#define BUTTON_ACCESSORY_TEST_HPP

#include <Arduino.h>
#include <gtest/gtest.h>

#include <ButtonModule.hpp>

#include "ButtonAccessory/ButtonAccessory.hpp"

// Test fixture for ButtonAccessory class
class ButtonAccessoryTest : public ::testing::Test
{
protected:
    uint32_t initialFreeHeap = 0; // Initial free heap size
    uint8_t buttonPin = 14;       // Pin assigned to the button

    // Components used in the test
    ButtonModule *button;
    ButtonAccessory *buttonAccessory;

    // Set up function to run before each test case
    void SetUp() override
    {
        delay(10);                                              // Introduce a delay of 10ms to allow ESP32 to complete booting
        initialFreeHeap = ESP.getFreeHeap();                    // Record the initial free heap size
        button = new ButtonModule(buttonPin);                   // Create an instance of the ButtonModule
        buttonAccessory = new ButtonAccessory(button, nullptr); // Create an instance of the ButtonAccessory
    }

    // Tear down function to run after each test case
    void TearDown() override
    {
        delete button;          // Delete the button instance
        delete buttonAccessory; // Delete the ButtonAccessory instance
        delay(10);              // Introduce a delay of 10ms to allow ESP32 to release resources
        if (ESP.getFreeHeap() != initialFreeHeap)
            FAIL() << "Memory leak of " << initialFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }
};

// Test case for checking the initial press type
TEST_F(ButtonAccessoryTest, InitialPressTypeIsSinglePress)
{
    // Ensure that the initial press type is set to SinglePress
    EXPECT_EQ(buttonAccessory->getLastPressEvent(), ButtonAccessory::PressType::SinglePress);
}

// Test case for simulating a single button press
TEST_F(ButtonAccessoryTest, SinglePress)
{
    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(150); // Wait for debounce
    digitalWrite(buttonPin, LOW);
    delay(150);

    delay(500); // Wait for the double press timeout
    EXPECT_EQ(buttonAccessory->getLastPressEvent(), ButtonAccessory::PressType::SinglePress);
}

// Test case for simulating a double button press
TEST_F(ButtonAccessoryTest, DoublePress)
{
    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(150); // Wait for debounce
    digitalWrite(buttonPin, LOW);
    delay(150);

    // Simulate another button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(150); // Wait for debounce
    digitalWrite(buttonPin, LOW);
    delay(150);

    delay(500); // Wait for the double press timeout
    EXPECT_EQ(buttonAccessory->getLastPressEvent(), ButtonAccessory::PressType::DoublePress);
}

// Test case for simulating a long button press
TEST_F(ButtonAccessoryTest, LongPress)
{
    // Simulate a long button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(1500); // Wait for debounce
    digitalWrite(buttonPin, LOW);
    delay(150);

    EXPECT_EQ(buttonAccessory->getLastPressEvent(), ButtonAccessory::PressType::LongPress);
}

// Test case for notifying the app callback on a single press
TEST_F(ButtonAccessoryTest, NotifyAppCallBack_SinglePress)
{
    // Mock callback function for single press
    void (*mockCallback)(void *) = [](void *pParameter)
    {
        ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
        EXPECT_EQ(thisPointer->getLastPressEvent(), ButtonAccessory::PressType::SinglePress);
    };

    // Set the callback function
    buttonAccessory->setNotifyCallback(mockCallback, buttonAccessory);

    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(150); // Wait for debounce
    digitalWrite(buttonPin, LOW);
    delay(150);

    delay(500); // Wait for the double press timeout
}

// Test case for notifying the app callback on a double press
TEST_F(ButtonAccessoryTest, NotifyAppCallBack_DoublePress)
{
    // Mock callback function for double press
    void (*mockCallback)(void *) = [](void *pParameter)
    {
        ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
        EXPECT_EQ(thisPointer->getLastPressEvent(), ButtonAccessory::PressType::DoublePress);
    };

    // Set the callback function
    buttonAccessory->setNotifyCallback(mockCallback, buttonAccessory);

    // Simulate a button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(150); // Wait for debounce
    digitalWrite(buttonPin, LOW);
    delay(150);

    // Simulate another button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(150); // Wait for debounce
    digitalWrite(buttonPin, LOW);
    delay(150);

    delay(500); // Wait for the double press timeout
}

// Test case for notifying the app callback on a long press
TEST_F(ButtonAccessoryTest, NotifyAppCallBack_LongPress)
{
    // Mock callback function for long press
    void (*mockCallback)(void *) = [](void *pParameter)
    {
        ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
        EXPECT_EQ(thisPointer->getLastPressEvent(), ButtonAccessory::PressType::LongPress);
    };

    // Set the callback function
    buttonAccessory->setNotifyCallback(mockCallback, buttonAccessory);

    // Simulate a long button press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(1500); // Wait for debounce
    digitalWrite(buttonPin, LOW);
    delay(150);

    delay(500); // Wait for the double press timeout
}

#endif // BUTTON_ACCESSORY_TEST_HPP
