#ifndef SHELLY_GENERIC_H
#define SHELLY_GENERIC_H

#include <lvgl.h>
#include <esp_lv_adapter.h>
#include <shellyunit.h>

#define PALETTECOLOR LV_PALETTE_BLUE_GREY

#pragma once

class ShellyGeneric {
public:
    ShellyGeneric();
    ~ShellyGeneric();
    virtual lv_obj_t *createGUIObject(lv_obj_t *parent, int xPos, int yPos);
    const lv_image_dsc_t    *imgDsc;
    void setName(char *_name);
    char *getName();
private:
    char *name;
};

#endif