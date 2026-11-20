#ifndef WIFIIF_H
#define WIFIIF_H

#pragma once

#include <esp_wifi.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

class WifiIF {
public:
    void init(char *ssid, char *pwd);
    void setSSID(char *_ssid);
    void setPWD(char *_pwd);
    char *getSSID() {   return ssid;    }
    char *getPWD()  {   return pwd;     }
    static WifiIF *get()    {
        if (!ptr)   {
            ptr=new WifiIF;
        }
        return ptr;
    }
    ~WifiIF();

    EventGroupHandle_t  eventGroup;
    
private:
    static WifiIF *ptr;
    TaskHandle_t    wifiTask;
    char ssid[32], pwd[32];
    WifiIF();
};

#endif