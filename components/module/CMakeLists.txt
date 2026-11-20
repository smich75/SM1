idf_component_register(SRCS "module.cpp" "wifiif.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_wifi esp_event esp_netif nvs_flash devices freertos gui cjson littlefs)
