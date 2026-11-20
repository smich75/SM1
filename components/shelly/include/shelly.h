#ifndef SHELLYES_H
#define SHELLYES_H


#include <vector>
#include <devices.h>
#include <shelly1pm.h>
#include <shelly2pm.h>
#include <esp_http_server.h>
#include <cJSON.h>
#include <esp_log.h>

#define SHELLY_MAX_CLIENT 32

class Shelly  {
    public:
    Shelly() {};
    ~Shelly() {};
    void setup();
    std::vector<Device> devices;

    private:
};

#endif

