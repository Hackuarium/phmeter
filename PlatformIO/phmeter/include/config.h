/**
 * @file config.h
 * @brief Define macros for run threads and configurations.
 * @version 0.1
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define MONITORING_LED 13 /**< Indication LED or test */

#define MAX_PARAM 52 /**< Maximum parameters to save in EEPROM */
#define PARAM_ERROR 24

//#define THR_MONITORING 1
// #define THR_SERIAL 1

// 08/21/2020
#define THR_I2C 1

// 06/01/2021
#define THR_PH_AND_CONDUCTIVITY

//#define THR_LCD


// 08/24/2020
// Enable Thread into WireMaster[.h,.cpp] into hack folder
//#define THR_WIRE_MASTER 1
// Enable Thread into WireM[.h,.cpp] src folder
//#define THR_WIRE_M 1