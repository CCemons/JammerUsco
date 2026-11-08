#include "cli_handler.h"
#include "globals.h"
#include "radio_control.h"
#include "display_menu.h"

void processSerialCommands() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (!(cmd == 'u' || cmd == 'v' || cmd == 'e' || cmd == 'b' || cmd == 'U' || cmd == 'V')) {
      wakeUp();
    }
    bool configChanged = false;

    switch (cmd) {
      case 'm': currentPA = RF24_PA_MIN; configChanged = true; Serial.println("Potencia -> MIN"); break;
      case 'l': currentPA = RF24_PA_LOW; configChanged = true; Serial.println("Potencia -> LOW"); break;
      case 'h': currentPA = RF24_PA_HIGH; configChanged = true; Serial.println("Potencia -> HIGH"); break;
      case 'x': currentPA = RF24_PA_MAX; configChanged = true; Serial.println("Potencia -> MAX"); break;
      
      case 'k': currentRate = RF24_250KBPS; configChanged = true; Serial.println("Velocidad -> 250 KBPS"); break;
      case '1': currentRate = RF24_1MBPS; configChanged = true; Serial.println("Velocidad -> 1 MBPS"); break;
      case '2': currentRate = RF24_2MBPS; configChanged = true; Serial.println("Velocidad -> 2 MBPS"); break;

      case 'd': 
        if (xSemaphoreTake(radioMutex, portMAX_DELAY) == pdTRUE) {
          radio.printPrettyDetails(); 
          radio1.printPrettyDetails(); 
          xSemaphoreGive(radioMutex);
        }
        break;

      case 'o': SweepMode = 1; Serial.println("Random"); break;
      case 't': 
        if (xSemaphoreTake(radioMutex, portMAX_DELAY) == pdTRUE) {
          ch = 0; ch1 = 80; SweepMode = 2; 
          xSemaphoreGive(radioMutex);
        }
        Serial.println("Double Sweep"); 
        break;  
      case 'w': SweepMode = 4; Serial.println("WiFi Sweep"); break;

      case 's': 
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
        break;
      case 'p': 
        if (xSemaphoreTake(radioMutex, portMAX_DELAY) == pdTRUE) {
          isJamming = false; 
          radio.stopConstCarrier(); 
          radio1.stopConstCarrier(); 
          xSemaphoreGive(radioMutex);
        }
        Serial.println("Sweep stopped"); 
        Serial.println("Jamming stopped"); 
        break;

      case 'u': 
      case 'U': 
      case 'v': 
      case 'V': 
      case 'e': 
      case 'b': 
        handleVirtualButtons(cmd); 
        break;
    }

    if (configChanged) {
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
      configChanged = false;
    }
  }
}


