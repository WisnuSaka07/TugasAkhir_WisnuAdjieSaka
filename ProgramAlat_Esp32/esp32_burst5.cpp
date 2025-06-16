#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "esp_sleep.h"


const char* BEACON_NAME   = "Beacon1";
const uint64_t SLEEP_TIME = 5ULL * 60ULL * 1000000ULL;   
const uint8_t  BURST_CNT  = 10;      
const uint16_t BURST_GAP  = 30;     



void wakeupMsg();


void setup() {
  Serial.begin(115200);
  delay(50);

  wakeupMsg();

  
  BLEDevice::init(BEACON_NAME);
  BLEAdvertising* adv = BLEDevice::getAdvertising();

  BLEAdvertisementData advData;
  advData.setFlags(0x06);        
  advData.setName(BEACON_NAME);  
  adv->setAdvertisementData(advData);
  adv->setScanResponse(false);   
  adv->setAdvertisementType(ADV_TYPE_NONCONN_IND); 

  
  for (uint8_t i = 0; i < BURST_CNT; ++i) {
    adv->start();
    delay(10);      
    adv->stop();
    if (i < BURST_CNT - 1) delay(BURST_GAP);
  }
  Serial.printf("Burst %u× selesai, masuk deep‑sleep…\n", BURST_CNT);

  
  BLEDevice::deinit(true);        
  esp_sleep_enable_timer_wakeup(SLEEP_TIME);
  esp_deep_sleep_start();
}

void loop() {  }


void wakeupMsg() {
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_TIMER) {
    Serial.println("Bangun");
  } else {
    Serial.println("reset normal");
  }
}
