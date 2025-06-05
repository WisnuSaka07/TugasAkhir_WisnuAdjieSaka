#include <Arduino.h>


int myFunction(int, int);

void setup() {
  Serial.begin(115200);  
  Serial2.begin(9600, SERIAL_8N1, 16, 17); 

  delay(2000); 

  
  Serial2.println("AT+RESET");
  delay(500);

  
  Serial2.println("AT+ADVDATA=0");
  delay(500);

  
  Serial2.println("AT+NAME_");
  delay(500);

  
  Serial2.println("AT+NAMBBeacon3");
  delay(500);

  
  Serial2.println("AT+RESET");
  delay(500);

  Serial.println("✅ JDY-33 telah diatur ulang dan di-rename ke Beacon3");
}

void loop() {
  
}
