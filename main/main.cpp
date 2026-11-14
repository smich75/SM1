#include <cstdio>
#include <waveshare__esp32_p4_wifi6_touch_lcd_7b/include/bsp/esp-bsp.h>
#include <esp_lv_adapter.h>
#include <lvgl.h>
#include <shelly.h>
#include <gui.h>
#include <module.h>

#include <freertos/task.h>

Module *mod=Module::get();
Shelly  ses;

Shelly1PM shelly[20];

uint32_t eventGroupValue;

extern "C" void app_main(void)  {
    GUI::get()->setupGUI();
    GUI::get()->createMainUI();
    Module::get()->initWifi();
    char buffer[20];
    for (int y=0; y<2; y++) {
        for (int x=0; x<4; x++)  {
            sprintf(buffer, "Test %d", (y*4)+x);
            shelly[(y*4)+x].setName(buffer);
            shelly[(y*4)+x].createGUIObject(GUI::get()->getMainPage(), 100+(192+10)*x, 50+(128+10)*y);
        }
    }
    for (int x=0; x<4; x++)  {
        sprintf(buffer, "Tapparella %d", x);
        GUI::get()->createDoubleSwitchUI(GUI::get()->getMainPage(), 100+(192+10)*x, 50+((128+10)*3), NULL, NULL, buffer);
    }

    for (int x=0; x<4; x++)  {
        sprintf(buffer, "Tenda %d", x);
        GUI::get()->createDoubleSwitchUI(GUI::get()->getMainPage(), 100+(192+10)*x, 50+((128+10)*4), NULL, NULL, buffer);
    }

    while (1)   {
        eventGroupValue=xEventGroupWaitBits(Module::get()->wifiEventGroup, WIFI_CONNECTED_BIT|WIFI_FAIL_BIT, 0xffffffff, pdFALSE, pdMS_TO_TICKS(10));
        if (eventGroupValue&WIFI_CONNECTED_BIT) {
            printf("Connected\n");
            GUI::get()->topBar->enableWifi();
        }
        if (eventGroupValue&WIFI_FAIL_BIT) {
            GUI::get()->topBar->disableWifi();
        }
    }
}