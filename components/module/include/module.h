#ifndef MODULE_H
#define MODULE_H

#include <esp_wifi.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>
#include <wifiif.h>

typedef struct {
    char *ssid;
    char *password;
} WifiConfig;


class Module {
    public:
    void init();
    
    static Module *get()    {
        if (!ptr)   {
            ptr=new Module;
        }
        return ptr;
    }
    ~Module()   {};

    private:
    WifiConfig  wifiConfig;
    static Module *ptr;
    Module()    {};
};

#endif

