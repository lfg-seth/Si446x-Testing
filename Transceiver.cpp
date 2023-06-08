#include "Transceiver.h"

Transceiver::Transceiver() {}

void Transceiver::init() {
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH); // Ensure SS is high
  pinMode(IRQ_PIN, INPUT);
  
  SPI.begin();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); //10 MHz, MSB first, mode 0
}

void Transceiver::sendData(String data) {
  uint8_t cmd = 0x66; // Command register for TX FIFO
  
  // Ensure SS pin is low before communication
  digitalWrite(SS_PIN, LOW);
  
  // Send command to write to TX FIFO
  SPI.transfer(cmd);
  
  // Break data into chunks of 64 bytes and send each chunk
  int len = data.length();
  for (int i = 0; i < len; i+=64) {
    String chunk = data.substring(i, min(i+64, len));
    for (int j = 0; j < chunk.length(); j++) {
      SPI.transfer(chunk[j]);
    }
  }
  
  // Ensure SS pin is high after communication
  digitalWrite(SS_PIN, HIGH);
}


String Transceiver::receiveData() {
  // Use specific SPI commands from datasheet to receive data
  // Add check for IRQ_PIN to see if data has been received
}

void Transceiver::writeRegister(uint8_t address, uint8_t value) {
  // Use specific SPI commands from datasheet to write to a register
}

uint8_t Transceiver::readRegister(uint8_t address) {
  // Use specific SPI commands from datasheet to read from a register
}


void Transceiver::startTransmit() {
  uint8_t cmd = 0x31; // Command to start transmitting
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(cmd);
  digitalWrite(SS_PIN, HIGH);
}

void Transceiver::startReceive() {
  uint8_t cmd = 0x32; // Command to start receiving
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(cmd);
  digitalWrite(SS_PIN, HIGH);
}

void Transceiver::readFIFOInfo(uint8_t &rxCount, uint8_t &txSpace) {
  uint8_t cmd1 = 0x15; // Command to read FIFO info
  uint8_t cmd2 = 0x00;

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(cmd1);
  SPI.transfer(cmd2);
  rxCount = SPI.transfer(0x00); // Dummy write to read data
  txSpace = SPI.transfer(0x00); // Dummy write to read data
  digitalWrite(SS_PIN, HIGH);
}

// struct PartInfo {
//   uint8_t chipRev;
//   uint16_t part;
//   uint8_t partBuild;
//   uint16_t id;
//   uint8_t customer;
//   uint8_t romId;
// };

PartInfo Transceiver::readPartInfo() {
  uint8_t cmd = 0x01;
  PartInfo info;

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(cmd);
  SPI.transfer(0x00); // Read CTS
  info.chipRev = SPI.transfer(0x00);
  info.part = SPI.transfer(0x00) << 8;
  info.part |= SPI.transfer(0x00);
  info.partBuild = SPI.transfer(0x00);
  info.id = SPI.transfer(0x00) << 8;
  info.id |= SPI.transfer(0x00);
  info.customer = SPI.transfer(0x00);
  info.romId = SPI.transfer(0x00);
  digitalWrite(SS_PIN, HIGH);

  return info;
}

// struct FuncInfo {
//   uint8_t revExt;
//   uint8_t revBranch;
//   uint8_t revInt;
//   uint16_t patch;
//   uint8_t func;
// };

FuncInfo Transceiver::readFuncInfo() {
  uint8_t cmd = 0x10;
  FuncInfo info;

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(cmd);
  SPI.transfer(0x00); // Read CTS
  info.revExt = SPI.transfer(0x00);
  info.revBranch = SPI.transfer(0x00);
  info.revInt = SPI.transfer(0x00);
  info.patch = SPI.transfer(0x00) << 8;
  info.patch |= SPI.transfer(0x00);
  info.func = SPI.transfer(0x00);
  digitalWrite(SS_PIN, HIGH);

  return info;
}

void Transceiver::printDeviceInfo() {
  PartInfo partInfo = readPartInfo();
  FuncInfo funcInfo = readFuncInfo();

  Serial.println("Device Information:");
  Serial.println("-------------------");
  
  Serial.print("Chip Revision: ");
  Serial.println(partInfo.chipRev, HEX);
  
  Serial.print("Part Number: ");
  Serial.println(partInfo.part, HEX);
  
  Serial.print("Part Build: ");
  Serial.println(partInfo.partBuild, HEX);
  
  Serial.print("ID: ");
  Serial.println(partInfo.id, HEX);
  
  Serial.print("Customer ID: ");
  Serial.println(partInfo.customer, HEX);
  
  Serial.print("Rom ID: ");
  Serial.println(partInfo.romId, HEX);
  
  Serial.print("External Revision Number: ");
  Serial.println(funcInfo.revExt, HEX);
  
  Serial.print("Branch Revision Number: ");
  Serial.println(funcInfo.revBranch, HEX);
  
  Serial.print("Internal Revision Number: ");
  Serial.println(funcInfo.revInt, HEX);
  
  Serial.print("ID of Applied Patch: ");
  Serial.println(funcInfo.patch, HEX);
  
  Serial.print("Current Functional Mode: ");
  Serial.println(funcInfo.func == 0 ? "Boot mode" : "Running main application image");
  
  Serial.println("-------------------");
}

