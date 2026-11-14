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

class GUI   {
    public:
    lv_obj_t *createSwitchUI(lv_obj_t *parent, int16_t xPos, int16_t yPos, lv_image_dsc_t *img, char *label);
    lv_obj_t *createDoubleSwitchUI(lv_obj_t *parent, int16_t xPos, int16_t yPos, lv_image_dsc_t *img1, lv_image_dsc_t *img2, char *label);
    const lv_font_t *getFont(int size);
    lv_palette_t getMainColor() {   return mainColor;   }
    void setGapBorderValues(lv_obj_t *obj, int16_t margin, int16_t padAll, int16_t padRow, int16_t padColumn, int16_t border, int16_t shadow);
    void createMainUI();
    void setupGUI();
    lv_obj_t *getMainPage() {   return mainPage;    }
    ~GUI()  {};
    static GUI *get()   {
        if (ptr==NULL)   {
            ptr=new GUI;
        }
        return ptr;
    }

    uint16_t    switchWidth, switchHeight;

    lv_palette_t mainColor, mainSelectedColor;
    lv_color_t backgroundColor;
    lv_color_t barColor;
    lv_color_t selSwitchColor, defSwitchColor;
    lv_color_t knobPressed, knobDefault, knobIndicator;
    lv_color_t labelDefault;

    TopBar  *topBar;

    lv_style_t  switchStyle;
    lv_style_t  barStyle;
    lv_style_t  defButtonStyle;
    lv_style_t  selButtonStyle;
    
    private:
    GUI();

    static GUI *ptr;
    lv_obj_t *mainPage;
    lv_obj_t *bottomBar;
    
    const lv_font_t *smallFont;
    const lv_font_t *mediumFont;
    const lv_font_t *bigFont;
    
    
};

#endif
