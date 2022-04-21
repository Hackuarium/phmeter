# phmeter
Open source design of a battery powered pH meter

- LCD screen (2 lines) (8 pins).
- Rotary push button (3 pins).
- RJ-12 connector to a master.
- ATMEGA32U4.
- 64 Mbit memory ISP.
- 2 pumps.
- 4 I/O 12 V.
- Battery charge.

BOM
---
[iBOM](/pcb/main/bom/README.md)

## Cloning the project

In order to clone it use:

git clone --recurse-submodules https://github.com/Hackuarium/phmeter

To update the submodules:

git submodule update --recursive --remote

Last update: 04/08/2021


To Do
---
- Check I2C communication. (created branch _i2c_communication_ 04212022)
- Temperature sensors.
- Equation for pH.

