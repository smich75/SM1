#ifndef SHELLY_1PM_H
#define SHELLY_1PM_H

#pragma once

#include <shelly_generic.h>
#include <shellyswitch.h>

class Shelly1PM : public ShellyGeneric {
public:
    Shelly1PM();
    ~Shelly1PM();

private:
    ShellySwitch  unit0;
};

#endif