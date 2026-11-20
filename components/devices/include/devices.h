#ifndef DEVICE_H
#define DEVICE_H

#pragma once
#include <cstdint>
#include <vector>
#include <component.h>

class Device {
public:
    Device()    {};
    ~Device()   {};
    void setName(char *n)   {   deviceName=n;   }
    char *getName() {   return deviceName;  }
    void setType(uint32_t val)  {   type=val;  }
    uint32_t getType()  {   return type;    }
protected:
    char *deviceName;
    uint32_t    type;
    std::vector<Component *> units;
    uint32_t unitsNum;
    bool online;
    uint8_t failCnt;
    uint32_t nextPollMS;
    uint32_t ip;
};

#endif