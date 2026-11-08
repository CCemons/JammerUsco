#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <RF24.h>

extern bool isJamming;
extern byte SweepMode;
extern rf24_pa_dbm_e currentPA;
extern byte wifiChannel;
extern byte toneChannel;
extern byte ch;
extern byte ch1;
extern byte dir;
extern byte dirv;
extern byte cch;
extern byte cch1;
extern rf24_datarate_e currentRate;
extern SPIClass *sp;
extern SPIClass *hp;

extern RF24 radio;
extern RF24 radio1;
extern SemaphoreHandle_t radioMutex;

void initHP();
void initSP();

#endif

