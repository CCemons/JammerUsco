
#include "RF24.h"
#include <SPI.h>
#include <Arduino.h>
#include <ezButton.h>
#include "esp_bt.h"
#include "esp_wifi.h"

#include "globals.h"
#include "radio_control.h"
#include "cli_handler.h"
#include "display_menu.h"

// Define buttons (Commented out for now, to be used later)

#define BUTTON_UP_PIN    14
#define BUTTON_DOWN_PIN  13
#define BUTTON_OK_PIN    4
#define BUTTON_BACK_PIN  16

ezButton btnUp(BUTTON_UP_PIN);
ezButton btnDown(BUTTON_DOWN_PIN);
ezButton btnOk(BUTTON_OK_PIN);
ezButton btnBack(BUTTON_BACK_PIN);
unsigned long lastHoldScroll = 0;
TaskHandle_t jammerTaskHandle = NULL;

void jammerTask(void *pvParameters) {
  unsigned long lastWatchdogFeed = millis();
  for (;;) {
    if (isJamming && (SweepMode == 1 || SweepMode == 2 || SweepMode == 4)) {
      if (xSemaphoreTake(radioMutex, portMAX_DELAY) == pdTRUE) {
        if (isJamming) {
          if (SweepMode == 1) Random();
          else if (SweepMode == 2) Double_Sweep();
          else if (SweepMode == 4) WiFi_Sweep();
        }
        xSemaphoreGive(radioMutex);
      }
      // Feed Core 0 IDLE0 Task Watchdog Timer for 1 tick every 500ms
      if (millis() - lastWatchdogFeed >= 500) {
        vTaskDelay(1);
        lastWatchdogFeed = millis();
      }
    } else {
      // Idle or SweepMode 3 (Tone constant carrier): yield Core 0 CPU
      vTaskDelay(pdMS_TO_TICKS(5));
      lastWatchdogFeed = millis();
    }
  }
}

void setup() {
  Serial.begin(115200);
  esp_bt_controller_deinit();
  esp_wifi_stop();
  esp_wifi_deinit();
  esp_wifi_disconnect();
  
  radioMutex = xSemaphoreCreateMutex();

  // Initialize buttons (commented out)
  
  btnUp.setDebounceTime(2);
  btnDown.setDebounceTime(2);
  btnOk.setDebounceTime(2);
  btnBack.setDebounceTime(2);
  

  initDisplay(); // Initialize OLED and show boot screen
  updateDisplay(); // Show main menu

  // Launch RF sweep task on Core 0 (UI/OLED/Serial run on Core 1)
  xTaskCreatePinnedToCore(
    jammerTask,
    "JammerRFTask",
    4096,
    NULL,
    1,
    &jammerTaskHandle,
    0
  );

  Serial.println("Welcome, User, Wanna Jamm?");
  Serial.println("Menu controls (Serial): 'u' (Up), 'U' (Up fast), 'v' (Down), 'V' (Down fast), 'e' (OK), 'b' (Back)");
}

void loop() {
  // Read physical buttons (commented out)
  
  btnUp.loop();
  btnDown.loop();
  btnOk.loop();
  btnBack.loop();

  if (btnUp.isPressed()) { 
    handleVirtualButtons('u'); 
    lastHoldScroll = millis(); 
  } else if (btnUp.getState() == LOW) {
    // Logic for hold scroll (600ms delay, 25ms repeat)
    if (millis() - lastHoldScroll > 600) {
       handleVirtualButtons('u'); 
       lastHoldScroll = millis() - 575; 
    }
  }

  if (btnDown.isPressed()) { 
    handleVirtualButtons('v'); 
    lastHoldScroll = millis(); 
  } else if (btnDown.getState() == LOW) {
    if (millis() - lastHoldScroll > 600) {
       handleVirtualButtons('v'); 
       lastHoldScroll = millis() - 575;
    }
  }

  if (btnOk.isPressed()) { handleVirtualButtons('e'); }
  if (btnBack.isPressed()) { handleVirtualButtons('b'); }

  processSerialCommands(); // Reads serial and handles UI/Jammer config
  checkScreensaver(); // Update screensaver logic and animation
}