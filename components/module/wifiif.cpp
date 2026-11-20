#include "wifiif.h"
#include <module.h>
#include <cstring>
#include <gui.h>

#define MAX_RETRY 5

WifiIF *WifiIF::ptr=NULL;
static int s_retry_num=0;

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)  {
    WifiIF  *wifi=WifiIF::get();
    if (event_base==WIFI_EVENT&&event_id==WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base==WIFI_EVENT&&event_id==WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num<MAX_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
        } else {
            GUI::get()->topBar->disableWifi();
            xEventGroupSetBits(wifi->eventGroup, WIFI_FAIL_BIT);
        }
    } else if (event_base==IP_EVENT&&event_id==IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event=(ip_event_got_ip_t *)event_data;
        s_retry_num=0;
        GUI::get()->topBar->enableWifi();
        xEventGroupSetBits(wifi->eventGroup, WIFI_CONNECTED_BIT);
    }
}

void wifiIFTask(void *arg)  {
    int32_t event;
    WifiIF  *wifi=WifiIF::get();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg=WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));
    wifi_config_t wifi_config={
        .sta={
            .threshold={
                .authmode=WIFI_AUTH_WPA2_PSK,
            }
        },
    };
    strcpy((char *)wifi_config.sta.ssid, wifi->getSSID());
    strcpy((char *)wifi_config.sta.password, wifi->getPWD());
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    while (1)   {
        event=xEventGroupWaitBits(wifi->eventGroup, WIFI_CONNECTED_BIT|WIFI_FAIL_BIT, pdTRUE, pdFALSE, pdMS_TO_TICKS(10));
    }
}

WifiIF::WifiIF() {
}



void WifiIF::init(char *_ssid, char *_pwd)    {
    strcpy((char *)ssid, _ssid);
    strcpy((char *)pwd, _pwd);
    eventGroup=xEventGroupCreate();
    xTaskCreate(wifiIFTask, "WIFI", 8192, NULL, 1, &wifiTask);
}

void WifiIF::setSSID(char *_ssid)   {
    strcpy((char *)ssid, _ssid);
}

void WifiIF::setPWD(char *_pwd) {
    strcpy((char *)pwd, _pwd);
}

WifiIF::~WifiIF()   {
}