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
    lv_obj_t *createStdFrame(lv_obj_t *parent, int32_t xPos, int32_t yPos, int32_t width, int32_t height);
    lv_obj_t *createStdLabel(lv_obj_t *parent, int32_t xPos, int32_t yPos, int32_t width, int32_t height, char *text);
    lv_obj_t *createStdSlider(lv_obj_t *parent, int32_t xPos, int32_t yPos, int32_t width, int32_t height, int32_t min, int32_t max, int32_t val);
    lv_obj_t *createStdImgButton(lv_obj_t *parent, int32_t xPos, int32_t yPos, int32_t width, int32_t height, const lv_img_dsc_t *img);
    lv_obj_t *createSwitchUI(lv_obj_t *parent, int16_t xPos, int16_t yPos, lv_image_dsc_t *deviceImg, char *labelTxt);
    lv_obj_t *createDoubleSwitchUI(lv_obj_t *parent, int16_t xPos, int16_t yPos, lv_image_dsc_t *deviceImg, char *labelTxt);
    lv_img_dsc_t *getDeviceImage(int32_t deviceID)  {
        return deviceImages[deviceID];
    }
    const lv_font_t *getFont(int size);
    lv_palette_t getMainColor() {   return defPaletteColor;   }
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

    lv_palette_t defPaletteColor, selPaletteColor;
    lv_color_t defBGColor, defFGColor;
    lv_color_t defBarColor;
    lv_color_t selSwitchColor, defSwitchColor;
    lv_color_t selKnobColor, defKnobColor, defIndicatorColor;
    lv_color_t defLabelColor;

    TopBar  *topBar;

    lv_style_t  frameStyle;
    lv_style_t  switchStyle;
    lv_style_t  sliderStyle;
    lv_style_t  indicatorStyle;
    lv_style_t  defKnobStyle, selKnobStyle;
    lv_style_t  barStyle;
    lv_style_t  defButtonStyle, selButtonStyle;
    
    private:
    GUI();

    static GUI *ptr;
    lv_obj_t *mainPage;
    lv_obj_t *bottomBar;
    
    const lv_font_t *smallFont;
    const lv_font_t *mediumFont;
    const lv_font_t *bigFont;

    lv_img_dsc_t    *deviceImages[64];   
    
};

#endif
