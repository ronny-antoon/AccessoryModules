#ifndef BASIC_ACCESSORY_INTERFACE_HPP
#define BASIC_ACCESSORY_INTERFACE_HPP

#include <MultiPrinterLoggerInterface.hpp>
#include <TaskTracker.hpp>

/**
 * @file BasicAccessoryInterface.hpp
 * @brief Defines the BasicAccessoryInterface class
 * @details Header file declaring the implementation of the BasicAccessoryInterface class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for basic accessories.
 *
 * @details This abstract class serves as an interface for basic accessories,
 * providing methods for setting callback functions for status change events.
 * The callback function will be called when the status of the basic accessory changes by the accessory itself.
 */
class BasicAccessoryInterface
{
private:
public:
    /**
     * @brief Virtual destructor for BasicAccessoryInterface.
     */
    virtual ~BasicAccessoryInterface() = default;

    /**
     * @brief Sets the callback function for notifying events.
     *
     * @param notifyCallback The callback function, taking a void pointer parameter.
     * @param callbackParameter The void pointer parameter for the callback function.
     */
    virtual void setNotifyCallback(void (*notifyCallback)(void *), void *callbackParameter) = 0;
};

static void checkWaterMArkAndPrint(MultiPrinterLoggerInterface *logger, TaskHandle_t taskHandle)
{
    int watermark = uxTaskGetStackHighWaterMark(taskHandle);
    if (watermark < 200)
    {
        Log_Error(logger, "Task %s has low stack watermark: %d", pcTaskGetName(taskHandle), watermark);
        return;
    }
    if (watermark < 500)
    {
        Log_Warning(logger, "Task %s has low stack watermark: %d", pcTaskGetName(taskHandle), watermark);
        return;
    }
}

#endif // BASIC_ACCESSORY_INTERFACE_HPP
