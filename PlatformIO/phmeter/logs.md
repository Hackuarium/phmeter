# Task

- Defining parameters to set (see https://hackuarium.github.io/bioreactor/).

## 06-01-2021:

- Add pH and Conductivity adquisition performed (step 1).

## 05-19-2021:

- Replace Nil library for PlatformIO recently library.
- Replace HX711 for PlatformIO recently library.

```
lib_deps =
	bogde/HX711@^0.7.4
	greiman/ChNil@^2017.8.2
```

- Replace new commands for NilRTOS with PlatformIO:

| Old command                                                              | New command                                                      |
| ------------------------------------------------------------------------ | ---------------------------------------------------------------- |
| nilThdSleepMilliseconds(1);                                              | chThdSleep(1);                                                   |
| nilPrintUnusedStack(&Serial);                                            | chPrintUnusedStack(&Serial);                                     |
| nilSemWait(&isrSem);                                                     | chSemWait(&isrSem);                                              |
| nilSemSignal(&isrSem);                                                   | chSemSignal(&isrSem);                                            |
| nilSysBegin();                                                           | chBegin();                                                       |
| nilPrintUnusedStack(&Serial);                                            | chPrintUnusedStack(&Serial);                                     |
| NIL_WORKING_AREA(waThreadI2C, 20);                                       | THD_WORKING_AREA(waThread2, 20);                                 |
| NIL_THREAD(Thread2, arg) {...}                                           | THD_FUNCTION(Thread2, arg) {...}                                 |
| NIL_THREADS_TABLE_BEGIN()                                                | THD_TABLE_BEGIN                                                  |
| NIL_THREADS_TABLE_ENTRY(NULL, Thread1, NULL, waThread1, sizeof(Thread1)) | THD_TABLE_ENTRY(waThread1, **"thread1" or NULL**, Thread1, NULL) |
| NIL_THREADS_TABLE_END()                                                  | THD_TABLE_END                                                    |

## 05-15-2021:

- Add setupParameters(); in 'uc' option in _serialUtilities.cpp_ to see actual parameters stored in EEPROM.
- Verified I2C thread.

## 05-14-2021:

- Add setupParameters(); into printParameters(...) in _params.cpp_ to see last values.
- Complete resetParameters() in _serialUtilities.cpp_.

## 05-13-2021:

- Enable --echo flag for pio device monitor in PlatformIO [NOTE 1].
- Change **SERIAL_MAX_PARAM_VALUE_LENGTH** from 32 to 6 because we're using 16 bits store data in the EEPROM (1024 bytes ATMEGA32U4 - 512 words of 2 bytes length).
- Update toHex.cpp file.

## 05-12-2021:

- Delete _if_ condition for serial NIL_THREAD.
- Delete _if_ condition for A-Z check.
- Display **ERR** if the serial is more than **SERIAL_BUFFER_LENGTH**.

### NOTE 1

- Click - PlatformIO.
- Click on: **Projects & Configuration**.
- In actual project (ex.: LilyPadUSB) searh on: **New Option** -> **monitor_flags** or searh in the bottom of this window.
- Write: _--echo_ to enable echo in the serial monitor.
- [More info here](https://docs.platformio.org/en/latest/core/userguide/device/cmd_monitor.html).
