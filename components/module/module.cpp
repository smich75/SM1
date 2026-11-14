#include <cstdio>
#include "module.h"

Module  *Module::ptr=NULL;

#define WIFI_SSID "RN11S"
#define WIFI_PASS "amiga4000"

#define MAX_RETRY 5

static int s_retry_num=0;

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)  {
    Module *mod=(Module *)arg;
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < MAX_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            printf("Reconnecting...\n");
            //ESP_LOGI(TAG, "Tentativo di riconnessione (%d/%d)...", s_retry_num, MAX_RETRY);
        } else {
            xEventGroupSetBits(mod->wifiEventGroup, WIFI_FAIL_BIT);
        }
        // Qui puoi aggiornare un'eventuale icona Wi-Fi su LVGL (usando lvgl_port_lock)
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        //ESP_LOGI(TAG, "Connesso! IP assegnato: " IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num=0;
        xEventGroupSetBits(mod->wifiEventGroup, WIFI_CONNECTED_BIT);
        // Qui puoi aggiornare l'icona Wi-Fi su LVGL come connessa
    }
}

void Module::initWifi() {
    esp_err_t ret=nvs_flash_init();
    if (ret==ESP_ERR_NVS_NO_FREE_PAGES || ret==ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret=nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    wifiEventGroup=xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg=WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        this,
                                                        NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &wifi_event_handler,
                                                        this,
                                                        NULL));
    wifi_config_t wifi_config={
        .sta={
            .ssid=WIFI_SSID,
            .password=WIFI_PASS,
            .threshold={
                .authmode=WIFI_AUTH_WPA2_PSK,
            }
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}
