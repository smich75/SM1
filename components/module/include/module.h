#ifndef MODULE_H
#define MODULE_H

#include <esp_wifi.h>
#include <esp_event.h>
#include <nvs_flash.h>
#include <freertos/FreeRTOS.h>
#include <wifiif.h>
#include <mdns.h>
#include "usb/usb_host.h"
#include "usb/msc_host.h"
#include "usb/msc_host_vfs.h"

#define MNT_PATH "/usb"

class Module {
    public:
    void init();
    void init_mdns_service();
    void init_usb_host_msc();
    mdns_result_t   *find_devices(char *service, char *proto, int32_t timeout_ms);
    
    static Module *get()    {
        if (!ptr)   {
            ptr=new Module;
        }
        return ptr;
    }
    ~Module()   {};

    SemaphoreHandle_t device_connected_sem;
    msc_host_device_handle_t msc_device=NULL;
    msc_host_vfs_handle_t vfs_handle=NULL;
    uint8_t connected_device_addr=0;
    QueueHandle_t usb_event_queue;

    private:

    mdns_result_t   *mdns_results;

    static Module *ptr;
    Module()    {};
};

#endif

