#include "radio_control.h"
#include "globals.h"

void Double_Sweep() {
  if (dirv == 0) {  // If flag is 0, increment ch by 4 and ch1 by 1
    ch1 += 2;
  } else {  // If flag is not 0, decrement ch by 4 and ch1 by 1
    ch1 -= 2;
  }

  if (dir == 0) {  // If flag is 0, increment ch by 4 and ch1 by 1
    ch += 2;
  } else {  // If flag is not 0, decrement ch by 4 and ch1 by 1
    ch -= 2;
  }

  // Check if ch1 is greater than 79 and flag is 0
  if ((ch1 > 79) && (dirv == 0)) {
    dirv = 1;                             // Set flag to 1 to change direction
  } else if ((ch1 < 2) && (dirv == 1)) {  // Check if ch1 is less than 2 and flag is 1
    dirv = 0;                             // Set flag to 0 to change direction
  }

  // Check if ch is greater than 79 and flag is 0
  if ((ch > 79) && (dir == 0)) {
    dir = 1;                            // Set flag to 1 to change direction
  } else if ((ch < 2) && (dir == 1)) {  // Check if ch is less than 2 and flag is 1
    dir = 0;                            // Set flag to 0 to change direction
  }
  radio.setChannel(ch);
  radio1.setChannel(ch1);
  //delayMicroseconds(150);
}

void Random() {
  ////RANDOM CHANNEL
  radio1.setChannel(random(80));
  radio.setChannel(random(80));
  //delayMicroseconds(150):
}

void WiFi_Sweep() {
  byte centerCh = 0;
  if (wifiChannel <= 13) {
    centerCh = 12 + (wifiChannel - 1) * 5;
  } else {
    centerCh = 84;
  }
  
  byte startCh = (centerCh >= 11) ? (centerCh - 11) : 0;
  byte endCh = centerCh + 11;
  if (endCh > 125) endCh = 125;
  
  // Random sweep within this bandwidth
  byte diff = endCh - startCh + 1;
  radio.setChannel(startCh + random(diff));
  radio1.setChannel(startCh + random(diff));
}

void initSP() {
  if (sp == nullptr) {
    sp = new SPIClass(VSPI);
    sp->begin(19, 18, 5, -1);
  }
  if (radio1.begin(sp)) {
    Serial.println("SP Started !!!");
    radio1.setAutoAck(false);
    radio1.stopListening();
    radio1.setRetries(0, 0);
    radio1.setPALevel(currentPA, true);
    radio1.setDataRate(currentRate);
    radio1.setCRCLength(RF24_CRC_DISABLED);
    radio1.startConstCarrier(currentPA, cch1);
  } else {
    Serial.println("SP couldn't start !!!");
  }
}

void initHP() {
  if (hp == nullptr) {
    hp = new SPIClass(HSPI);
    hp->begin(26, 25, 33, -1);
  }
  if (radio.begin(hp)) {
    Serial.println("HP Started !!!");
    radio.setAutoAck(false);
    radio.stopListening();
    radio.setRetries(0, 0);
    radio.setPALevel(currentPA, true);
    radio.setDataRate(currentRate);
    radio.setCRCLength(RF24_CRC_DISABLED);
    radio.startConstCarrier(currentPA, cch);
  } else {
    Serial.println("HP couldn't start !!!");
  }
}

