#include <Arduino.h>
#include <ChNil.h>

#include "Funcs.h"
#include "sleep.h"
#include "Utility.h"

#include "acquire.h"

#define LANGUAGE 'es'

// https://docs.google.com/spreadsheets/d/1oek6pKHUvD7NI2u9-_iEOfVL-NeUmnj1pZCFRRo7n_4/edit?usp=sharing

#if LANGUAGE == 'en'
#define TEXT_ABSORBANCE "Absorb."
#define TEXT_FLUORESCENCE "Fluor."
#define TEXT_WAITING_BLANK "Waiting blank"
#define TEXT_WAITING_EXP "Waiting exp."
#define TEXT_ACQUIRING "Acquiring"
#define TEXT_BLANK "Blank"
#define TEXT_SAMPLE "Sample"
#define TEXT_SEQUENCE "Sequence"
#define TEXT_KINETIC "Kinetic"
#define TEXT_STOP "Stop acquis."
#define TEXT_ACQUIRE "Acquire"
#define TEXT_ACQ_SEQUENCE "Acq. sequence"
#define TEXT_CONT_SEQUENCE "Continue seq."
#define TEXT_ACQ_KINETIC "Acq. kinetic"
#define TEXT_CONT_KINETC "Continue kin."
#define TEXT_RESULTS "Results"
#define TEXT_SETTINGS "Settings"
#define TEXT_STATUS "Status"
#define TEXT_UTILITIES "Utilities"
#define TEXT_SLEEP "Sleep"
#define TEXT_TEST_PROBES "Test Probes"
#define TEXT_RESET "Reset"
#define TEXT_REBOOT "Reboot"
#define TEXT_MAIN_MENU "Main menu"
#define TEXT_RED "Red"
#define TEXT_GREEN "Green"
#define TEXT_BLUE "Blue"
#define TEXT_UV1 "UV"
#define TEXT_UV2 "UV 2"
#define TEXT_BEFORE_DELAY "Before delay"
#define TEXT_FIRST_DELAY "First delay"
#define TEXT_INTER_DELAY "Inter exp. delay"
#define TEXT_NUMBER_EXP "Number exp."
#define TEXT_RESULT_COLOR "Result color"
#define TEXT_PRESS_NEXT "Press for next"
#endif

#if LANGUAGE == 'es'
#define TEXT_ABSORBANCE "Absorb."
#define TEXT_FLUORESCENCE "Fluor."
#define TEXT_WAITING_BLANK "Esperando blanco"
#define TEXT_WAITING_EXP "Esperando exp."
#define TEXT_ACQUIRING "Adquiriendo"
#define TEXT_BLANK "Blanco"
#define TEXT_SAMPLE "Muestra"
#define TEXT_SEQUENCE "Secuencia"
#define TEXT_KINETIC "Cinetica"
#define TEXT_STOP "Detener"
#define TEXT_ACQUIRE "Adquirir"
#define TEXT_ACQ_SEQUENCE "Adq. secuencia"
#define TEXT_CONT_SEQUENCE "Continuar sec."
#define TEXT_ACQ_KINETIC "Adq. Cinetica"
#define TEXT_CONT_KINETC "Continuar Cin."
#define TEXT_RESULTS "Resultados"
#define TEXT_SETTINGS "Ajustes"
#define TEXT_STATUS "Estado"
#define TEXT_UTILITIES "Utilidades"
#define TEXT_SLEEP "Dormir"
#define TEXT_TEST_PROBES "Prueba sondas"
#define TEXT_RESET "Reiniciar"
#define TEXT_REBOOT "Reiniciar"
#define TEXT_MAIN_MENU "Menu"
#define TEXT_RED "Rojo"
#define TEXT_GREEN "Verde"
#define TEXT_BLUE "Azul"
#define TEXT_UV1 "UV"
#define TEXT_BEFORE_DELAY "Tiempo inicio"
#define TEXT_FIRST_DELAY "Primera pausa"
#define TEXT_INTER_DELAY "Tiempo entre exp"
#define TEXT_NUMBER_EXP "Numero de exp"
#define TEXT_RESULT_COLOR "Color"
#define TEXT_PRESS_NEXT "Press for next"
#endif

#include <LiquidCrystal.h>

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


#include "Rotary.h"

// Rotary encoder is wired with the common to ground and the two
// outputs to pins 2 and 3.
Rotary rotary = Rotary(ROT_A, ROT_B);

int noEventCounter = 0;
byte previousMenu = 0;

/* Declaring a function pointer called reboot that points to address 0. */
// void(* reboot) (void) = 0;

uint8_t ALL_PARAMETERS[TOTAL_PARAMETERS] = {PH_DOUT, EC, TEMP_EXT1, TEMP_EXT2, BATTERY_LEVEL};  // all possible reading values
uint8_t ACTIVE_PARAMETERS[TOTAL_PARAMETERS];
// Old variables from spectro - 20220701
// Used in acquire.h->setActiveProbes()
uint8_t nbProbes = 2;              // number of active leds
uint8_t nbParameters = sizeof(ALL_PARAMETERS);        // number of parameters to record
uint8_t dataRowSize = nbParameters + 1;         // size of a data row (number of entries in data)
uint8_t maxNbRows = DATA_SIZE / dataRowSize;           // calculate value depending the size of EEPROM dedicated to logs


bool rotaryPressed = false;
int rotaryCounter = 0;
bool captureCounter = false;  // use when you need to setup a parameter from the menu
bool rotaryMayPress = true;  // be sure to go through release. Seems to allow some deboucing

uint8_t accelerationMode = 0;
int lastIncrement = 0;
unsigned long lastRotaryEvent = millis();

/**
 * If the rotary encoder is turned, then increment the rotaryCounter variable by 1
 * or -1, depending on the direction of the turn
 * 
 * @return The rotary encoder is being read and the direction of rotation is being
 * determined.
 */
void rotate() {
  int increment = 0;

  byte direction = rotary.process();
  if (direction == DIR_CW) {
    increment = -1;
  } else if (direction == DIR_CCW) {
    increment = 1;
  }

  if (increment == 0)
    return;

  long unsigned current = millis();
  long unsigned diff = current - lastRotaryEvent;
  lastRotaryEvent = current;

  if (diff < 50) {
    accelerationMode++;
    if (accelerationMode < 5)
      return;
    if (accelerationMode > 20)
      accelerationMode = 20;
  } else {
    accelerationMode = 0;
  }

  if (getParameterBit(PARAM_FLAGS, PARAM_FLAG_INVERT_ROTARY) == 1) {
    increment *= -1;
  }

  if (accelerationMode > 4) {
    rotaryCounter += (increment * accelerationMode);
  } else {
    if (accelerationMode == 0) {
      rotaryCounter += increment;
    }
  }
}

void eventRotaryPressed() {
  cli();
  byte state = digitalRead(ROT_PUSH);
  long unsigned eventMillis = millis();
  if (state == 0) {
    if (rotaryMayPress && ((eventMillis - lastRotaryEvent) > 200)) {
      rotaryPressed = true;
      rotaryMayPress = false;
      lastRotaryEvent = eventMillis;
    }
  } else {
    rotaryMayPress = true;
    if ((eventMillis - lastRotaryEvent) > 5000) {
      resetParameters();
      reboot();
    }
  }
  sei();
}

void setupRotary() {
  attachInterrupt(digitalPinToInterrupt(ROT_A), rotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROT_B), rotate, CHANGE);
  pinMode(ROT_PUSH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROT_PUSH), eventRotaryPressed, CHANGE);
}

void updateCurrentMenu(int counter, uint8_t maxValue, uint8_t modulo) {
  byte currentMenu = getParameter(PARAM_MENU);
  if (captureCounter)
    return;
  if (counter < 0) {
    setParameter(PARAM_MENU, currentMenu + max(counter, -currentMenu % modulo));
  } else if (counter > 0) {
    setParameter(PARAM_MENU,
                 currentMenu + min(counter, maxValue - currentMenu % modulo));
  }
}

void updateCurrentMenu(int counter, uint8_t maxValue) {
  updateCurrentMenu(counter, maxValue, 10);
}

/**
 * It prints the current menu line and a dot to the LCD
 * 
 * @param line the line number of the LCD display (0 or 1)
 */
void lcdNumberLine(uint8_t line) {
  lcd.print(getParameter(PARAM_MENU) % 10 + line + 1);
  if (line == 0) {
    lcd.print(".*");
  } else {
    lcd.print(". ");
  }
}

void lcdMenuHome(int counter, bool doAction) {
  if (noEventCounter > 2)
    return;
  lcd.clear();
  // Define number of options in the Menu
  byte lastMenu = 6;
  updateCurrentMenu(counter, lastMenu);

  for (byte line = 0; line < LCD_NB_ROWS; line++) {
    lcd.setCursor(0, line);
    if (getParameter(PARAM_MENU) % 10 + line <= lastMenu)
      lcdNumberLine(line);

    switch (getParameter(PARAM_MENU) % 10 + line) {
      // 1st option (default)
      case 0:
        /* Checking if the next exposure is greater than or equal to 0. If it is,
        it prints "STOP" on the LCD. If the doAction is true, it sets the next
        exposure to -1, the status to 0, and the menu to 100. If the next
        exposure is not greater than or equal to 0, it prints "ACQUIRE" on the
        LCD. If the doAction is true, it sets the status to STATUS_ONE_SPECTRUM
        and the next exposure to 0. */
        if (getParameter(PARAM_NEXT_EXP) >= 0) {
          lcd.print(F(TEXT_STOP));
          if (doAction) {
            setParameter(PARAM_NEXT_EXP, -1);
            setParameter(PARAM_STATUS, 0);
            setParameter(PARAM_MENU, 100);
          }
        } else {
          lcd.print(F(TEXT_ACQUIRE));
          if (doAction) {
            setParameter(PARAM_STATUS, STATUS_ONE_SPECTRUM);
            setParameter(PARAM_NEXT_EXP, 0);
          }
        }
        break;
      case 1:
        if ((getParameter(PARAM_NEXT_EXP) >= 0) &&
            (getParameter(PARAM_STATUS) ==
             STATUS_SEQUENCE)) {  // continue acquisition
          lcd.print(F(TEXT_CONT_SEQUENCE));
          if (doAction) {
            // Check for pH or EC - 20220701
            // setAcquisitionMenu();
          }
        } else {
          lcd.print(F(TEXT_ACQ_SEQUENCE));
          if (doAction) {
            setParameter(PARAM_STATUS, STATUS_SEQUENCE);
            setParameter(PARAM_NEXT_EXP, 0);
          }
        }
        break;
      case 2:
        if ((getParameter(PARAM_NEXT_EXP) >= 0) &&
            (getParameter(PARAM_STATUS) ==
             STATUS_KINETIC)) {  // continue acquisition
          lcd.print(F(TEXT_CONT_KINETC));
          if (doAction) {
            // Check for pH or EC - 20220701
            // setAcquisitionMenu();
          }
        } else {
          lcd.print(F(TEXT_ACQ_KINETIC));
          if (doAction) {
            setParameter(PARAM_STATUS, STATUS_KINETIC);
            setParameter(PARAM_NEXT_EXP, 0);
          }
        }
        break;
      case 3:
        lcd.print(F(TEXT_RESULTS));
        if (doAction) {
          setParameter(PARAM_MENU, 100);
        }
        break;
      case 4:
        lcd.print(F(TEXT_SETTINGS));
        if (doAction) {
          setParameter(PARAM_MENU, 10);
        }
        break;
      case 5:
        lcd.print(F(TEXT_STATUS));
        if (doAction) {
          setParameter(PARAM_MENU, 20);
        }
        break;
      case 6:
        lcd.print(F(TEXT_UTILITIES));
        if (doAction) {
          setParameter(PARAM_MENU, 40);
        }
        break;
    }
    doAction = false;
  }
}

void lcdMenuSettings(int counter, boolean doAction) {
  byte lastMenu = 8;
  if (!captureCounter)
    updateCurrentMenu(counter, lastMenu);

  byte currentParameter = 0;
  int8_t currentParameterBit = -1;
  float currentFactor = 1;
  char currentUnit[5] = "\0";
  int maxValue = 32767;
  int minValue = -32768;

  lcd.clear();

  switch (getParameter(PARAM_MENU) % 10) {
    case 0:
      lcd.print(F(TEXT_BEFORE_DELAY));
      currentParameter = PARAM_BEFORE_DELAY;
      minValue = 0;
      strcpy(currentUnit, "s\0");
      break;
    case 1:
      lcd.print(F(TEXT_FIRST_DELAY));
      currentParameter = PARAM_FIRST_DELAY;
      minValue = 0;
      strcpy(currentUnit, "s\0");
      break;
    case 2:
      lcd.print(F(TEXT_INTER_DELAY));
      currentParameter = PARAM_INTER_DELAY;
      minValue = 0;
      strcpy(currentUnit, "s\0");
      break;
    case 3:
      lcd.print(F(TEXT_NUMBER_EXP));
      currentParameter = PARAM_NUMPER_EXP;
      minValue = 1;
      maxValue = maxNbRows;
      break;
    case 4:
      lcd.print(F(TEXT_RESULT_COLOR));
      currentParameter = PARAM_COLOR;
      minValue = 1;
      maxValue = nbParameters;
      break;
    case 5:
      lcd.print(F("Raw values"));
      currentParameter = PARAM_FLAGS;
      currentParameterBit = PARAM_FLAG_RAW_VALUES;
      minValue = 0;
      maxValue = 1;
      break;
    case 6:
      lcd.print(F("Active leds"));
      currentParameter = PARAM_ACTIVE_PROBES;
      minValue = 0;
      maxValue = pow(2, sizeof(ALL_PARAMETERS)) - 1;
      break;
    case 7:
      lcd.print(F("Rotary inverse"));
      currentParameter = PARAM_FLAGS;
      currentParameterBit = PARAM_FLAG_INVERT_ROTARY;
      minValue = 0;
      maxValue = 1;
      break;
    case 8:
      lcd.print(F(TEXT_MAIN_MENU));
      if (doAction) {
        setParameter(PARAM_MENU, 1);
      }
      return;
  }

  if (doAction) {
    captureCounter = !captureCounter;
    if (!captureCounter) {
      setAndSaveParameter(currentParameter, getParameter(currentParameter));
    }
  }
  if (captureCounter) {
    if (currentParameterBit == -1) {
      int newValue = getParameter(currentParameter) + counter;
      setParameter(currentParameter, max(min(maxValue, newValue), minValue));
    } else {  // flag kind so either true or false
      if (counter > 0) {
        setParameterBit(currentParameter, currentParameterBit);
      } else if (counter < 0) {
        clearParameterBit(currentParameter, currentParameterBit);
      }
    }
  }

  lcd.setCursor(0, 1);
  if (millis() % 1000 < 500 && captureCounter) {
    lcd.print((char)255);
  } else {
    lcd.print(" ");
  }
  switch (getParameter(PARAM_MENU) % 10) {
    case 4:
      // Check for pH or EC - 20220701
      // printColor(&lcd, ACTIVE_PARAMETERS[getParameter(currentParameter) - 1]);
      break;
    case 6:  // active leds
      lcd.print((getParameter(currentParameter)));
      lcd.print(" ");
      setActiveProbes();
      for (byte i = 0; i < nbParameters; i++) {
        // Check for pH or EC - 20220701
        // printColorOne(&lcd, ACTIVE_PARAMETERS[i]);
        lcd.print(" ");
      }
      break;
    default:
      if (currentParameterBit == -1) {
        if (currentFactor == 1) {
          lcd.print((getParameter(currentParameter)));
        } else {
          lcd.print(((float)getParameter(currentParameter)) * currentFactor);
        }
      } else {  // it is a flag so we need to display true or false
        if (getParameterBit(currentParameter, currentParameterBit)) {
          lcd.print("true");
        } else {
          lcd.print("false");
        }
      }
      lcd.print(" ");
      lcd.print(currentUnit);
  }
}

void lcdPrintBlank(byte number) {
  for (byte i = 0; i < number; i++) {
    lcd.print(" ");
  }
}

void lcdStatus(int counter, boolean doAction) {
  if (doAction)
    setParameter(PARAM_MENU, 0);
  updateCurrentMenu(counter, nbProbes);
  if (noEventCounter < 2)
    lcd.clear();
  byte menu = getParameter(PARAM_MENU) % 10;
  if (menu < nbProbes) {
    lcd.setCursor(0, 0);
    // Check for pH or EC - 20220701
    // printColor(&lcd, ACTIVE_PARAMETERS[menu]);
    lcd.setCursor(0, 1);

    if (getParameter(menu + 5) == INT_MAX_VALUE ||
        getParameter(menu) == INT_MAX_VALUE) {
      lcd.print(F("OVER"));
    } else {
      if (menu < 3) {
        lcd.print(F(TEXT_ABSORBANCE));
        lcd.setCursor(8, 1);
        lcd.print(
            log10((double)getParameter(menu + 5) / (double)getParameter(menu)));
      } else {
        lcd.print(F(TEXT_FLUORESCENCE));
        lcd.setCursor(8, 1);
        lcd.print(getParameter(menu) - getParameter(menu + 5));
      }
    }
    lcdPrintBlank(2);
  } else {
    lcd.setCursor(0, 0);
#ifdef TEMPERATURE_ADDRESS
    lcd.print("T:");
    lcd.print(((float)getParameter(PARAM_TEMPERATURE)) / 100, 1);
    lcd.print("\xDF\x43");
#endif
#ifdef BATTERY
    lcd.print(F(" B:"));
    lcd.print(((float)getParameter(PARAM_BATTERY)) / 1000);

#ifdef BATTERY_CHARGING
    if (getParameter(PARAM_CHARGING) > 1000) {
      lcd.print("~");
    } else if (getParameter(PARAM_CHARGING) > 500) {
      lcd.print("+");
    } else {
      lcd.print("-");
    }

#else
    lcd.print("V");
#endif
#endif
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
    lcd.print("s");
    lcd.setCursor(7, 1);
    lcd.print(F(SOFTWARE_VERSION));
  }
}

void lcdWait() {
  lcd.setCursor(0, 1);
  if (getParameter(PARAM_STATUS) ==
      STATUS_SEQUENCE) {  // need to press enter for next acquisition
    lcd.print(F(TEXT_PRESS_NEXT));
  } else {
    lcd.print(getParameter(PARAM_WAIT));
    lcd.print(" s ");
  }
}

void lcdAcquisition(int counter, boolean doAction) {
  byte menu = getParameter(PARAM_MENU) % 10;
  // if it is a sequence we should go to menu only if in an acquisition
  if (counter) {  // the button was turned
    setParameter(PARAM_MENU, 0);
  }
  if (doAction) {     // the button was pressed
    if (menu == 3) {  // test sequence
      setParameter(PARAM_MENU, 0);
      setParameter(PARAM_NEXT_EXP, -1);
      setParameter(PARAM_STATUS, 0);
    } else if (menu == 2 || getParameter(PARAM_STATUS) != STATUS_SEQUENCE) {
      setParameter(PARAM_MENU, 0);
    } else {  // next experiment, it is a manual sequence
      setParameter(PARAM_WAIT, 0);
    }
  }
  if (noEventCounter < 2)
    lcd.clear();
  switch (menu) {
    case 0:  // waiting for blank
      lcd.setCursor(0, 0);
      lcd.print(F(TEXT_WAITING_BLANK));
      lcdWait();
      break;
    case 1:  // waiting for acquisition
      lcd.setCursor(0, 0);
      lcd.print(F(TEXT_WAITING_EXP));
      lcd.print(getParameter(PARAM_NEXT_EXP));
      lcdWait();
      break;
    case 2:  // acquiring
      lcd.setCursor(0, 0);
      lcd.print(F(TEXT_ACQUIRING));
      lcd.setCursor(0, 1);
      if (getParameter(PARAM_NEXT_EXP) == 0) {
        lcd.print(F(TEXT_BLANK));
      } else if (getParameter(PARAM_NEXT_EXP) == 1) {
        lcd.print(F(TEXT_SAMPLE));
      } else if (getParameter(PARAM_NEXT_EXP) > 1) {
        if (getParameter(PARAM_STATUS) == STATUS_SEQUENCE) {
          lcd.print(F(TEXT_KINETIC));
        } else {
          lcd.print(F(TEXT_SEQUENCE));
        }
        lcdPrintBlank(1);
        lcd.print(getParameter(PARAM_NEXT_EXP));
      }
      break;
    case 3:  // TEST mode
      lcd.setCursor(0, 0);
      lcd.print("pH:");
      // Check EEPROMLogger - 20220701
      // lcd.print(getDataLong(1));
      lcd.print((float)getParameter(PARAM_PH)/100.0);
      lcdPrintBlank(6);
      lcd.setCursor(8, 0);
      lcd.print("T1:");
      // Check EEPROMLogger - 20220701
      // lcd.print(getDataLong(2));
      lcd.print((float)getParameter(PARAM_TEMP_EXT1)/100.0);
      lcdPrintBlank(6);
      lcd.setCursor(0, 1);
      lcd.print("EC:");
      // Check EEPROMLogger - 20220701
      // lcd.print(getDataLong(3));
      lcd.print((float)getParameter(PARAM_EC));
      // lcd.print("Data 3L EEPROM");
      lcdPrintBlank(6);
      lcd.setCursor(8, 2);
      lcd.print("T2:");
      // Check EEPROMLogger - 20220701
      // lcd.print(getDataLong(4));
      lcd.print((float)getParameter(PARAM_TEMP_EXT2)/100.0);
      lcdPrintBlank(6);
  }
}

void lcdUtilities(int counter, boolean doAction) {
  if (noEventCounter > 2)
    return;
  lcd.clear();
  byte lastMenu = 4;
  updateCurrentMenu(counter, lastMenu);

  for (byte line = 0; line < LCD_NB_ROWS; line++) {
    lcd.setCursor(0, line);
    if (getParameter(PARAM_MENU) % 10 + line <= lastMenu)
      lcdNumberLine(line);

    switch (getParameter(PARAM_MENU) % 10 + line) {
      case 0:
        lcd.print(F(TEXT_SLEEP));
        if (doAction) {
          sleepNow();
        }
        break;
      case 1:
        if (getParameter(PARAM_STATUS) == STATUS_TEST_PROBES) {
          lcd.print(F("Stop test"));
          setParameter(PARAM_MENU, 33);
          if (doAction) {
            setParameter(PARAM_STATUS, 0);
          }
        } else {
          lcd.print(F(TEXT_TEST_PROBES));
          if (doAction) {
            setParameter(PARAM_STATUS, STATUS_TEST_PROBES);
          }
        }

        break;
      case 2:
        lcd.print(F(TEXT_RESET));
        if (doAction) {
          resetParameters();
          setParameter(PARAM_MENU, 20);
        }
        break;
      case 3:
        lcd.print(F(TEXT_REBOOT));
        if (doAction) {
          reboot();
        }
        break;

      case 4:
        lcd.print(F(TEXT_MAIN_MENU));
        if (doAction) {
          setParameter(PARAM_MENU, 1);
        }
        return;
    }
    doAction = false;
  }
}

void lcdResults(int counter, boolean doAction) {
  if (doAction)
    setParameter(PARAM_MENU, 0);
  if (noEventCounter < 2)
    lcd.clear();

  // calculate the last experiment based on epoch of each experiment
  byte lastExperiment = 1;
  // Check EEPROMLogger - 20220701
  // long dataZero = getDataLong(0);
  long dataZero = 0L;
  for (lastExperiment; lastExperiment < maxNbRows; lastExperiment++) {
    // Check EEPROMLogger - 20220701
    // if (getDataLong(lastExperiment * dataRowSize) <= dataZero)
    if (0L <= dataZero)
      break;
  }

  updateCurrentMenu(counter, lastExperiment - 1, 50);
  int start = getParameter(PARAM_MENU) % 50 - 1;
  boolean header = start == -1;
  if (!getParameterBit(PARAM_FLAGS, PARAM_FLAG_RAW_VALUES))
    start++;  // we add one it we don't show blank
  for (int i = start; i < min(lastExperiment, start + LCD_NB_ROWS); i++) {
    lcd.setCursor(0, i - start);
    if (header) {
      // Check for pH or EC - 20220701
      // printColor(&lcd, getParameter(PARAM_COLOR) - 1);
      header = false;
    } else {
      lcd.print(i);
      lcd.print(" ");
      if (getParameterBit(PARAM_FLAGS, PARAM_FLAG_RAW_VALUES)) {
        // Check EEPROMLogger - 20220701
        // lcd.print((getDataLong(i * dataRowSize) - getDataLong(0)) / 1000);
        lcd.print((i * dataRowSize - 0) / 1000);
        lcd.print(" ");
      }
      if (getParameterBit(PARAM_FLAGS, PARAM_FLAG_RAW_VALUES) == 1) {
        // Check EEPROMLogger - 20220701
        // lcd.print(getDataLong(i * dataRowSize + getParameter(PARAM_COLOR)));
        lcd.print(i * dataRowSize + getParameter(PARAM_COLOR));
      } else {
        // Check EEPROMLogger - 20220701
        // if (getDataLong(getParameter(PARAM_COLOR)) == LONG_MAX_VALUE || getDataLong(i * dataRowSize + getParameter(PARAM_COLOR)) == LONG_MAX_VALUE) {
        if (getParameter(PARAM_COLOR) == LONG_MAX_VALUE || i * dataRowSize + getParameter(PARAM_COLOR) == LONG_MAX_VALUE) {
          lcd.print(F("OVER"));
        } else {
          if (getParameter(PARAM_COLOR) < 4) {
            // Check EEPROMLogger - 20220701
            // lcd.print(log10((double)getDataLong(getParameter(PARAM_COLOR)) / (double)getDataLong(i * dataRowSize + getParameter(PARAM_COLOR))));
            lcd.print(log10((double)getParameter(PARAM_COLOR) / (double)i * dataRowSize + getParameter(PARAM_COLOR)));
          } else {
            // Check EEPROMLogger - 20220701
            // lcd.print(getDataLong(i * dataRowSize + getParameter(PARAM_COLOR)) - getDataLong(getParameter(PARAM_COLOR)));
            lcd.print(i * dataRowSize + getParameter(PARAM_COLOR) - getParameter(PARAM_COLOR));
          }
        }
      }
    }
    lcdPrintBlank(6);
  }
}

void lcdMenu() {
  byte currentMenu = getParameter(PARAM_MENU);
  if (previousMenu != currentMenu) {  // this is used to clear screen from
                                      // external process for example
    noEventCounter = 0;
    previousMenu = currentMenu;
  }
  if (rotaryCounter == 0 && !rotaryPressed) {
    if (noEventCounter < 32760)
      noEventCounter++;
  } else {
    noEventCounter = 0;
  }
  // Show standby Menu
  if (noEventCounter > 250 && getParameter(PARAM_STATUS) == 0) {
    if (currentMenu - currentMenu % 10 != 20) {
      setParameter(PARAM_MENU, 20);
    }
    captureCounter = false;
  }

#ifdef BATTERY_CHARGING
  if (noEventCounter > 500 &&
      getParameter(PARAM_CHARGING) >
          500) {  // battery is charging so we are on USB : no sleep !
    noEventCounter = 500;
  }
#endif
  // Delete with BATTERY_CHARGING is set
  noEventCounter = 0;
  
  // Enter to sleep
  if (noEventCounter > 1500 && getParameter(PARAM_STATUS) == 0) {
    sleepNow();
    noEventCounter = 0;
  }

  boolean doAction = rotaryPressed;
  rotaryPressed = false;
  int counter = rotaryCounter;
  rotaryCounter = 0;
  switch (currentMenu < 100 ? currentMenu - currentMenu % 10
                            : currentMenu - currentMenu % 50) {
    case 0:
      lcdMenuHome(counter, doAction);
      break;
    case 10:
      lcdMenuSettings(counter, doAction);
      break;
    case 20:
      lcdStatus(counter, doAction);
      break;
    case 30:
      lcdAcquisition(counter, doAction);
      break;
    case 40:
      lcdUtilities(counter, doAction);
      break;
    case 100:
      lcdResults(counter, doAction);
      break;
  }
}

/*
// this code is currently not USED
void lcdDefaultExact(int counter, boolean doAction) {
  if (doAction)
    setParameter(PARAM_MENU, 0);
  updateCurrentMenu(counter, 1);
  if (noEventCounter < 2)
    lcd.clear();
  switch (getParameter(PARAM_MENU) % 10) {
    case 0:
      for (byte i = 0; i < min(nbProbes, 4); i++) {
        lcd.setCursor((i % 2) * 8, floor(i / 2));
        printColorOne(&lcd, ACTIVE_PARAMETERS[i]);
        lcd.print(": ");
        lcd.print(getParameter(i + 5) - getParameter(i));
        lcdPrintBlank(2);
      }
      break;
    case 1:
      lcd.setCursor(0, 0);
      epochToString(now(), &lcd);
      lcd.setCursor(6, 1);
      lcd.print("s: ");
      lcd.print(millis() / 1000);
      break;
  }
}

*/
