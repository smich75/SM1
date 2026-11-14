#include "shelly_generic.h"
#include <gui.h>

extern const lv_image_dsc_t shelly1pm;

ShellyGeneric::ShellyGeneric() {
    imgDsc=&shelly1pm;
}

ShellyGeneric::~ShellyGeneric() {
}

lv_obj_t *ShellyGeneric::createGUIObject(lv_obj_t *parent, int xPos, int yPos)      {
    return GUI::get()->createSwitchUI(parent, xPos, yPos, NULL, name);
}

void ShellyGeneric::setName(char *_name)    {
    name=_name;
}

char *ShellyGeneric::getName()  {
    return name;
}
