idf_component_register( SRCS "shelly.cpp" "shelly_generic.cpp"
                            "shelly1pm.cpp" "shelly2pm.cpp"
                            "shellyunit.cpp" "shellyswitch.cpp"
                            "shelly1pm.c" "shelly2pm.c"
                        INCLUDE_DIRS "include"
                        PRIV_REQUIRES lvgl__lvgl espressif__esp_lvgl_adapter gui)
