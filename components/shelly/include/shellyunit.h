#ifndef UNIT_H
#define UNIT_H

#pragma once

class ShellyGeneric;

class ShellyUnit {
public:
    ShellyUnit();
    ~ShellyUnit();

private:
    ShellyGeneric *parent;
};

#endif