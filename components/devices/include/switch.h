#ifndef SWITCH_H
#define SWITCH_H

#pragma once

#include <component.h>

class Device;

class Switch : public Component {
public:
    Switch();
    Switch(Device *d, int32_t u=0);
    ~Switch();
private:
    uint32_t value;
    uint32_t power;
};

#endif