#include <cstdio>
#include <waveshare__esp32_p4_wifi6_touch_lcd_7b/include/bsp/esp32_p4_wifi6_touch_lcd_7b.h>
#include "gui.h"

GUI *GUI::ptr=NULL;

extern "C" {
    LV_FONT_DECLARE(open_sans_14b);
    LV_FONT_DECLARE(open_sans_18b);
    LV_FONT_DECLARE(open_sans_24b);
}

extern "C" {
    LV_IMG_DECLARE(lightbulb);
    LV_IMG_DECLARE(arrowup);
    LV_IMG_DECLARE(arrowdown);
    LV_IMG_DECLARE(settings);
    LV_IMG_DECLARE(shelly1pm);
    LV_IMG_DECLARE(shelly2pm);
}

#define CFG_OFFSET (GUI::get()->switchWidth/3)*2

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

void switchCB(lv_event_t *e)    {
    lv_obj_t *target=(lv_obj_t *)lv_event_get_target(e);
    printf("Click on switch 0x%x\n", (int)target);
}

lv_obj_t *GUI::createStdFrame(lv_obj_t *parent, int32_t xPos, int32_t yPos, int32_t width, int32_t height)  {
    lv_obj_t *obj=lv_obj_create(parent);
    if (obj)   {
        lv_obj_set_pos(obj, xPos, yPos);
        lv_obj_set_size(obj, width, height);
        lv_obj_add_style(obj, &frameStyle, 0);
    }
    return obj;
}

lv_obj_t *GUI::createStdLabel(lv_obj_t *parent, int32_t xPos, int32_t yPos, int32_t width, int32_t height, char *text)  {
    lv_obj_t *label=lv_label_create(parent);
    if (label)  {
        lv_obj_set_pos(label, xPos, yPos);
        lv_obj_set_size(label, width, height);
        if (text)   lv_label_set_text(label, text);
        lv_obj_set_style_text_font(label, GUI::get()->get_font(FONT_SMALL), LV_PART_MAIN);
        lv_obj_set_style_text_color(label, defLabelColor, LV_PART_MAIN);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    }
    return label;
}

lv_obj_t *GUI::createStdSlider(lv_obj_t *parent, int32_t xPos, int32_t yPos, int32_t width, int32_t height, int32_t min, int32_t max, int32_t val)  {
    lv_obj_t *obj=lv_slider_create(parent);
    if (obj)    {
        lv_obj_set_pos(obj, xPos, yPos);
        lv_obj_set_size(obj, width, height);
        lv_slider_set_range(obj, min, max);
        lv_slider_set_value(obj, val, LV_ANIM_OFF);
        lv_obj_add_style(obj, &sliderStyle, 0);
        lv_obj_add_style(obj, &defKnobStyle, LV_PART_KNOB);
        lv_obj_add_style(obj, &selKnobStyle, LV_PART_KNOB|LV_STATE_PRESSED);
        lv_obj_add_style(obj, &indicatorStyle, LV_PART_INDICATOR);
    }
    return obj;
}

lv_obj_t *GUI::createStdImgButton(lv_obj_t *parent, int32_t xPos, int32_t yPos, int32_t width, int32_t height, const lv_img_dsc_t *img)  {
    lv_obj_t *obj=lv_button_create(parent);
    if (obj)    {
        lv_obj_set_pos(obj, xPos, yPos);
        lv_obj_set_size(obj, width, height);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_PRESS_LOCK);
        lv_obj_add_style(obj, &defButtonStyle, LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &selButtonStyle, LV_STATE_PRESSED);
        lv_obj_add_style(obj, &selButtonStyle, LV_STATE_CHECKED);
        lv_obj_add_event_cb(obj, switchCB, LV_EVENT_CLICKED, NULL);
        if (img)    {
            lv_obj_t *image=lv_image_create(obj);
            lv_image_set_src(image, img);
            lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
        }
    }
    return obj;
}

lv_obj_t *GUI::create_switch_ui(lv_obj_t *parent, int16_t xPos, int16_t yPos, lv_image_dsc_t *deviceImg, char *labelTxt)   {
    lv_obj_t *obj=NULL, *cont=NULL, *label=NULL;
    if (parent==NULL)   parent=lv_screen_active();
    esp_lv_adapter_lock(-1);
    cont=createStdFrame(parent, xPos, yPos, GUI::get()->switchWidth, GUI::get()->switchHeight);
    obj=createStdImgButton(cont, 0, 0, CFG_OFFSET, lv_pct(80), &lightbulb);
    obj=createStdImgButton(cont, CFG_OFFSET, 0, lv_pct(30), lv_pct(80), (const lv_img_dsc_t *)deviceImg);
    label=createStdLabel(cont, 0, lv_pct(85), lv_pct(100), lv_pct(15), labelTxt);
    esp_lv_adapter_unlock();
    return obj;
}

void GUI::create_main_ui() {
    topBar=new TopBar;
    topBar->setup();
    esp_lv_adapter_lock(-1);
    lv_obj_t *tabView=lv_tabview_create(lv_screen_active());
    lv_tabview_set_tab_bar_position(tabView, LV_DIR_BOTTOM);
    lv_obj_set_pos(tabView, 0, 64);
    lv_obj_set_size(tabView, lv_pct(100), 600-64);
    //lv_obj_set_style_radius(tabView, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabView, defBGColor, LV_PART_MAIN);
    //lv_obj_set_style_bg_opa(tabView, LV_OPA_100, LV_PART_MAIN);
    //lv_obj_set_style_border_width(tabView, 0, LV_PART_MAIN);
    //lv_obj_set_style_margin_all(tabView, 0, LV_PART_MAIN);
    //lv_obj_set_style_outline_width(tabView, 0, LV_PART_MAIN);
    //lv_obj_set_style_pad_all(tabView, 0, LV_PART_MAIN);
    //lv_obj_set_style_pad_gap(tabView, 0, LV_PART_MAIN);
    
    lv_obj_t *tab1, *tab2, *tab3, *tab4;
    tab1=lv_tabview_add_tab(tabView, "Devices");
    //lv_obj_set_style_bg_color(tab1, defBGColor, LV_PART_MAIN);
    //lv_obj_set_style_bg_opa(tab1, LV_OPA_100, LV_PART_MAIN);
    //lv_obj_set_style_border_width(tab1, 0, LV_PART_MAIN);
    //lv_obj_set_style_margin_all(tab1, 0, LV_PART_MAIN);
    //lv_obj_set_style_outline_width(tab1, 0, LV_PART_MAIN);
    //lv_obj_set_style_pad_all(tab1, 0, LV_PART_MAIN);
    //lv_obj_set_style_pad_gap(tab1, 0, LV_PART_MAIN);
    tab2=lv_tabview_add_tab(tabView, "Rooms");
    lv_obj_t *lv0=create_listview(tab2, 10, 10, 600, 400);
    add_device_item(lv0, "Shelly 1PM", get_device_image(SHELLY1PM), 0);
    add_device_item(lv0, "Shelly 2PM", get_device_image(SHELLY2PM), 1);
    add_device_item(lv0, "Shelly 2PM", get_device_image(SHELLY2PM), 2);
    add_device_item(lv0, "Shelly 2PM", get_device_image(SHELLY2PM), 3);
    add_device_item(lv0, "Shelly 1PM", get_device_image(SHELLY1PM), 4);
    tab3=lv_tabview_add_tab(tabView, "Settings");
    tab4=lv_tabview_add_tab(tabView, "Shelly");
    tab4=lv_tabview_add_tab(tabView, "Alarm");
    tab4=lv_tabview_add_tab(tabView, "Configuration");

    lv_obj_t *tabBar=lv_tabview_get_tab_bar(tabView);
    uint32_t tab_count = lv_tabview_get_tab_count(tabView);
    for(uint32_t i=0; i<tab_count; i++) {
        lv_obj_t * button=lv_obj_get_child(tabBar, i);
        lv_obj_set_style_text_font(button, get_font(FONT_MEDIUM), 0);
        lv_obj_set_style_bg_color(button, defBGColor, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(button, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(button, defLabelColor, LV_PART_MAIN | LV_STATE_DEFAULT);

        /* Stato attivo (tab selezionata) */
        lv_obj_set_style_bg_color(button, defFGColor, LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(button, defBGColor, LV_PART_MAIN | LV_STATE_CHECKED);
        
        /* Indicatore inferiore sulla tab attiva */
        lv_obj_set_style_border_color(button, selSwitchColor, LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_width(button, 3, LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_border_side(button, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_CHECKED);
    }
    mainPage=tab1;

    lv_obj_update_layout(tabView);
    lv_obj_invalidate(lv_tabview_get_tab_bar(tabView));
    esp_lv_adapter_unlock();
}

lv_obj_t *GUI::create_double_switch_ui(lv_obj_t *parent, int16_t xPos, int16_t yPos, lv_image_dsc_t *deviceImg,  char *labelTxt)    {
    lv_obj_t *obj=NULL, *cont=NULL, *label=NULL, *valText=NULL;
    lv_subject_t *subject=(lv_subject_t *)lv_malloc(sizeof(lv_subject_t));
    if (parent==NULL)   parent=lv_screen_active();
    esp_lv_adapter_lock(-1);
    cont=createStdFrame(parent, xPos, yPos, GUI::get()->switchWidth, GUI::get()->switchHeight);
    obj=createStdImgButton(cont, 0, 0, lv_pct(35), lv_pct(60), &arrowup);
    obj=createStdImgButton(cont, lv_pct(35), 0, lv_pct(35), lv_pct(60), &arrowdown);
    obj=createStdImgButton(cont, CFG_OFFSET, 0, lv_pct(30), lv_pct(60), (const lv_img_dsc_t *)deviceImg);
    obj=createStdSlider(cont, lv_pct(10), lv_pct(65), lv_pct(80), lv_pct(10), 0, 100, 50);
    label=createStdLabel(cont, 0, lv_pct(85), lv_pct(85), lv_pct(15), labelTxt);
    valText=createStdLabel(cont, lv_pct(85), lv_pct(85), lv_pct(15), lv_pct(15), "--");
    lv_subject_init_int(subject, 50);
    lv_slider_bind_value(obj, subject);
    lv_label_bind_text(valText, subject, "%d");
    esp_lv_adapter_unlock();
    return obj;
}

lv_obj_t *GUI::create_listview(lv_obj_t *parent, int16_t xPos, int16_t yPos, int16_t xSize, int16_t ySize)  {
    lv_obj_t *list=lv_obj_create(parent);
    if (list)   {
        lv_obj_set_pos(list, xPos, yPos);
        lv_obj_set_size(list, xSize, ySize);
        //lv_obj_center(list);
        lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_all(list, 0, 0);
        lv_obj_set_style_pad_row(list, 0, 0);
        lv_obj_set_style_radius(list, 6, 0);
        lv_obj_set_style_clip_corner(list, true, 0);
    }
    return list;
}

static lv_obj_t *selected_row=NULL;

static void row_event_cb(lv_event_t *e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lv_obj_t *clicked_row =(lv_obj_t *)lv_event_get_target(e);

        // Deseleziona la riga precedente, se esiste
        if(selected_row!=NULL&&selected_row!=clicked_row) {
            lv_obj_clear_state(selected_row, LV_STATE_CHECKED);
        }

        // Imposta la nuova riga come selezionata
        lv_obj_add_state(clicked_row, LV_STATE_CHECKED);
        selected_row = clicked_row;

        intptr_t index = (intptr_t)lv_event_get_user_data(e);
        LV_LOG_USER("Riga selezionata: %d", (int)index);
    }
}

lv_obj_t *GUI::add_device_item(lv_obj_t *parent, char *text, lv_img_dsc_t *img_dsc, int32_t index)   {
    lv_obj_t *row= lv_obj_create(parent);
    lv_obj_set_size(row, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_set_style_radius(row, 0, 0);
    lv_obj_set_style_border_width(row, 1, 0);
    lv_obj_set_style_border_side(row, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_color(row, lv_palette_lighten(LV_PALETTE_GREY, 2), 0);
    lv_obj_set_style_bg_color(row, lv_color_white(), 0);
    lv_obj_set_style_pad_ver(row, 12, 0);
    lv_obj_set_style_pad_hor(row, 10, 0);
    lv_obj_set_style_pad_column(row, 12, 0);

    lv_obj_set_style_bg_color(row, lv_palette_lighten(LV_PALETTE_BLUE, 4), LV_STATE_PRESSED);

    lv_obj_set_style_bg_color(row, lv_palette_lighten(LV_PALETTE_BLUE, 3), LV_STATE_CHECKED);
    lv_obj_set_style_text_color(row, lv_palette_darken(LV_PALETTE_BLUE, 3), LV_STATE_CHECKED);

    lv_obj_add_flag(row, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(row, row_event_cb, LV_EVENT_CLICKED, (void *)(intptr_t)index);

    lv_obj_t *img = lv_img_create(row);
    lv_img_set_src(img, img_dsc);
    
    lv_obj_t * label = lv_label_create(row);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, get_font(FONT_MEDIUM), 0);
    lv_obj_set_flex_grow(label, 1);

    return row;
}

const lv_font_t *GUI::get_font(int size) {
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

void GUI::setup_gui()    {
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
    lv_indev_set_scroll_limit(lv_indev_get_act(), 2);
    lv_indev_set_gesture_min_distance(lv_indev_get_act(), 25);
    esp_lv_adapter_lock(-1);

    defPaletteColor=LV_PALETTE_BLUE_GREY;
    selPaletteColor=LV_PALETTE_RED;
    defBGColor=lv_palette_darken(defPaletteColor, 2);
    defFGColor=lv_palette_darken(defPaletteColor, 4);
    defSwitchColor=lv_palette_main(defPaletteColor);
    selSwitchColor=lv_palette_lighten(selPaletteColor, 2);
    defKnobColor=lv_palette_lighten(defPaletteColor, 1);
    selKnobColor=lv_palette_lighten(defPaletteColor, 2);
    defIndicatorColor=lv_palette_lighten(selPaletteColor, 2);
    defLabelColor=lv_color_darken(lv_color_white(), 1);
    defBarColor=lv_palette_lighten(defPaletteColor, 1);
    switchWidth=DEF_SWITCH_WIDTH;
    switchHeight=DEF_SWITCH_HEIGHT;
    smallFont=&open_sans_14b;
    mediumFont=&open_sans_18b;
    bigFont=&open_sans_24b;

    deviceImages[SHELLY1PM]=(lv_img_dsc_t *)&shelly1pm;
    deviceImages[SHELLY2PM]=(lv_img_dsc_t *)&shelly2pm;
    
    lv_style_init(&switchStyle);

    lv_style_init(&barStyle);
    lv_style_set_margin_all(&barStyle, 0);
    lv_style_set_pad_all(&barStyle, 0);
    lv_style_set_pad_row(&barStyle, 0);
    lv_style_set_pad_column(&barStyle, 0);
    lv_style_set_border_width(&barStyle, 0);
    lv_style_set_shadow_width(&barStyle, 0);
    lv_style_set_bg_opa(&barStyle, LV_OPA_100);
    lv_style_set_bg_color(&barStyle, defBarColor);
    lv_style_set_pad_gap(&barStyle, 0);

    lv_style_init(&frameStyle);
    lv_style_set_margin_all(&frameStyle, 0);
    lv_style_set_pad_all(&frameStyle, 0);
    lv_style_set_pad_row(&frameStyle, 0);
    lv_style_set_pad_column(&frameStyle, 0);
    lv_style_set_border_width(&frameStyle, 2);
    lv_style_set_shadow_width(&frameStyle, 0);
    lv_style_set_bg_opa(&frameStyle, 0);
    lv_style_set_pad_gap(&frameStyle, 0);

    lv_style_init(&sliderStyle);
    lv_style_set_bg_color(&sliderStyle, lv_color_white());
    lv_style_set_margin_all(&sliderStyle, 0);
    lv_style_set_pad_all(&sliderStyle, 0);
    lv_style_set_pad_row(&sliderStyle, 0);
    lv_style_set_pad_column(&sliderStyle, 0);
    lv_style_set_border_width(&sliderStyle, 0);
    lv_style_set_shadow_width(&sliderStyle, 0);
    lv_style_set_bg_opa(&sliderStyle, 0);
    lv_style_set_pad_gap(&sliderStyle, 0);
    lv_style_set_outline_pad(&sliderStyle, 0);
    lv_style_set_outline_width(&sliderStyle, 0);
    lv_style_set_radius(&sliderStyle, 0);

    lv_style_init(&defKnobStyle);
    lv_style_set_bg_color(&defKnobStyle, defKnobColor);
    lv_style_set_radius(&defKnobStyle, 2);

    lv_style_init(&selKnobStyle);
    lv_style_set_bg_color(&selKnobStyle, selKnobColor);

    lv_style_init(&indicatorStyle);
    lv_style_set_bg_color(&indicatorStyle, defIndicatorColor);
    lv_style_set_radius(&indicatorStyle, 2);

    lv_style_init(&defButtonStyle);
    lv_style_set_bg_color(&defButtonStyle, defSwitchColor);
    lv_style_set_margin_all(&defButtonStyle, 0);
    lv_style_set_pad_all(&defButtonStyle, 0);
    lv_style_set_border_width(&defButtonStyle, 0);
    lv_style_set_shadow_width(&defButtonStyle, 0);
    lv_style_set_outline_pad(&defButtonStyle, 0);
    lv_style_set_outline_width(&defButtonStyle, 0);
    lv_style_set_radius(&defButtonStyle, 2);
    
    lv_style_init(&selButtonStyle);
    lv_style_set_bg_color(&selButtonStyle, selSwitchColor);

    lv_obj_set_style_bg_color(lv_screen_active(), defBGColor, 0);
    lv_obj_set_style_bg_opa(lv_screen_active(), LV_OPA_COVER, 0);
    esp_lv_adapter_unlock();
}

GUI::GUI()  {
};
