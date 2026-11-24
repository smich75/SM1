#ifndef WIFIIF_H
#define WIFIIF_H

#pragma once

#include <esp_wifi.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>

#define MAX_KNOWN_NETWORK   8
#define WIFI_CONFIG_FILE "/littlefs/wificonfig.json"

typedef enum {
    WIFI_STATE_INIT=0,
    WIFI_STATE_CONNECTING,
    WIFI_STATE_CONNECTED,
    WIFI_STATE_DISCONNECTED,
    WIFI_STATE_ERROR
} wifi_state_t;

typedef struct {
    char ssid[32];
    char password [64];
}   wifi_network_t;

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

class WifiIF {
public:
    int32_t configure(char *configuration);
    char *get_ssid(int32_t index) {   return wifi_network_array[index]->ssid;    }
    char *get_password(int32_t index)  {   return wifi_network_array[index]->password;     }
    static WifiIF *get()    {
        if (!ptr)   {
            ptr=new WifiIF;
        }
        return ptr;
    }
    ~WifiIF();

    EventGroupHandle_t  event_group;
    wifi_state_t    current_state;
    int32_t         wifi_current_network;
    wifi_network_t  *wifi_network_array[MAX_KNOWN_NETWORK];
    int32_t         wifi_total_networks;
    
    private:
    static WifiIF *ptr;
    TaskHandle_t    wifi_task;
    WifiIF();
};

#endif