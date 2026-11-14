#ifndef MODULE_H
#define MODULE_H

#include <esp_wifi.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

class Module {
    public:
    void initWifi();
    void initWebSockets();

    EventGroupHandle_t wifiEventGroup;
    
    static Module *get()    {
        if (!ptr)   {
            ptr=new Module;
        }
        return ptr;
    }
    ~Module()   {};
    private:
    
    static Module *ptr;
    Module()    {};
};

#endif

