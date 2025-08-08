#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <vector>
#include <algorithm>
#include <map>
#include <chrono>

std::map<String, unsigned long> lastSeenMap;
const unsigned long TIMEOUT_MS = 1000;

#define SERVER_URL "http://10.15.41.53:5000/update_location"
const char* LOCATION_NAME = "Lokasi B";
const char* TARGET_BEACONS[] = {"Beacon1", "Beacon2", "Beacon3"};
const int NUM_BEACONS = sizeof(TARGET_BEACONS) / sizeof(TARGET_BEACONS[0]);

#define SCAN_TIME 2               
#define SCAN_INTERVAL 3000        

BLEScan* pBLEScan;
std::vector<String> detectedBeacons;
std::vector<String> previousBeacons;
unsigned long lastScanTime = 0;

void sendLocationToServer(const String& beaconId, const String& location) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(SERVER_URL);
        http.addHeader("Content-Type", "application/json");

        String payload = "{\"beacon_id\": \"" + beaconId + "\", \"location\": \"" + location + "\"}";
        int httpResponseCode = http.POST(payload);
        Serial.println("Sent: " + payload + " | Response: " + String(httpResponseCode));
        http.end();
    } else {
        Serial.println("WiFi not connected. Cannot send data.");
    }
}

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    int rssi = advertisedDevice.getRSSI();
    if (rssi > -85 && advertisedDevice.haveName()) {
        for (int i = 0; i < NUM_BEACONS; i++) {
            if (advertisedDevice.getName() == TARGET_BEACONS[i]) {
                String beaconId = String("Beacon ") + String(i + 1);
                if (std::find(detectedBeacons.begin(), detectedBeacons.end(), beaconId) == detectedBeacons.end()) {
                    detectedBeacons.push_back(beaconId);
                    Serial.println("✅ Dalam jangkauan: " + beaconId);
                }
            }
        }
    } else {
        Serial.println("ℹ️ Sinyal lemah / tidak dikenal");
    }
  }
};

void setup() {
    Serial.begin(115200);

    // ----------- WIFI MANAGER -----------
    WiFiManager wm;
    // wm.resetSettings(); // Aktifkan jika ingin reset konfigurasi WiFi
    bool success = wm.autoConnect("ESP32-Receiver", "admin123");
    if (!success) {
        Serial.println("❌ Gagal konek WiFi, restart...");
        delay(3000);
        ESP.restart();
    }

    Serial.println("✅ Tersambung WiFi: " + WiFi.SSID());
    Serial.println("📡 IP: " + WiFi.localIP().toString());

    // ------------------------------------
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true);
}

void loop() {
    unsigned long now = millis();
    if (now - lastScanTime >= SCAN_INTERVAL) {
        Serial.println("🔍 Mulai scan BLE...");
        detectedBeacons.clear();
        pBLEScan->start(SCAN_TIME, false);
        lastScanTime = now;

        // Deteksi masuk
        for (const String& beaconId : detectedBeacons) {
            if (std::find(previousBeacons.begin(), previousBeacons.end(), beaconId) == previousBeacons.end()) {
                sendLocationToServer(beaconId, LOCATION_NAME);
            }
            lastSeenMap[beaconId] = now; // simpan waktu terakhir terlihat
        }

        // Deteksi keluar berdasarkan timeout
        std::vector<String> keluarSekarang;
        for (auto it = lastSeenMap.begin(); it != lastSeenMap.end(); ) {
            if (now - it->second >= TIMEOUT_MS) {
                sendLocationToServer(it->first, "Keluar dari lokasi");
                keluarSekarang.push_back(it->first);
                it = lastSeenMap.erase(it); // hapus dari map
            } else {
                ++it;
            }
        }

        // Update previousBeacons
        previousBeacons = detectedBeacons;
    }
}

