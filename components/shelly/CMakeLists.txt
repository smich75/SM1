idf_component_register( SRCS "shelly.cpp"
                            "shelly1pm.cpp" "shelly2pm.cpp"
                            "shellyswitch.cpp" "shellydevice.cpp"
                           
                        INCLUDE_DIRS "include"
                        REQUIRES lvgl__lvgl espressif__esp_lvgl_adapter esp_http_server espressif__cjson esp_netif gui devices)
