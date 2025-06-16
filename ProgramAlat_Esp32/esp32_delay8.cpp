#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "esp_sleep.h"


#define ACTIVE_TIME 60000          
#define SLEEP_DURATION 8 * 60 * 1000000ULL  

void setup() {
  Serial.begin(115200);
  delay(100); 


  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
    Serial.println("Bangun dari Deep Sleep");
  } else {
    Serial.println("Restart");
  }

  // Inisialisasi BLE
  BLEDevice::init("Beacon1");
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  BLEAdvertisementData oAdvertisementData;
  oAdvertisementData.setFlags(0x06);
  oAdvertisementData.setName("Beacon1");
  pAdvertising->setAdvertisementData(oAdvertisementData);

  pAdvertising->start();
  Serial.println("mengirim sinyal");

  
  delay(ACTIVE_TIME);

  
  pAdvertising->stop();
  BLEDevice::deinit(true);
  Serial.println("Beacon Sleep");

  
  esp_sleep_enable_timer_wakeup(SLEEP_DURATION);
  esp_deep_sleep_start();
}

void loop() {
  // Tidak digunakan
}
