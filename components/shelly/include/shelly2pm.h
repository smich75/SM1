#ifndef SHELLY2PM_H
#define SHELLY2PM_H

#pragma once

#include <shellyswitch.h>
#include <shellydevice.h>

#define S2PMCONF_SWITCH 0
#define S2PMCONF_COVER  1

class Shelly2PM : public ShellyDevice {
public:
    Shelly2PM();
    ~Shelly2PM();
private:
};

#endif