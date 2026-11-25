#ifndef GUI_H
#define GUI_H

#include <cstdint>
#include <cstdlib>
#include <lvgl.h>
#include <esp_lv_adapter.h>
#include <topbar.h>

enum FONT_SIZE {FONT_SMALL, FONT_MEDIUM, FONT_BIG};

#define DIM_TIME_MS      60000
#define OFF_TIME_MS      120000

#define DEF_SWITCH_WIDTH 192
#define DEF_SWITCH_HEIGHT 128

enum DEVICEIMAGES   {SHELLY1PM, SHELLY2PM};

class GUI   {
    public:
    lv_obj_t *create_std_frame(lv_obj_t *parent, int32_t x_pos, int32_t y_pos, int32_t width, int32_t height);
    lv_obj_t *create_std_label(lv_obj_t *parent, int32_t x_pos, int32_t y_pos, int32_t width, int32_t height, char *text);
    lv_obj_t *create_std_slider(lv_obj_t *parent, int32_t x_pos, int32_t y_pos, int32_t width, int32_t height, int32_t min, int32_t max, int32_t val);
    lv_obj_t *create_std_img_button(lv_obj_t *parent, int32_t x_pos, int32_t y_pos, int32_t width, int32_t height, const lv_img_dsc_t *img);
    lv_obj_t *create_switch_ui(lv_obj_t *parent, int16_t x_pos, int16_t y_pos, lv_image_dsc_t *device_img, char *label_txt);
    lv_obj_t *create_double_switch_ui(lv_obj_t *parent, int16_t x_pos, int16_t y_pos, lv_image_dsc_t *device_img, char *label_txt);
    lv_obj_t *create_listview(lv_obj_t *parent, int16_t x_pos, int16_t y_pos, int16_t x_size, int16_t y_size);
    lv_obj_t *add_device_item(lv_obj_t *parent, char *text, lv_img_dsc_t *img_dsc, int32_t index);
    lv_img_dsc_t *get_device_image(int32_t device_id)  {
        return deviceImages[device_id];
    }
    const lv_font_t *get_font(int size);
    lv_palette_t getMainColor() {   return def_palette;   }
    void create_main_ui();
    void setup_gui();
    lv_obj_t *get_main_page() {   return mainPage;    }

    ~GUI()  {};

    static GUI *get()   {
        if (ptr==NULL)   {
            ptr=new GUI;
        }
        return ptr;
    }

    uint16_t    switch_width, switch_height;

    lv_palette_t def_palette, sel_palette;
    lv_color_t def_bg_color, def_fg_color;
    lv_color_t def_bar_color;
    lv_color_t sel_switch_color, def_switch_color;
    lv_color_t sel_knob_color, def_knob_color, def_indicator_color;
    lv_color_t def_label_color;
    lv_color_t def_tab_color, sel_tab_color;

    TopBar  *top_bar;

    lv_style_t  frame_style;
    lv_style_t  switch_style;
    lv_style_t  slider_style;
    lv_style_t  indicator_style;
    lv_style_t  def_knob_style, sel_knob_style;
    lv_style_t  bar_style;
    lv_style_t  def_button_style, sel_button_style;
    lv_style_t  def_tab_style, sel_tab_style;
    lv_style_t  del_lv_item_style, sel_lv_item_style;
    lv_style_t  def_lv__style;
    
    private:
    GUI();

    static GUI *ptr;
    lv_display_t    *display;
    lv_obj_t *mainPage;
    lv_obj_t *bottomBar;
    lv_obj_t *mainTab;
    lv_obj_t *homeTab;
    lv_obj_t *devicesTab;
    lv_obj_t *settingsTab;
    
    const lv_font_t *smallFont;
    const lv_font_t *mediumFont;
    const lv_font_t *bigFont;

    lv_img_dsc_t    *deviceImages[64];   
    
};

#endif
