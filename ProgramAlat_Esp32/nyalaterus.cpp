#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

const char* BEACON_NAME   = "Beacon2";
const uint8_t  BURST_CNT  = 3;
const uint16_t BURST_GAP  = 200;

void wakeupMsg();

void setup() {
  Serial.begin(115200);
  delay(50);

  BLEDevice::init(BEACON_NAME);
  BLEAdvertising* adv = BLEDevice::getAdvertising();

  BLEAdvertisementData advData;
  advData.setFlags(0x06);
  advData.setName(BEACON_NAME);
  adv->setAdvertisementData(advData);
  adv->setScanResponse(false);
  adv->setAdvertisementType(ADV_TYPE_NONCONN_IND);

  Serial.println("Memulai transmisi BLE berkelanjutan...");
}

void loop() {
  BLEAdvertising* adv = BLEDevice::getAdvertising();
  for (uint8_t i = 0; i < BURST_CNT; ++i) {
    adv->start();
    delay(200);
    adv->stop();
    if (i < BURST_CNT - 1) delay(BURST_GAP);
  }
  Serial.printf("📡 Burst %u× selesai, menunggu untuk burst berikutnya...\n", BURST_CNT);

  delay(1000);
}

void wakeupMsg() {
}
