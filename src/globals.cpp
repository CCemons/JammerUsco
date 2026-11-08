#include "globals.h"

SPIClass *sp = nullptr;
SPIClass *hp = nullptr;

RF24 radio(27, 32, 16000000);
RF24 radio1(21, 17, 16000000);

byte dir = 0;
byte dirv = 0;

byte cch = 41;
byte cch1 = 43; 
byte ch = 0;
byte ch1 = 80;

byte SweepMode = 0;
byte PulseMode = 0;

byte toneChannel = 0;
byte wifiChannel = 1;
bool isJamming = false;

rf24_pa_dbm_e currentPA = RF24_PA_MIN;
rf24_datarate_e currentRate = RF24_2MBPS;

SemaphoreHandle_t radioMutex = NULL;
