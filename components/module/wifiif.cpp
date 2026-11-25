#include "wifiif.h"
#include <module.h>
#include <cstring>
#include <gui.h>
#include <cJSON.h>
#include <esp_log.h>

static const char *TAG="wifi.cpp";

#define MAX_RETRY_DELAY_MS 20000

WifiIF *WifiIF::ptr=NULL;
static bool is_switching_network=false;

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)  {
    WifiIF  *wifi=WifiIF::get();
    if (event_base==WIFI_EVENT&&event_id==WIFI_EVENT_STA_START) {
        //esp_wifi_connect();
    } else if (event_base==WIFI_EVENT&&event_id==WIFI_EVENT_STA_DISCONNECTED) {
        if (is_switching_network)   return;
        GUI::get()->top_bar->disableWifi();
        xEventGroupSetBits(wifi->event_group, WIFI_FAIL_BIT);
        xEventGroupClearBits(wifi->event_group, WIFI_CONNECTED_BIT);
    } else if (event_base==IP_EVENT&&event_id==IP_EVENT_STA_GOT_IP) {
        GUI::get()->top_bar->enableWifi();
        xEventGroupSetBits(wifi->event_group, WIFI_CONNECTED_BIT);
        xEventGroupClearBits(wifi->event_group, WIFI_FAIL_BIT);
    }
}

void connect_to_indexed_network()   {
    WifiIF  *wifi=WifiIF::get();
    wifi_config_t wifi_config={
        .sta={
            .threshold={
                .authmode=WIFI_AUTH_WPA2_PSK,
            }
        },
    };
    strcpy((char *)wifi_config.sta.ssid, wifi->get_ssid(wifi->wifi_current_network));
    strcpy((char *)wifi_config.sta.password, wifi->get_password(wifi->wifi_current_network));
    esp_wifi_disconnect();
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    esp_wifi_connect();
}

void wifi_fsm(void *arg)  {
    WifiIF  *wifi=WifiIF::get();
    int32_t retry_delay_ms=1000;
    EventBits_t events;
    wifi->wifi_current_network=0;
    wifi->current_state=WIFI_STATE_INIT;
    wifi->event_group=xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    Module::get()->init_mdns_service();
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
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    while (1)   {
        switch (wifi->current_state)    {
            case WIFI_STATE_INIT:
                connect_to_indexed_network();
                wifi->current_state=WIFI_STATE_CONNECTING;
                break;

            case WIFI_STATE_CONNECTING:
                ESP_LOGW(TAG, "trying %d - %d - %s", wifi->wifi_current_network, wifi->wifi_total_networks, wifi->get_ssid(wifi->wifi_current_network));
                events=xEventGroupWaitBits(wifi->event_group, WIFI_CONNECTED_BIT|WIFI_FAIL_BIT, pdFALSE, pdFALSE, pdMS_TO_TICKS(15000));
                ESP_LOGI(TAG, "Connecting :%0x", (uint32_t)events);
                if (events&WIFI_CONNECTED_BIT) {
                    retry_delay_ms=1000;
                    wifi->current_state=WIFI_STATE_CONNECTED;
                } else {
                    wifi->current_state=WIFI_STATE_DISCONNECTED;
                }
                break;

            case WIFI_STATE_CONNECTED:
                events=xEventGroupWaitBits(wifi->event_group, WIFI_FAIL_BIT, pdFALSE, pdFALSE, portMAX_DELAY);
                ESP_LOGI(TAG, "Connected :%0x", (uint32_t)events);
                if (events&WIFI_FAIL_BIT) {
                    wifi->current_state=WIFI_STATE_DISCONNECTED;
                }   else    {
                   
                }
                break;

            case WIFI_STATE_DISCONNECTED:
                ESP_LOGW(TAG, "Stato: DISCONNECTED. Riconnessione tra %lu ms...", retry_delay_ms);
                is_switching_network=true;
                esp_wifi_disconnect();
                vTaskDelay(pdMS_TO_TICKS(retry_delay_ms));
                is_switching_network=false;
                xEventGroupClearBits(wifi->event_group, WIFI_FAIL_BIT|WIFI_CONNECTED_BIT);
                wifi->wifi_current_network=wifi->wifi_current_network+1;
                if (wifi->wifi_current_network==wifi->wifi_total_networks)    {
                    wifi->wifi_current_network=0;
                    retry_delay_ms*=2;
                    if (retry_delay_ms>MAX_RETRY_DELAY_MS)  retry_delay_ms=MAX_RETRY_DELAY_MS;
                }
                connect_to_indexed_network();
                wifi->current_state=WIFI_STATE_CONNECTING;
                break;

            case WIFI_STATE_ERROR:
                ESP_LOGE(TAG, "Stato: ERROR. Controllare wificonfig.txt. Task bloccato.");
                vTaskDelay(pdMS_TO_TICKS(10000));
                break;

        }
    }
}

WifiIF::WifiIF() {
}

int32_t WifiIF::configure(char *configuration)  {
    int32_t ret_val=0;
    wifi_total_networks=0;
    if (configuration)  {
        cJSON *root=cJSON_Parse(configuration);
        free(configuration);
        if (root!=NULL) {
            cJSON *network_array=cJSON_GetObjectItemCaseSensitive(root, "nets");
            if (cJSON_IsArray(network_array))   {
                cJSON *net=NULL;
                int index=0;
                cJSON_ArrayForEach(net, network_array) {
                    cJSON *ssid=cJSON_GetObjectItemCaseSensitive(net, "ssid");
                    cJSON *password=cJSON_GetObjectItemCaseSensitive(net, "password");

                    if (cJSON_IsString(ssid)&&(ssid->valuestring!=NULL) &&
                        cJSON_IsString(password)&&(password->valuestring!=NULL)) {
                        ESP_LOGI(TAG, "Rete %d -> SSID: %s | Password: %s", 
                        index, ssid->valuestring, password->valuestring);
                    }
                    wifi_network_array[index]=new wifi_network_t;
                    strcpy(wifi_network_array[index]->ssid, ssid->valuestring);
                    strcpy(wifi_network_array[index]->password, password->valuestring);
                    wifi_total_networks++;
                    index++;
                }
                xTaskCreate(wifi_fsm, "WIFI", 8192, NULL, 1, &wifi_task);
                ret_val=1;
            }
            cJSON_Delete(root);
        }
    }
    return ret_val;
}

WifiIF::~WifiIF()   {
}