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

uint32_t event_group_value;

extern "C" void app_main(void)  {

    GUI::get()->setup_gui();
    GUI::get()->create_main_ui();

    Module::get()->init();

    char buffer[20];
    for (int y=0; y<2; y++) {
        for (int x=0; x<4; x++)  {
            sprintf(buffer, "Test %d-%d", x, y);
            GUI::get()->create_switch_ui(GUI::get()->get_main_page(), (192+24)*x, (128+12)*y, GUI::get()->get_device_image(SHELLY1PM), buffer);
        }
    }
    for (int x=0; x<4; x++)  {
        sprintf(buffer, "Tapparella %d", x);
        GUI::get()->create_double_switch_ui(GUI::get()->get_main_page(), (192+24)*x, ((128+12)*2), GUI::get()->get_device_image(SHELLY2PM), buffer);
    }

    while (1)   {
        vTaskDelay(20);
    }
}