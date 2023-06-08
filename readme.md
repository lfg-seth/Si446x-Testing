# Arduino SI4464 Transceiver Test

This project involves using two Arduino boards to test the SI4464 transceiver IC from Silicon Labs. Each Arduino board will be connected to a separate transceiver over SPI.

The goal is to have a message typed into the console of the computer connected to the transmitting Arduino, have it be sent over to the receiving Arduino, and read out over the console of the receiving Arduino's connected computer.

## Hardware Requirements

- Two Arduino UNO boards (or compatible)
- Two SI4464 transceiver ICs
- Necessary wiring for SPI connections and IRQ pin
- Two computers to interface with each Arduino

## Software Requirements

- Arduino IDE
- Serial Terminal on both computers (often built into the Arduino IDE)
- [Wireless Development Suite](https://www.silabs.com/documents/login/software/WDS3-Setup.exe) (Official Version)

## Wireless Development Suite
This software was found by searching "Wireless Development Suite on [silabs.com](silabs.com) and clicking on the first link.
It does require that you be signed in to download, but an account can be made with no requirements. 
Once signed in, the download will start.
This is the software used to create radio_config.h.  
As of now this isn't used, and the config is just set manually to use the packet handler in the default setup. But this can be used to create different configurations.

More info can be found in [AN633 Programming Guide and Sample Code](Docs/AN625%20Si446x%20API%20Descriptions.pdf) page 19

## Pin Connections

For both Arduino boards, we will use the following connections:
- SCK: 13
- MISO: 12
- MOSI: 11
- SS: 10
- IRQ: 2

These can be changed in the `Transceiver.h` file.

## Instructions

1. Wire up your Arduino boards to the SI4464 transceivers following the pin connections above.

2. Open the Arduino IDE on each computer and load the main.ino sketch onto each Arduino board.

3. Open the Serial Monitor on each computer (usually found in the Arduino IDE).

4. On the transmitting computer, type a message into the Serial Monitor and hit send.

5. The receiving Arduino should receive the message and it should be displayed on the receiving computer's Serial Monitor.

Note: The current version of the code is only a boilerplate and requires specific SPI commands from the SI4464 datasheet to interact with the SI4464 transceivers. Please modify the `Transceiver.cpp` file with the specific SPI commands to send and receive data.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
MIT License

Copyright (c) 2023 Seth Smith

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.