#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once
#include <cstdint>

class Device;

class Component {
public:
    Component();
    Component(Device *p, int32_t u=0);
    ~Component();
private:
    Device *parent;
    int32_t unit;
};

#endif