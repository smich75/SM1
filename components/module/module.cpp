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

    init_usb_host_msc();
    WifiIF::get()->configure(load_file(WIFI_CONFIG_FILE));
}

void Module::init_mdns_service()    {
    ESP_ERROR_CHECK(mdns_init());
    ESP_ERROR_CHECK(mdns_hostname_set(mdns_hostname));
    ESP_ERROR_CHECK(mdns_instance_name_set(mdns_instance_name));
}

static void msc_event_cb(const msc_host_event_t *event, void *arg)  {
    Module *module=Module::get();
    xQueueSend(module->usb_event_queue, event, portMAX_DELAY);
}

// Task di sistema per la libreria USB Host
static void usb_lib_task(void *arg) {
    Module *module=Module::get();
    module->usb_event_queue=xQueueCreate(5, sizeof(msc_host_event_t));

    const usb_host_config_t host_config = {
        .skip_phy_setup = false,
        .intr_flags = ESP_INTR_FLAG_LEVEL1,
    };
    ESP_ERROR_CHECK(usb_host_install(&host_config));

    // 2. Installa driver MSC (il suo task interno resta isolato e non blocca mai le letture/scritture)
    const msc_host_driver_config_t msc_config = {
        .create_backround_task=true,
        .task_priority=5,
        .stack_size=4096,
        .callback=msc_event_cb,
    };
    ESP_ERROR_CHECK(msc_host_install(&msc_config));

    module->msc_device=NULL;
    module->vfs_handle=NULL;

    while (1) {
        uint32_t event_flags;
        usb_host_lib_handle_events(pdMS_TO_TICKS(20), &event_flags);
        if (event_flags & USB_HOST_LIB_EVENT_FLAGS_NO_CLIENTS) {
            usb_host_device_free_all();
        }
        msc_host_event_t msg;
        if (xQueueReceive(module->usb_event_queue, &msg, 0) == pdTRUE) {
            if (msg.event == msc_host_event_t::MSC_DEVICE_CONNECTED) {
                ESP_LOGI(TAG, "Chiavetta inserita");
                ESP_ERROR_CHECK(msc_host_install_device(msg.device.address, &module->msc_device));

                const esp_vfs_fat_mount_config_t mount_config = {
                    .format_if_mount_failed = false,
                    .max_files = 3,
                    .allocation_unit_size = 1024,
                };
                //ESP_ERROR_CHECK(msc_host_vfs_register(module->msc_device, "/usb", &mount_config, &module->vfs_handle));
                ESP_LOGI(TAG, "Chiavetta montata su /usb");

            } else if (msg.event == msc_host_event_t::MSC_DEVICE_DISCONNECTED) {
                ESP_LOGI(TAG, "Chiavetta rimossa");
                if (module->vfs_handle) {
                    msc_host_vfs_unregister(module->vfs_handle);
                    module->vfs_handle = NULL;
                }
                if (module->msc_device) {
                    msc_host_uninstall_device(module->msc_device);
                    module->msc_device = NULL;
                }
            }
        }
    }
}

void Module::init_usb_host_msc()    {
    device_connected_sem=xSemaphoreCreateBinary();
    xTaskCreate(usb_lib_task, "usb_lib", 4096, NULL, 2, NULL);
}

mdns_result_t *Module::find_devices(char *service, char *proto, int32_t timeout_ms)  {
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
