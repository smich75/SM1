#include <cstdio>
#include "module.h"
#include "cJSON.h"
#include "esp_littlefs.h"
#include <esp_log.h>

static const char *TAG="Module.cpp";

Module  *Module::ptr=NULL;

char *readFile(const char *filename)  {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        ESP_LOGI(TAG, "Error opening file: %s", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length=ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer=(char*)malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, file);
        buffer[length]='\0';
    }
    fclose(file);
    return buffer;
}

int parseWifiConfig(const char* filename, char** out_ssid, char** out_pass) {
    char *json_string = readFile(filename);
    if (!json_string) return -1;
    cJSON *json = cJSON_Parse(json_string);
    free(json_string);
    if (!json) return -1;
    const cJSON *ssid = cJSON_GetObjectItemCaseSensitive(json, "ssid");
    const cJSON *password = cJSON_GetObjectItemCaseSensitive(json, "password");
    if (cJSON_IsString(ssid) && ssid->valuestring) {
        *out_ssid = strdup(ssid->valuestring); // Alloca e copia automaticamente
    }
    if (cJSON_IsString(password) && password->valuestring) {
        *out_pass = strdup(password->valuestring);
    }
    cJSON_Delete(json);
    return 0;
}

void Module::init() {
    //                                          NVS FLASH INITIALIZATION
    esp_err_t ret=nvs_flash_init();
    if (ret==ESP_ERR_NVS_NO_FREE_PAGES||ret==ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret=nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    //                                          LITTLEFS INITIALIZATION

    esp_vfs_littlefs_conf_t conf = {
        .base_path = "/littlefs",
        .partition_label = "storage", // Deve corrispondere al nome in partitions.csv
        .format_if_mount_failed = true,
        .dont_mount = false,
    };

    ret=esp_vfs_littlefs_register(&conf);
    if (ret!=ESP_OK) {
        if (ret==ESP_FAIL) {
            ESP_LOGE(TAG, "Impossibile montare o formattare il filesystem");
        } else if (ret==ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Partizione LittleFS non trovata");
        } else {
            ESP_LOGE(TAG, "Errore inizializzazione LittleFS (%s)", esp_err_to_name(ret));
        }
    }

    size_t total = 0, used = 0;
    ret=esp_littlefs_info(conf.partition_label, &total, &used);
    if (ret==ESP_OK) {
        ESP_LOGI(TAG, "Partizione montata: totale %d byte, usati %d byte", total, used);
    }

    //                                          WIFI INITIALIZATION

    parseWifiConfig("/littlefs/wificonfig.txt", &wifiConfig.ssid, &wifiConfig.password);
    WifiIF::get()->init(wifiConfig.ssid, wifiConfig.password);
}
