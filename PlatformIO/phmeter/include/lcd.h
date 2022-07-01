#include <Arduino.h>
#include <ChNil.h>

// Rotary push button
void rotate();
void eventRotaryPressed();
void setupRotary();
void updateCurrentMenu(int, uint8_t, uint8_t);
void updateCurrentMenu(int, uint8_t);
void lcdNumberLine(uint8_t);
void lcdMenuHome(int, bool);
void lcdMenuSettings(int, bool);
void lcdPrintBlank(uint8_t);
void lcdStatus(int, bool);
void lcdWait();
void lcdAcquisition(int, bool);
void lcdUtilities(int, bool);
void lcdResults(int, bool);

void lcdMenu();

