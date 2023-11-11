#ifndef FA_MODULE_HPP
#define FA_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "FanModuleInterface.hpp"
#include "OnOffBasicModule.hpp"

/**
 * @file FanModule.hpp
 * @brief Defines the FanModule class
 * @details Header file declaring the implementation of the FanModule class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the FanModule class.
 *
 * @details The FanModule class is responsible for managing fan modules,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the fan module by button trigger, it will call the callback function to notify the app.
 */

class FanModule : public OnOffBasicModule, public FanModuleInterface
{
public:
    /**
     * @brief
     *
     * @param relayModule
     * @param buttonModule
     */
    FanModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief
     *
     */
    ~FanModule() override;
};

#endif // FA_MODULE_HPP