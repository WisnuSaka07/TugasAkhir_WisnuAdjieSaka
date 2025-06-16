#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <vector>
#include <algorithm>

#define WIFI_SSID "ITS-WIFI-TW2"
#define WIFI_PASSWORD "itssurabaya"
#define SERVER_URL "http://10.15.41.91:5000/update_location"

#define SCAN_TIME 4
const char* LOCATION_NAME = "Lokasi B"; //Disesuaikan nama lokasi

const char* TARGET_BEACONS[] = {"Beacon1", "Beacon2", "Beacon3"}; //Disesuaikan target beacon
const int NUM_BEACONS = sizeof(TARGET_BEACONS) / sizeof(TARGET_BEACONS[0]);

BLEScan* pBLEScan;
std::vector<String> detectedBeacons;
std::vector<String> previousBeacons;

void sendLocationToServer(const String& beaconId, const String& location) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(SERVER_URL);
        http.addHeader("Content-Type", "application/json");

        String payload = "{\"beacon_id\": \"" + beaconId + "\", \"location\": \"" + location + "\"}";
        int httpResponseCode = http.POST(payload);
        Serial.println("Sent: " + payload + " | Response: " + String(httpResponseCode));

        http.end();
    }
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    int rssi = advertisedDevice.getRSSI();  
    Serial.print("Ditemukan: ");
    Serial.print(advertisedDevice.getName().c_str());
    Serial.print(" | RSSI: ");
    Serial.println(rssi);

    
    if (rssi > -85 && advertisedDevice.haveName()) { 
        for (int i = 0; i < NUM_BEACONS; i++) {
            if (advertisedDevice.getName() == TARGET_BEACONS[i]) {
                String beaconId = String("Beacon ") + String(i + 1);
                if (std::find(detectedBeacons.begin(), detectedBeacons.end(), beaconId) == detectedBeacons.end()) {
                    detectedBeacons.push_back(beaconId);
                    Serial.println("Dalam jangkauan: " + beaconId);
                }
            }
        }
    } else {
        Serial.println("sinyal lemah");
    }
  }
};

void setup() {
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi!");

    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true);
}

void loop() {
    Serial.println("Scanning...");
    detectedBeacons.clear();

    
    pBLEScan->start(SCAN_TIME, false);

    
    for (const String& beaconId : detectedBeacons) {
        if (std::find(previousBeacons.begin(), previousBeacons.end(), beaconId) == previousBeacons.end()) {
            sendLocationToServer(beaconId, LOCATION_NAME);
        }
    }

    
    for (const String& beaconId : previousBeacons) {
        if (std::find(detectedBeacons.begin(), detectedBeacons.end(), beaconId) == detectedBeacons.end()) {
            sendLocationToServer(beaconId, "Keluar dari lokasi");
        }
    }

    previousBeacons = detectedBeacons;
    delay(500); 
}
