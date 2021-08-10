#include <stdio.h>
#include <iostream>
#include "StorageController.h"
#include "global_variables.h"

void StorageController::init ( ) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
}

void StorageController::createHandle ( std::string key ) {
    esp_err_t err = nvs_open( (char*)key.c_str(), NVS_READWRITE, &_handle);
    if ( err != ESP_OK ) fatal_error = err;
}

void StorageController::closeHandle ( ) {
    nvs_close( _handle );
}

esp_err_t StorageController::isEmpty ( std::string key ) {
    createHandle( key );
    char* value = (char*) malloc( sizeof( char ) * MODE_CHAR_PTR_SIZE );
    esp_err_t err = nvs_get_str( _handle, (char*)key.c_str(), value, &MODE_CHAR_PTR_SIZE );
    closeHandle();
    if (err != ESP_OK) printf( "\nEmpty!: %d\n", err );
    return err;
}

void StorageController::commit ( ) {
    esp_err_t err = nvs_commit(_handle);
    printf((err != ESP_OK) ? "\nCommit Failed!\n" : "\nCommited\n");
}

char* StorageController::read ( std::string key ) {
    createHandle( key );
    char* value = (char*) malloc( sizeof( char ) * MODE_CHAR_PTR_SIZE );
    esp_err_t err = nvs_get_str( _handle, (char*)key.c_str(), value, &MODE_CHAR_PTR_SIZE );
    closeHandle();
    printf((err != ESP_OK) ? "\nRead Failed!\n" : "\nSaved\n");
    return ( err == ESP_ERR_NVS_NOT_FOUND ) ? (char*)"" : value;
}

void StorageController::write ( std::string key, std::string value ) {
    createHandle( key );
    esp_err_t err = nvs_set_str( _handle, (char*)key.c_str(), (char*)value.c_str() );
    commit( );
    closeHandle();
    printf((err != ESP_OK) ? "\nWrite Failed!\n" : "\nSaved\n");
}
void StorageController::write ( std::string key, std::string* value ) {
    createHandle( key );
    esp_err_t err = nvs_set_str( _handle, (char*)key.c_str(), (char*)value->c_str() );
    closeHandle();
    printf((err != ESP_OK) ? "\nWrite Failed!\n" : "\nSaved\n");
    commit( );
}