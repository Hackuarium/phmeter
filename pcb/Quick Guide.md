HX711:
24-Bit Analog-to-Digital Converter (ADC) for Weigh Scales
===
Datasheet available on: [HX711 Datasheet](https://www.mouser.com/datasheet/2/813/hx711_english-1022875.pdf)

Pin Description
---
![Pin Description HX711](Images/pin_description-HX711.png)

| PIN # | NAME   | FUNCTION       |                               DESCRIPTION                                |
| ----- | ------ | -------------- | :----------------------------------------------------------------------: |
| 1     | VSUP   | Power          |                      Regulator supply: 2.7 ~ 5.5 V                       |
| 2     | BASE   | Analog Output  |               Regulator control output (NC when not used)                |
| 3     | AVDD   | Power          |                       Analog supply: 2.6  ~ 5.5 V                        |
| 4     | VFB    | Analog Input   |         Regulator control input (connect to AGND when not used)          |
| 5     | AGND   | Ground         |                              Analog ground                               |
| 6     | VBG    | Analog Output  |                         Reference bypass output                          |
| 7     | INA-   | Analog Input   |                         Channel A negative input                         |
| 8     | INA+   | Analog Input   |                         Channel A positive input                         |
| 9     | INB-   | Analog Input   |                         Channel B negative input                         |
| 10    | INB+   | Analog Input   |                         Channel B positive input                         |
| 11    | PD_SCK | Digital Input  | Power down control (high active) and serial clock and serial clock input |
| 12    | DOUT   | Digital Output |                            Serial data output                            |
| 13    | XO     | Digital I/O    |                      Crystal I/O (NC when not used)                      |
| 14    | XI     | Digital Input  |      Crystal I/O or external clock input, 0: use on-chip oscillator      |
| 15    | RATE   | Digital Input  |               Output data rate control, 0: 10 Hz; 1: 80 Hz               |
| 16    | DVDD   | Power          |                       Digital supply: 2.6 ~ 5.5 V                        |

Analog Inputs
---

### Channel A
It can be programmed with a gain of 128 or 64. When 5V supply is used at the AVDD pin, these gains correspond to a full-scale differential input voltage of &plusmn; 20 mV or &plusmn; 40 mV respectively.

**(For 3.3 AVDD the range is near to &plusmn; 13 mV and &plusmn; 26 mV respectively).**

### Channel B
It has a fixed gain of 32. The full-scale input voltage range is &plusmn; 80 mV, when 5V suppl is used at the AVV pin.

**(For 3.3 AVDD the range is near to &plusmn; 52 mV).**

Power Supply Options
---
DVDD should be the same power supply as the MCU power supply.

If the on-chip analog supply regulator is not used, the VSUP pin should be connected to either AVDD or DVDD. depending on which voltage is higher. Pin VFB should be connected to Ground and pin BASE becomes NC. The external 0.1 &micro;F bypass capacitor at the VBG output pin is then not needed.

**(VSUP is connect to DVDD, VFB to ground, VGB and BASE is NC).**


