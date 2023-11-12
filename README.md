# AccessoryModules Library

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/donate/?hosted_button_id=BACPRJTAU4G4E)
[![Latest](https://img.shields.io/github/v/tag/ronny-antoon/AccessoryModules?color=red&label=last+release)](https://github.com/ronny-antoon/AccessoryModules/releases)
[![Latest](https://badges.registry.platformio.org/packages/ronny-antoon/library/AccessoryModules.svg)](https://registry.platformio.org/libraries/ronny-antoon/AccessoryModules)
[![UnitTests](https://github.com/ronny-antoon/AccessoryModules/actions/workflows/build-and-test-embeded.yaml/badge.svg)](https://github.com/ronny-antoon/AccessoryModules/actions/workflows/build-and-test-embeded.yaml)

The AccessoryModules library provides a set of C++ classes for managing various accessory modules, such as fans, light bulbs, outlets, and switches. These modules are designed to be controlled using a combination of relay and button modules. The library is built with modularity in mind, allowing easy integration into different applications.

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

The library consists of several accessory modules, each encapsulated in a separate C++ class. The modules include:
- [FanAccessory](#fanaccessory)
- [LightBulbAccessory](#lightbulbaccessory)
- [OutletAccessory](#outletaccessory)
- [SwitchAccessory](#switchaccessory)

## Installation

**Method 1**:
To use the **AccessoryModules** library in your PlatformIO project, follow these steps:

1. Open "platformio.ini", a project configuration file located in the root of PlatformIO project.

2. Add the following line to the `lib_deps` option of `[env:]` section:
`ronny-antoon/AccessoryModules@^1.1.0`

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

Include the necessary header files in your project and use the provided classes according to your application requirements. Refer to the Classes section for details on each class.

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