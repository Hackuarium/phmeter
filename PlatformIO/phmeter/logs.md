05-12-2021:
---
- Delete *if* condition for serial NIL_THREAD.
- Delete *if* condition for A-Z check.
- Display **ERR** if the serial is more than **SERIAL_BUFFER_LENGTH**.

05-13-2021:
---

- Enable --echo flag for pio device monitor in PlatformIO [NOTE 1].
- Change **SERIAL_MAX_PARAM_VALUE_LENGTH** from 32 to 16 because we're using 16 bits store data in the EEPROM (1024 bytes ATMEGA32U4).

22.99 585
33.2 9512

### NOTE 1
- Click - PlatformIO.
- Click on: **Projects & Configuration**.
- In actual project (ex.: LilyPadUSB) searh on: **New Option** -> **monitor_flags** or searh in the bottom of this window.
- Write: *--echo* to enable echo in the serial monitor.
- [More info here](https://docs.platformio.org/en/latest/core/userguide/device/cmd_monitor.html).

