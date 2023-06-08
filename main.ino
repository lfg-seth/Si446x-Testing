#include "Transceiver.h"

Transceiver trx;

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // Wait for Serial to be ready
  trx.init();
  trx.printDeviceInfo();
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readString();
    trx.sendData(data);
    
    }
  
  String receivedData = trx.receiveData();
  if (receivedData != "") {
    Serial.println(receivedData);
  }
}
