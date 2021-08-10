#pragma once

#include <string>
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

class StorageController {
    mutable esp_err_t    fatal_error = ESP_OK;
    mutable nvs_handle_t _handle;

public:
    void        init         ( );
    void        createHandle ( std::string key );
    void        closeHandle  ( );
    void        commit       ( );
    char*       read         ( std::string key );
    esp_err_t   isEmpty      ( std::string key );
    void        write        ( std::string key, std::string  value );
    void        write        ( std::string key, std::string* value );
};