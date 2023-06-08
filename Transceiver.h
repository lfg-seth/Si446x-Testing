#ifndef Transceiver_h
#define Transceiver_h

#include "SPI.h"

#define SS_PIN 10
#define IRQ_PIN 2

struct PartInfo {
  uint8_t chipRev;
  uint16_t part;
  uint8_t partBuild;
  uint16_t id;
  uint8_t customer;
  uint8_t romId;
};

struct FuncInfo {
  uint8_t revExt;
  uint8_t revBranch;
  uint8_t revInt;
  uint16_t patch;
  uint8_t func;
};

class Transceiver {
  public:
    Transceiver();
    void init();
    void printDeviceInfo();
    void sendData(String data);
    String receiveData();
    void startTransmit();
    void startReceive();
    void readFIFOInfo(uint8_t &rxCount, uint8_t &txSpace);
    PartInfo readPartInfo();
    FuncInfo readFuncInfo();
    // Methods for specific SPI commands can be added here

  private:
    void writeRegister(uint8_t address, uint8_t value);
    uint8_t readRegister(uint8_t address);
};

#endif
