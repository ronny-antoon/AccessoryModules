# AccessoryModules Library

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/donate/?hosted_button_id=BACPRJTAU4G4E)
[![Latest](https://img.shields.io/github/v/tag/ronny-antoon/AccessoryModules?color=red&label=last+release)](https://github.com/ronny-antoon/AccessoryModules/releases)
[![Latest](https://badges.registry.platformio.org/packages/ronny-antoon/library/AccessoryModules.svg)](https://registry.platformio.org/libraries/ronny-antoon/AccessoryModules)
[![UnitTests](https://github.com/ronny-antoon/AccessoryModules/actions/workflows/build-and-test-embeded.yaml/badge.svg)](https://github.com/ronny-antoon/AccessoryModules/actions/workflows/build-and-test-embeded.yaml)

The AccessoryModules Library provides a collection of C++ classes representing various smart home accessories. These accessories include blinds, boilers, buttons, doorbells, door locks, fans, light bulbs, outlets, and switches. The library aims to simplify the development of applications for controlling and monitoring these devices in a smart home environment.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Dependency](#dependency)
- [Usage](#usage)
- [API](#API)
- [Example](#example)
- [License](#license)
- [Contributions](#contributions)
- [Platformio Registry](#platformio-registry)

## Introduction

The AccessoryModules Library simplifies the management of various accessory modules in ESP32/Arduino projects. It provides abstract interfaces for controlling accessory states, offering methods for turning on/off, toggling, and checking the current state and more as more accessories will added.
These modules are designed to be controlled through a relay module and a button module, with the flexibility to trigger status changes either through user input or app commands.

## Features

The library consists of several accessory modules, each encapsulated in a separate C++ class.
The library currently supports the following accessories:
- [Fan Accessory](https://github.com/ronny-antoon/AccessoryModules/blob/main/include/FanAccessory.hpp)
- [Light Bulb Accessory](https://github.com/ronny-antoon/AccessoryModules/blob/main/include/LightBulbAccessory.hpp)
- [Outlet Accessory](https://github.com/ronny-antoon/AccessoryModules/blob/main/include/OutletAccessory.hpp)
- [Switch Accessory](https://github.com/ronny-antoon/AccessoryModules/blob/main/include/SwitchAccessory.hpp)
- [Button Accessory](https://github.com/ronny-antoon/AccessoryModules/blob/main/include/ButtonAccessory.hpp)
- [Blind Accessory](https://github.com/ronny-antoon/AccessoryModules/blob/main/include/BlindAccessory.hpp)
- [Boiler Accessory](https://github.com/ronny-antoon/AccessoryModules/blob/main/include/BoilerAccessory.hpp)
- [Doorbell Accessory](https://github.com/ronny-antoon/AccessoryModules/blob/main/include/DoorbellAccessory.hpp)
- [Door Lock Accessory](https://github.com/ronny-antoon/AccessoryModules/blob/main/include/DoorLockAccessory.hpp)
Each accessory class extends a common interface, providing consistency in usage.

## Installation

**Method 1**:
To use the **AccessoryModules** library in your PlatformIO project, follow these steps:

1. Open "platformio.ini", a project configuration file located in the root of PlatformIO project.

2. Add the following line to the `lib_deps` option of `[env:]` section:
`ronny-antoon/AccessoryModules@^3.0.5`

3. Build a project, PlatformIO will automatically install dependencies.

**Method 2**:
To use the **AccessoryModules** library in your Arduino project, follow these steps:

1. Download the latest release from the [GitHub repository](https://github.com/ronny-antoon/AccessoryModules).

2. In the Arduino IDE, click "Sketch" -> "Include Library" -> "Add .ZIP Library" and select the downloaded `.zip` file.

3. Make sure to link your project with the necessary ESP-IDF libraries for NVS support.

## Dependency

The library depends on the following libraries:
- [ButtonModule](https://github.com/ronny-antoon/ButtonModule).
- [RelayModule](https://github.com/ronny-antoon/RelayModule).
- [MultiPrinterLogger](https://github.com/ronny-antoon/MultiPrinterLogger).

## Usage

Include the appropriate header file for the accessory you want to use in your project. Each accessory class is designed to provide a set of methods for controlling and monitoring the corresponding device. Refer to the Classes section for details on each class.

## API

The AccessoryModules Library provides abstract interfaces and implementations for different accessory modules. For detailed documentation and usage examples, refer to the header files in the source code.

## Example

Explore example sketches for each accessory module in the "examples" directory.

## License

This library is provided under the MIT License. You are free to use, modify, and distribute it as needed.

## Contributions

If you'd like to contribute to the Library, please follow these guidelines:
1. Fork the repository.
2. Make your changes and document them.
3. Submit a pull request.

## Author

This library was created by Ronny Antoon. You can contact me at [ronny.antoon@gmail.com] for any questions or feedback.

## Platformio Registry

https://registry.platformio.org/libraries/ronny-antoon/AccessoryModules