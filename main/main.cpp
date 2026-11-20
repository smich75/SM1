#include <cstdio>
#include <waveshare__esp32_p4_wifi6_touch_lcd_7b/include/bsp/esp-bsp.h>
#include <esp_lv_adapter.h>
#include <lvgl.h>
#include <shelly.h>
#include <gui.h>
#include <module.h>
#include <wifiif.h>

#include <freertos/task.h>

Module *mod=Module::get();
Shelly  ses;

uint32_t eventGroupValue;

extern "C" void app_main(void)  {

    GUI::get()->setupGUI();
    GUI::get()->createMainUI();

    Module::get()->init();

    char buffer[20];
    for (int y=0; y<2; y++) {
        for (int x=0; x<4; x++)  {
            sprintf(buffer, "Test %d-%d", x, y);
            GUI::get()->createSwitchUI(GUI::get()->getMainPage(), (192+24)*x, (128+12)*y, GUI::get()->getDeviceImage(SHELLY1PM), buffer);
        }
    }
    for (int x=0; x<4; x++)  {
        sprintf(buffer, "Tapparella %d", x);
        GUI::get()->createDoubleSwitchUI(GUI::get()->getMainPage(), (192+24)*x, ((128+12)*2), GUI::get()->getDeviceImage(SHELLY2PM), buffer);
    }

    while (1)   {
        vTaskDelay(20);
    }
}