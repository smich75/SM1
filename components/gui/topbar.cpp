#include "topbar.h"
#include <gui.h>

extern "C" {
    LV_IMAGE_DECLARE(wifi_icon);
    LV_IMAGE_DECLARE(wifi_off_icon);
}

TopBar::TopBar() {
}

TopBar::~TopBar() {
}

void TopBar::setup()    {
    esp_lv_adapter_lock(-1);
    base=lv_obj_create(lv_screen_active());
    lv_obj_set_pos(base, 0, 0);
    lv_obj_set_size(base, lv_pct(100), 48);
    lv_obj_add_style(base, &GUI::get()->bar_style, 0);

    wifiIcon=lv_image_create(base);
    lv_image_set_src(wifiIcon, &wifi_icon);
    lv_obj_set_pos(wifiIcon, lv_pct(93), 1);
    lv_obj_set_style_image_recolor(wifiIcon, GUI::get()->def_fg_color, LV_PART_MAIN);
    lv_obj_set_style_image_recolor_opa(wifiIcon, LV_OPA_100, LV_PART_MAIN);
    esp_lv_adapter_unlock();
}

void TopBar::enableWifi()   {
    esp_lv_adapter_lock(-1);
    lv_image_set_src(wifiIcon, &wifi_icon);
    lv_obj_set_style_image_recolor(wifiIcon, GUI::get()->def_fg_color, LV_PART_MAIN);
    esp_lv_adapter_unlock();
}

void TopBar::disableWifi()  {
    esp_lv_adapter_lock(-1);
    lv_image_set_src(wifiIcon, &wifi_off_icon);
    lv_obj_set_style_image_recolor(wifiIcon, GUI::get()->def_fg_color, LV_PART_MAIN);
    esp_lv_adapter_unlock();
}
