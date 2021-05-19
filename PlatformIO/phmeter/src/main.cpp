/**
 * @mainpage pHMeter Documentation
 *
 * @section description Description
 * Ths project is develop to control and adquire pH and conductimetry in
 * the principal project [Bioreactor](https://github.com/Hackuarium/bioreactor).
 * The source code documentation was made with Doxygen.
 *
 * @section circuit Circuit
 * - Microcontroller ATMEGA32U4.
 * - Buck converter from 5V and 12 V to 3.3 V.
 * - Battery charge.
 * - I2C communication.
 * - USB connection.
 * - Adquistion for pH.
 * - Adquisition for conductimetry.
 * - 24 bits ADC for pH and conductimetry.
 * - 4 I/O connections to control pH and conductimetry.
 * - One-wire communication.
 * - Temperature sense and control.
 * - 64 Mbits SPI memory.
 * - LCD 16x2 display.
 * - Rotary push button.
 * - Momentary push button connected to pin D3.
 *
 * @section libraries Libraries
 * - nilRTOS (https://github.com/greiman/NilRTOS-Arduino)
 *   - RTOS create threads for every component in the board.
 *
 * @section notes Notes
 * - Comments are Doxygen compatible.
 *
 * @section todo TODO
 * - Don't use Doxygen style formatting inside the body of a function.
 *
 * @section author Author
 * - Created by Andres Camilo Vargas on 04/08/2021.
 * - Modified by Andres Camilo Vargas on 05/12/2021.
 *
 * Copyright (c) 2021 Hackuarium.  All rights reserved.
 */

/**
 * @file  main.cpp
 * @brief This file is the firmware to run phMeter of Hackuarium.
 * 
 * @details This file start the NilRTOS threads for all components
 * associates to pH and Conductivity meter board of Hackuarium.
 * 
 * It uses the libraries and code of the bioreactor and simple-spectro
 * project to deploy new conigurations on PlatformIO.
 * 
 * @author Andres Camilo Vargas Román (andresc.vargasr@gmail.com)
 * @date  2021-04-08
 * @version 0.1 
 * @copyright Copyright &copy; 2021
 */

#include <Arduino.h>
// #include <NilRTOS.h>
#include <ChNil.h>
#include "config.h"

/**
 * The standard Arduino setup function used for setup and configuration tasks.
 */
void setup() {
  // put your setup code here, to run once:
  // nilSysBegin();
  // Start Nil RTOS.
  chBegin();
}

/**
 * The standard Arduino loop function used for repeating tasks.
 */
void loop() {
  // put your main code here, to run repeatedly:
}