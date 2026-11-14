idf_component_register(SRCS "topbar.cpp" "wifi_icon.c" "gui.cpp"
                            "open_sans_14b.c" "open_sans_24b.c"
                            "open_sans_18b.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES lvgl__lvgl espressif__esp_lvgl_adapter waveshare__esp32_p4_wifi6_touch_lcd_7b)
