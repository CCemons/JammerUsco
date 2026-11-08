#ifndef DISPLAY_MENU_H
#define DISPLAY_MENU_H

#include <Arduino.h>

void initDisplay();
void updateDisplay();
void checkScreensaver();
void wakeUp();
// Handlers for physical/virtual buttons
void handleVirtualButtons(char cmd); // for serial override

#endif // DISPLAY_MENU_H
