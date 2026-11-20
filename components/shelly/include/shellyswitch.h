#ifndef SHELLYSWITCH_H
#define SHELLYSWITCH_H

#pragma once

#include <switch.h>

class ShellyDevice;

class ShellySwitch : public Switch {
public:
    ShellySwitch();
    ShellySwitch(Device *p, int32_t u);
    ~ShellySwitch();
    void setOutput(int32_t val);
protected:
    int32_t sockNum;
};

#endif