#include "topbar.h"
#include <gui.h>

extern "C" {
    LV_IMAGE_DECLARE(wifi_icon);
}

TopBar::TopBar() {
}

TopBar::~TopBar() {
}

void TopBar::setup()    {
    esp_lv_adapter_lock(-1);
    base=lv_obj_create(lv_screen_active());
    lv_obj_set_pos(base, 0, 0);
    lv_obj_set_size(base, lv_pct(100), 64);
    lv_obj_set_style_radius(base, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(base, GUI::get()->barColor, LV_PART_MAIN);
    lv_obj_set_style_border_width(base, 0, LV_PART_MAIN);
    GUI::get()->setGapBorderValues(base, 0, 0, 0, 0, 0, 0);

    wifiIcon=lv_image_create(base);
    lv_image_set_src(wifiIcon, &wifi_icon);
    lv_obj_set_pos(wifiIcon, lv_pct(93), 1);
    lv_obj_set_style_image_recolor(wifiIcon, lv_palette_darken(LV_PALETTE_RED, 3), LV_PART_MAIN);
    lv_obj_set_style_image_recolor_opa(wifiIcon, LV_OPA_100, LV_PART_MAIN);
    esp_lv_adapter_unlock();
}

void TopBar::enableWifi()   {
    esp_lv_adapter_lock(-1);
    lv_obj_set_style_image_recolor(wifiIcon, lv_palette_darken(LV_PALETTE_GREEN, 3), LV_PART_MAIN);
    esp_lv_adapter_unlock();
}

void TopBar::disableWifi()  {
    esp_lv_adapter_lock(-1);
    lv_obj_set_style_image_recolor(wifiIcon, lv_palette_darken(LV_PALETTE_RED, 3), LV_PART_MAIN);
    esp_lv_adapter_unlock();
}
