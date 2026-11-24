#include <cstdio>
#include "module.h"
#include "cJSON.h"
#include "esp_littlefs.h"
#include <esp_log.h>

static const char *TAG="Module.cpp";

static const char *mdns_hostname="CONTROL MODULE";
static const char *mdns_instance_name="Shelly Scanner";

Module  *Module::ptr=NULL;

char *load_file(const char *filename)  {
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

void Module::init() {
    mdns_results=NULL;

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

    WifiIF::get()->configure(load_file(WIFI_CONFIG_FILE));

    init_mdns_service();
}

void Module::init_mdns_service()    {
    ESP_ERROR_CHECK(mdns_init());
    ESP_ERROR_CHECK(mdns_hostname_set(mdns_hostname));
    ESP_ERROR_CHECK(mdns_instance_name_set(mdns_instance_name));
}

mdns_result_t *Module::findDevices(char *service, char *proto, int32_t timeout_ms)  {
    esp_err_t err = mdns_query_ptr(service, proto, timeout_ms, 20, &mdns_results);
    if (err!=ESP_OK) {
        ESP_LOGE(TAG, "Errore durante la query mDNS: %s", esp_err_to_name(err));
        return NULL;
    }

    if (mdns_results==NULL) {
        ESP_LOGW(TAG, "Nessun servizio trovato.");
        return NULL;
    }
    return mdns_results;
}
