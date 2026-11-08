#include "display_menu.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "globals.h"
#include "radio_control.h"
#include "screensaver_frames.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char usco_logo[] PROGMEM = {
  0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 
  0x00, 0x00, 0x04, 0x78, 0x0f, 0x10, 0x00, 0x00, 
  0x07, 0xff, 0xf3, 0x03, 0xe0, 0x67, 0xff, 0xf0, 
  0x07, 0xff, 0xf0, 0x03, 0xe0, 0x07, 0xff, 0xf0, 
  0x07, 0xff, 0xf0, 0x30, 0x0e, 0x07, 0xff, 0xf0, 
  0x07, 0xff, 0xf1, 0x00, 0x00, 0x47, 0xff, 0xf0, 
  0x07, 0xff, 0xe2, 0x88, 0x08, 0xa7, 0xff, 0xf0, 
  0x01, 0xff, 0xc5, 0x0c, 0x18, 0x51, 0xff, 0xc0, 
  0x00, 0xff, 0x82, 0x72, 0x27, 0x20, 0xff, 0x80, 
  0x00, 0xff, 0x82, 0x08, 0x08, 0x28, 0xff, 0x80, 
  0x00, 0xff, 0x8a, 0x18, 0x08, 0x28, 0xff, 0x80, 
  0x00, 0xff, 0x8a, 0x06, 0x30, 0x28, 0xff, 0x80, 
  0x00, 0xff, 0x86, 0x00, 0x80, 0x30, 0xff, 0x80, 
  0x00, 0xff, 0x82, 0x1f, 0xf8, 0x20, 0xff, 0x80, 
  0x00, 0xff, 0x85, 0x17, 0xec, 0x50, 0xff, 0x80, 
  0x00, 0xff, 0x80, 0x9f, 0xf9, 0x00, 0xff, 0x80, 
  0x00, 0xff, 0x88, 0x10, 0x04, 0x08, 0xff, 0x80, 
  0x00, 0xff, 0x88, 0x0f, 0xff, 0xc8, 0xff, 0x80, 
  0x00, 0xff, 0x80, 0x30, 0x00, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x90, 0x6f, 0xcf, 0x44, 0xff, 0x80, 
  0x00, 0xff, 0x90, 0xdf, 0xff, 0x44, 0xff, 0x80, 
  0x00, 0xff, 0x80, 0xbf, 0xff, 0x44, 0xff, 0x80, 
  0x00, 0xff, 0x80, 0x7f, 0xff, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x81, 0x7f, 0xff, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x81, 0x7f, 0xff, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x91, 0x7f, 0xff, 0x44, 0xff, 0x80, 
  0x00, 0xff, 0x91, 0x7e, 0x7f, 0x44, 0xff, 0x80, 
  0x00, 0xff, 0x8d, 0x7f, 0x00, 0x58, 0xff, 0x80, 
  0x00, 0xff, 0x8f, 0x7f, 0x9f, 0xf0, 0xff, 0x80, 
  0x00, 0xff, 0x88, 0xbf, 0xc8, 0x00, 0xff, 0x80, 
  0x00, 0xff, 0x88, 0x9f, 0xf4, 0x00, 0xff, 0x80, 
  0x00, 0xff, 0x88, 0x6f, 0xfa, 0x00, 0xff, 0x80, 
  0x00, 0xff, 0x88, 0x27, 0xfd, 0x00, 0xff, 0x80, 
  0x00, 0xff, 0x88, 0x1b, 0xfe, 0x80, 0xff, 0x80, 
  0x00, 0xff, 0x89, 0xf8, 0xfe, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x89, 0x00, 0x7f, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x89, 0x7e, 0x3f, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x89, 0x7f, 0xff, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x89, 0x7f, 0xff, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x89, 0x7f, 0xff, 0x40, 0xff, 0x80, 
  0x00, 0xff, 0x89, 0x7f, 0xff, 0x00, 0xff, 0x80, 
  0x00, 0xff, 0x89, 0x7f, 0xfe, 0x80, 0xff, 0x80, 
  0x00, 0xff, 0x81, 0x7f, 0xfc, 0x00, 0xff, 0x80, 
  0x00, 0xff, 0x81, 0x7b, 0xf9, 0x00, 0xff, 0x80, 
  0x00, 0xff, 0x89, 0x00, 0x06, 0x08, 0xff, 0x80, 
  0x00, 0xff, 0x83, 0xfd, 0xf8, 0x60, 0xff, 0x80, 
  0x00, 0xff, 0xc0, 0x3e, 0x1e, 0x01, 0xff, 0x80, 
  0x00, 0xff, 0xf0, 0x00, 0x00, 0x07, 0xff, 0x80, 
  0x00, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0x80, 
  0x00, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0x80, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
  0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

enum MenuState {
  MENU_MAIN,
  MENU_MODES,
  MENU_POWER,
  MENU_TONE,
  MENU_WIFI
};

MenuState currentState = MENU_MAIN;
int currentSelection = 0;

unsigned long lastActivityTime = 0;
bool isSleeping = false;
unsigned long lastAnimTime = 0;
unsigned long lastBounceTime = 0;
int animFrame = 0;
int faceX = 15;
int faceY = 48;
int faceDx = 1;
int faceDy = 1;

// Main Menu Options
const int MAIN_MENU_ITEMS = 4;
const char* mainMenu[MAIN_MENU_ITEMS] = {"Start", "Modes", "Power", "Stop"};

// Power Menu Options
const int POWER_MENU_ITEMS = 4;
const char* powerMenu[POWER_MENU_ITEMS] = {"2dBm", "8dBm", "14dBm", "20dBm"};

// Modes Menu Options
const int MODES_MENU_ITEMS = 4;
const char* modesMenu[MODES_MENU_ITEMS] = {"Random", "Sweep", "Tone", "WiFi"};

unsigned long buttonHoldTime = 0;
bool isHolding = false;

void drawMenu(const char* title, const char** items, int numItems, int selection) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, 0);
  display.print(title);
  display.setCursor(104, 0);
  display.println("USCO");
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
  
  for (int i = 0; i < numItems; i++) {
    int x = 10;
    int y = 15 + i * 12;
    int cursorX = 0;
    
    if (i >= 3) {
      x = 74;
      y = 15 + (i - 3) * 12;
      cursorX = 64;
    }

    display.setCursor(x, y);
    if (i == selection) {
      display.setCursor(cursorX, y);
      display.print(">");
      display.setCursor(x, y);
      display.println(items[i]);
    } else {
      display.println(items[i]);
    }
  }
  
  // Status bar at bottom
  display.drawLine(0, 52, 128, 52, SSD1306_WHITE);
  display.setCursor(0, 55);
  display.print(isJamming ? "JAMMING:ON " : "JAMMING:OFF ");
  display.print("M:");
  display.print(SweepMode);
  display.print(" ");
  if (currentPA == RF24_PA_MIN) display.print("2dBm");
  else if (currentPA == RF24_PA_LOW) display.print("8dBm");
  else if (currentPA == RF24_PA_HIGH) display.print("14dBm");
  else if (currentPA == RF24_PA_MAX) display.print("20dBm");
  display.display();
}

void drawWiFiMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, 0);
  display.print("WiFi - CH");
  display.setCursor(104, 0);
  display.println("USCO");
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
  
  display.setTextSize(2);
  display.setCursor(20, 25);
  display.print("CH: ");
  display.print(wifiChannel);
  
  display.setTextSize(1);
  display.drawLine(0, 52, 128, 52, SSD1306_WHITE);
  display.setCursor(0, 55);
  display.print(isJamming ? "JAMMING:ON " : "JAMMING:OFF ");
  display.print("M:");
  display.print(SweepMode);
  display.print(" ");
  if (currentPA == RF24_PA_MIN) display.print("2dBm");
  else if (currentPA == RF24_PA_LOW) display.print("8dBm");
  else if (currentPA == RF24_PA_HIGH) display.print("14dBm");
  else if (currentPA == RF24_PA_MAX) display.print("20dBm");
  display.display();
}

void drawToneMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, 0);
  display.print("Tone - CH");
  display.setCursor(104, 0);
  display.println("USCO");
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
  
  display.setTextSize(2);
  display.setCursor(20, 25);
  display.print("CH: ");
  display.print(toneChannel);
  
  display.setTextSize(1);
  display.drawLine(0, 52, 128, 52, SSD1306_WHITE);
  display.setCursor(0, 55);
  display.print(isJamming ? "JAMMING:ON " : "JAMMING:OFF ");
  display.print("M:");
  display.print(SweepMode);
  display.print(" ");
  if (currentPA == RF24_PA_MIN) display.print("2dBm");
  else if (currentPA == RF24_PA_LOW) display.print("8dBm");
  else if (currentPA == RF24_PA_HIGH) display.print("14dBm");
  else if (currentPA == RF24_PA_MAX) display.print("20dBm");
  display.display();
}

void initDisplay() {
  Wire.begin(23, 22);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    // For now, we continue even if display fails so serial menu works
  }
  
  // 1. Show Logo
  display.clearDisplay();
  int x = (SCREEN_WIDTH - 64) / 2;
  display.drawBitmap(x, 0, usco_logo, 64, 64, SSD1306_WHITE);
  display.display();
  delay(2000); // 2 seconds delay for logo
  
  // 2. Show Warning
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(15, 20);
  display.println(F(" LABORATORY USE"));
  display.setCursor(50, 30);
  display.println(F("ONLY!!"));
  
  display.display();
  delay(2000); // 2 seconds delay for warning
  lastActivityTime = millis();
}

void wakeUp() {
  if (isSleeping) {
    isSleeping = false;
    updateDisplay();
  }
  lastActivityTime = millis();
}

void checkScreensaver() {
  if (!isSleeping && !isJamming && (millis() - lastActivityTime > 30000)) {
    isSleeping = true;
    animFrame = 0;
    lastAnimTime = millis();
    lastBounceTime = millis();
    faceX = 0;
    faceY = 0;
    faceDx = 2;
    faceDy = 2;
    display.clearDisplay();
    display.display();
  }
  
  if (isSleeping) {
    bool updateNeeded = false;
    
    // Video updates at roughly 3 FPS (333ms per frame)
    if (millis() - lastAnimTime > 333) {
      lastAnimTime = millis();
      animFrame++;
      if (animFrame >= NUM_SCREENSAVER_FRAMES) {
          animFrame = 0; // Loop the video
      }
      updateNeeded = true;
    }

    // Bounce updates every 50ms for smooth movement
    if (millis() - lastBounceTime > 50) {
      lastBounceTime = millis();
      faceX += faceDx;
      faceY += faceDy;
      
      // Screen is 128x64. Video is 128x64.
      // To create movement without completely leaving the screen, let's wander off-screen slightly.
      if (faceX <= -32 || faceX >= 32) {
        faceDx = -faceDx;
        faceX += faceDx; 
      }
      if (faceY <= -16 || faceY >= 16) {
        faceDy = -faceDy;
        faceY += faceDy;
      }
      updateNeeded = true;
    }

    if (updateNeeded) {
      display.clearDisplay();
      // Draw the video frame at the bouncing coordinates
      display.drawBitmap(faceX, faceY, screensaver_frames[animFrame], 128, 64, SSD1306_WHITE);
      display.display();
    }
  }
}

void updateDisplay() {
  switch(currentState) {
    case MENU_MAIN:
      drawMenu("Main Menu", mainMenu, MAIN_MENU_ITEMS, currentSelection);
      break;
    case MENU_MODES:
      drawMenu("Select Mode", modesMenu, MODES_MENU_ITEMS, currentSelection);
      break;
    case MENU_POWER:
      drawMenu("Select Power", powerMenu, POWER_MENU_ITEMS, currentSelection);
      break;
    case MENU_TONE:
      drawToneMenu();
      break;
    case MENU_WIFI:
      drawWiFiMenu();
      break;
  }
}

void handleUp(bool isHeld) {
  if (currentState == MENU_MAIN) {
    if (!isHeld) {
      currentSelection--;
      if (currentSelection < 0) currentSelection = MAIN_MENU_ITEMS - 1;
    }
  } else if (currentState == MENU_MODES) {
    if (!isHeld) {
      currentSelection--;
      if (currentSelection < 0) currentSelection = MODES_MENU_ITEMS - 1;
    }
  } else if (currentState == MENU_POWER) {
    if (!isHeld) {
      currentSelection--;
      if (currentSelection < 0) currentSelection = POWER_MENU_ITEMS - 1;
    }
  } else if (currentState == MENU_TONE) {
    toneChannel++;
    if (toneChannel > 125) toneChannel = 0;
  } else if (currentState == MENU_WIFI) {
    wifiChannel++;
    if (wifiChannel > 14) wifiChannel = 1;
  }
}

void handleDown(bool isHeld) {
  if (currentState == MENU_MAIN) {
    if (!isHeld) {
      currentSelection++;
      if (currentSelection >= MAIN_MENU_ITEMS) currentSelection = 0;
    }
  } else if (currentState == MENU_MODES) {
    if (!isHeld) {
      currentSelection++;
      if (currentSelection >= MODES_MENU_ITEMS) currentSelection = 0;
    }
  } else if (currentState == MENU_POWER) {
    if (!isHeld) {
      currentSelection++;
      if (currentSelection >= POWER_MENU_ITEMS) currentSelection = 0;
    }
  } else if (currentState == MENU_TONE) {
    if (toneChannel == 0) {
      toneChannel = 125;
    } else {
      toneChannel--;
    }
  } else if (currentState == MENU_WIFI) {
    if (wifiChannel <= 1) {
      wifiChannel = 14;
    } else {
      wifiChannel--;
    }
  }
}


void handleOk() {
  if (currentState == MENU_MAIN) {
    if (currentSelection == 0) { // Start
      if (xSemaphoreTake(radioMutex, portMAX_DELAY) == pdTRUE) {
        initHP();
        initSP();
        if (SweepMode == 3) {
          radio.setChannel(toneChannel);
          radio1.setChannel(toneChannel);
        }
        isJamming = true;
        xSemaphoreGive(radioMutex);
      }
      Serial.println("Jamming started");
    } else if (currentSelection == 1) { // Modes
      currentState = MENU_MODES;
      currentSelection = 0;
    } else if (currentSelection == 2) { // Power
      currentState = MENU_POWER;
      if (currentPA == RF24_PA_MIN) currentSelection = 0;
      else if (currentPA == RF24_PA_LOW) currentSelection = 1;
      else if (currentPA == RF24_PA_HIGH) currentSelection = 2;
      else if (currentPA == RF24_PA_MAX) currentSelection = 3;
    } else if (currentSelection == 3) { // Stop
      if (xSemaphoreTake(radioMutex, portMAX_DELAY) == pdTRUE) {
        isJamming = false;
        radio.stopConstCarrier();
        radio1.stopConstCarrier();
        SweepMode = 0;
        xSemaphoreGive(radioMutex);
      }
      Serial.println("Jamming stopped");
    }
  } else if (currentState == MENU_MODES) {
    if (currentSelection == 0) { // Random
      SweepMode = 1;
      currentState = MENU_MAIN;
      currentSelection = 0;
    } else if (currentSelection == 1) { // Double Sweep
      if (xSemaphoreTake(radioMutex, portMAX_DELAY) == pdTRUE) {
        ch = 0; ch1 = 80;
        SweepMode = 2;
        xSemaphoreGive(radioMutex);
      }
      currentState = MENU_MAIN;
      currentSelection = 0;
    } else if (currentSelection == 2) { // Tone
      SweepMode = 3;
      currentState = MENU_TONE;
    } else if (currentSelection == 3) { // WiFi
      SweepMode = 4;
      currentState = MENU_WIFI;
    }
  } else if (currentState == MENU_POWER) {
    if (currentSelection == 0) currentPA = RF24_PA_MIN;
    else if (currentSelection == 1) currentPA = RF24_PA_LOW;
    else if (currentSelection == 2) currentPA = RF24_PA_HIGH;
    else if (currentSelection == 3) currentPA = RF24_PA_MAX;

    if (isJamming) {
      if (xSemaphoreTake(radioMutex, portMAX_DELAY) == pdTRUE) {
        radio.stopConstCarrier();
        radio1.stopConstCarrier();
        initHP();
        initSP();
        if (SweepMode == 3) {
          radio.setChannel(toneChannel);
          radio1.setChannel(toneChannel);
        }
        xSemaphoreGive(radioMutex);
      }
    }
    currentState = MENU_MAIN;
    currentSelection = 2; // point back to Power
  } else if (currentState == MENU_TONE) {
    if (isJamming && SweepMode == 3) {
      if (xSemaphoreTake(radioMutex, portMAX_DELAY) == pdTRUE) {
        radio.setChannel(toneChannel);
        radio1.setChannel(toneChannel);
        xSemaphoreGive(radioMutex);
      }
    }
    currentState = MENU_MAIN;
    currentSelection = 0;
  } else if (currentState == MENU_WIFI) {
    currentState = MENU_MAIN;
    currentSelection = 0;
  }
}

void handleBack() {
  if (currentState == MENU_MODES) {
    currentState = MENU_MAIN;
    currentSelection = 1; // point back to Modes
  } else if (currentState == MENU_POWER) {
    currentState = MENU_MAIN;
    currentSelection = 2; // point back to Power
  } else if (currentState == MENU_TONE) {
    currentState = MENU_MODES;
    currentSelection = 2; // point back to Tone
  } else if (currentState == MENU_WIFI) {
    currentState = MENU_MODES;
    currentSelection = 3; // point back to WiFi
  }
}

void handleVirtualButtons(char cmd) {
  if (isSleeping) {
    wakeUp();
    return; // Ignore the button action when waking up
  }
  wakeUp(); // Reset the timer
  
  switch (cmd) {
    case 'u': // Up
      handleUp(false);
      updateDisplay();
      break;
    case 'U': // Up (held)
      handleUp(true);
      updateDisplay();
      break;
    case 'v': // Down
      handleDown(false);
      updateDisplay();
      break;
    case 'V': // Down (held)
      handleDown(true);
      updateDisplay();
      break;
    case 'e': // OK
      handleOk();
      updateDisplay();
      break;
    case 'b': // Back
      handleBack();
      updateDisplay();
      break;
  }
}
