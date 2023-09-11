# Intelligent-Door-System
It is a standalone door system with security and customisation of settings, designed with ARM LPC2148 Micro controller and peripherals.

It was our project for Productathon event held in CSE dept. for MCES (Microcontrollers and Embedded Systems) subject with 6hrs duration.

Components involved:

1. LPC2148 Microcontroller.
2. Proximity Sensor
3. Stepper Motor (For door simulation)
4. 7-Seg Display
5. 4x4 Matrix Keyboard for character input.
6. Push buttons for operation

The ports to which diffeent components are connected is specified in code.

We need ARMKeil UVision IDE to work with these files, its an Embedded C code.

In settings, we have to enable use microLib, create Hex file.

Then we need flashmagic to load this hex file into the ROM of microcontroller, operating at 9600 Baud Rate and specific COM channel, and then put the microcontroller into Programming mode to install the files and Reset to start operation.

