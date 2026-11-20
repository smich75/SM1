#include "shelly2pm.h"

Shelly2PM::Shelly2PM() {
    unitsNum=2;
    units.resize(2);
    for (int i=0; i<unitsNum; i++)  {
        units[i]=new ShellySwitch(this, i);
    }
}

Shelly2PM::~Shelly2PM() {
}