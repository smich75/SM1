#include "shellyswitch.h"

ShellySwitch::ShellySwitch() : Switch(NULL, 0) {
}

ShellySwitch::ShellySwitch(Device *p, int32_t u) : Switch(p, u)   {
}

ShellySwitch::~ShellySwitch() {
}

void ShellySwitch::setOutput(int32_t val)    {
}
