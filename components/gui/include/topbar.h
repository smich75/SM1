#ifndef TOPBAR_H
#define TOPBAR_H

#include <lvgl.h>

#pragma once

class TopBar {
public:
    TopBar();
    ~TopBar();
    void setup();
    void enableWifi();
    void disableWifi();
private:
    lv_obj_t    *base;
    lv_obj_t    *wifiIcon;
};

#endif