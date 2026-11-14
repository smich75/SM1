#ifndef SHELLY2PM_H
#define SHELLY2PM_H

#pragma once

#include <shelly_generic.h>
#include <shellyswitch.h>

class Shelly2PM : public ShellyGeneric {
public:
    Shelly2PM();
    ~Shelly2PM();
private:
    ShellySwitch unit0;
    ShellySwitch unit1;
};

#endif