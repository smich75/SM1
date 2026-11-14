#include <cstdio>
#include <waveshare__esp32_p4_wifi6_touch_lcd_7b/include/bsp/esp32_p4_wifi6_touch_lcd_7b.h>
#include "gui.h"

extern "C" {
    LV_FONT_DECLARE(open_sans_14b);
    LV_FONT_DECLARE(open_sans_18b);
    LV_FONT_DECLARE(open_sans_24b);
}

GUI *GUI::ptr=NULL;

//                              DISPLAY DIMMING
static bool is_dimmed = false;
static bool dimming=false;
static bool is_off = false;
static int dimLevel=100;
static lv_obj_t *lockScreen=NULL;

void dimDisplay(lv_timer_t *t) {
    uint32_t inactive_time = lv_display_get_inactive_time(NULL);
    if (dimLevel<25)  {
        if (lockScreen==NULL)   {
            lockScreen=lv_obj_create(lv_layer_top());
            lv_obj_remove_style_all(lockScreen);
            lv_obj_set_size(lockScreen, lv_pct(100), lv_pct(100));
            lv_obj_add_flag(lockScreen, LV_OBJ_FLAG_CLICKABLE);
        }   
    }   else    {
        if (lockScreen) {
            lv_obj_del(lockScreen);
            lockScreen=NULL;
        }    
    }
    if (inactive_time > OFF_TIME_MS) {
        if (!is_off) {
            dimming=true;
            dimLevel--;
            bsp_display_brightness_set(dimLevel); // Turn off backlight
            if (dimLevel==5) {
                is_off = true;
                dimming=false;
            }
        }
    } else if (inactive_time > DIM_TIME_MS) {
        if (!is_dimmed) {
            dimming=true;
            dimLevel--;
            bsp_display_brightness_set(dimLevel); // Dim backlight to 25%
            if (dimLevel==25)   {
                is_dimmed = true;
                is_off = false;
                dimming=false;
            }
        }
    } else {
        if (is_dimmed || is_off || dimming) {
            dimLevel++;
            bsp_display_brightness_set(dimLevel); // Restore full brightness
            if (dimLevel==100)  {
                is_dimmed = false;
                is_off = false;
                dimming=false;
            }
        }
    }
}

void GUI::setGapBorderValues(lv_obj_t *obj, int16_t margin, int16_t padAll, int16_t padRow, int16_t padColumn, int16_t border, int16_t shadow) {
    lv_obj_set_style_margin_all(obj, margin, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj, padAll, LV_PART_MAIN);
    lv_obj_set_style_pad_row(obj, padRow, LV_PART_MAIN);
    lv_obj_set_style_pad_column(obj, padColumn, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj, border, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(obj, shadow, LV_PART_MAIN);
}

lv_obj_t *GUI::createSwitchUI(lv_obj_t *parent, int16_t xPos, int16_t yPos, lv_image_dsc_t *img, char *label) {
    lv_obj_t *obj=NULL, *cont=NULL, *text=NULL;
    if (parent==NULL)   parent=lv_screen_active();
    esp_lv_adapter_lock(-1);

    //                              CONTAINER
    cont=lv_obj_create(parent);
    lv_obj_set_pos(cont, xPos, yPos);
    lv_obj_set_size(cont, GUI::get()->switchWidth, GUI::get()->switchHeight);
    lv_obj_set_style_bg_opa(cont, 0, LV_PART_MAIN);
    setGapBorderValues(cont, 0, 0, 0, 0, 2, 0);
    lv_obj_set_style_pad_gap(cont, 0, LV_PART_MAIN);
    
    //                              BUTTON
    obj=lv_button_create(cont);
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, lv_pct(100), lv_pct(80));
    lv_obj_set_style_bg_color(obj, defSwitchColor, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, selSwitchColor, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, selSwitchColor, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN);
    setGapBorderValues(obj, 0, 0, 0, 0, 0, 0);
    lv_obj_set_style_pad_gap(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_pad(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN);

    //                              TEXT
    text=lv_label_create(cont);
    lv_obj_set_pos(text, 0, lv_pct(85));
    lv_obj_set_size(text, lv_pct(100), lv_pct(15));
    if (label)   lv_label_set_text(text, label);
    lv_obj_set_style_text_font(text, GUI::get()->getFont(FONT_SMALL), LV_PART_MAIN);
    lv_obj_set_style_text_color(text, labelDefault, LV_PART_MAIN);
    lv_obj_set_style_text_align(text, LV_TEXT_ALIGN_CENTER, 0);
    esp_lv_adapter_unlock();
    return obj;
}


void testLPCB(lv_event_t *e)   {
    printf("LONG PRESS\n");
}

void testPCB(lv_event_t *e)   {
    printf("CLICKED\n");
}

void GUI::createMainUI() {
    topBar=new TopBar;
    topBar->setup();

    mainPage=lv_obj_create(lv_screen_active());
    lv_obj_set_pos(mainPage, 0, 50);
    lv_obj_set_size(mainPage, lv_pct(100), 600-50);
    lv_obj_set_style_radius(mainPage, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(mainPage, backgroundColor, LV_PART_MAIN);
    lv_obj_set_style_border_width(mainPage, 0, LV_PART_MAIN);
}

lv_obj_t *GUI::createDoubleSwitchUI(lv_obj_t *parent, int16_t xPos, int16_t yPos, lv_image_dsc_t *img1, lv_image_dsc_t *img2, char *label)    {
    lv_obj_t *obj=NULL, *cont=NULL, *hcont=NULL, *text=NULL;
    if (parent==NULL)   parent=lv_screen_active();
    esp_lv_adapter_lock(-1);

    cont=lv_obj_create(parent);
    lv_obj_set_pos(cont, xPos, yPos);
    lv_obj_set_size(cont, GUI::get()->switchWidth, GUI::get()->switchHeight);
    lv_obj_set_style_bg_opa(cont, 0, LV_PART_MAIN);
    setGapBorderValues(cont, 0, 0, 0, 0, 2, 0);
    lv_obj_set_style_pad_gap(cont, 0, LV_PART_MAIN);

    obj=lv_button_create(cont);
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, lv_pct(50), lv_pct(60));
    lv_obj_set_style_bg_color(obj, defSwitchColor, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, selSwitchColor, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, selSwitchColor, LV_PART_MAIN|LV_STATE_CHECKED);
    setGapBorderValues(obj, 0, 0, 0, 0, 0, 0);
    lv_obj_set_style_pad_gap(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_pad(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN);
    lv_obj_add_event_cb(obj, testLPCB, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(obj, testPCB, LV_EVENT_CLICKED, NULL);

    obj=lv_button_create(cont);
    lv_obj_set_pos(obj, lv_pct(50), 0);
    lv_obj_set_size(obj, lv_pct(50), lv_pct(60));
    lv_obj_set_style_bg_color(obj, defSwitchColor, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, selSwitchColor, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, selSwitchColor, LV_PART_MAIN|LV_STATE_CHECKED);
    setGapBorderValues(obj, 0, 0, 0, 0, 0, 0);
    lv_obj_set_style_pad_gap(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_pad(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN);
    lv_obj_add_event_cb(obj, testLPCB, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(obj, testPCB, LV_EVENT_CLICKED, NULL);

    obj=lv_slider_create(cont);
    lv_obj_set_pos(obj, lv_pct(10), lv_pct(65));
    lv_obj_set_size(obj, lv_pct(80), lv_pct(10));
    lv_obj_set_style_bg_color(obj, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, knobDefault, LV_PART_KNOB);
    lv_obj_set_style_bg_color(obj, knobPressed, LV_PART_KNOB|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, knobPressed, LV_PART_KNOB|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(obj, knobIndicator, LV_PART_INDICATOR);
    setGapBorderValues(obj, 0, 0, 0, 0, 0, 0);
    lv_obj_set_style_pad_gap(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_pad(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN);

    //                              TEXT
    text=lv_label_create(cont);
    lv_obj_set_pos(text, 0, lv_pct(85));
    lv_obj_set_size(text, lv_pct(100), lv_pct(15));
    if (label)   lv_label_set_text(text, label);
    //lv_obj_center(text);
    lv_obj_set_style_text_font(text, GUI::get()->getFont(FONT_SMALL), LV_PART_MAIN);
    lv_obj_set_style_text_color(text, labelDefault, LV_PART_MAIN);
    lv_obj_set_style_text_align(text, LV_TEXT_ALIGN_CENTER, 0);

    esp_lv_adapter_unlock();
    return obj;
}

const lv_font_t *GUI::getFont(int size) {
    switch (size)   {
        case FONT_SMALL:
            return smallFont;
        case FONT_MEDIUM:
            return mediumFont;
        case FONT_BIG:
            return bigFont;
        default:
            return smallFont;
    }
}

void GUI::setupGUI()    {
    bsp_display_cfg_t cfg = {
        .lv_adapter_cfg = ESP_LV_ADAPTER_DEFAULT_CONFIG(),
        .rotation = ESP_LV_ADAPTER_ROTATE_180,
        .tear_avoid_mode = ESP_LV_ADAPTER_TEAR_AVOID_MODE_TRIPLE_PARTIAL,
        .touch_flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
    };
    lv_display_t *disp=bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();
    bsp_display_brightness_set(100);
    lv_timer_create(dimDisplay, 10, NULL);
    esp_lv_adapter_lock(-1);

    lv_style_init(&switchStyle);
    lv_style_init(&barStyle);
    lv_style_init(&defButtonStyle);
    lv_style_init(&selButtonStyle);

    lv_style_set_bg_color(&defButtonStyle, defSwitchColor);
    lv_style_set_bg_color(&selButtonStyle, selSwitchColor);

    mainColor=LV_PALETTE_BLUE_GREY;
    mainSelectedColor=LV_PALETTE_RED;
    backgroundColor=lv_palette_darken(mainColor, 2);
    defSwitchColor=lv_palette_main(mainColor);
    selSwitchColor=lv_palette_lighten(mainSelectedColor, 2);
    knobDefault=lv_palette_lighten(mainColor, 1);
    knobPressed=lv_palette_lighten(mainColor, 2);
    knobIndicator=lv_palette_lighten(mainSelectedColor, 2);
    labelDefault=lv_color_darken(lv_color_white(), 1);
    barColor=lv_palette_lighten(mainColor, 2);
    switchWidth=DEF_SWITCH_WIDTH;
    switchHeight=DEF_SWITCH_HEIGHT;
    smallFont=&open_sans_14b;
    mediumFont=&open_sans_18b;
    bigFont=&open_sans_24b;

    lv_obj_set_style_bg_color(lv_screen_active(), backgroundColor, 0);
    lv_obj_set_style_bg_opa(lv_screen_active(), LV_OPA_COVER, 0);
    esp_lv_adapter_unlock();
}

GUI::GUI()  {
};
