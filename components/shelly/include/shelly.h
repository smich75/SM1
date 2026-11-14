#ifndef SHELLYES_H
#define SHELLYES_H


#include <vector>
#include <shelly_generic.h>
#include <shelly1pm.h>
#include <shelly2pm.h>

class Shelly  {
    public:
    Shelly() {};
    ~Shelly() {};
    std::vector<ShellyGeneric> devices;
};

#endif

