#ifndef MODULE_H
#define MODULE_H

#include <esp_wifi.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>
#include <wifiif.h>
#include <mdns.h>

class Module {
    public:
    void init();
    void init_mdns_service();
    mdns_result_t   *findDevices(char *service, char *proto, int32_t timeout_ms);
    
    static Module *get()    {
        if (!ptr)   {
            ptr=new Module;
        }
        return ptr;
    }
    ~Module()   {};

    private:
    mdns_result_t   *mdns_results;
    static Module *ptr;
    Module()    {};
};

#endif

