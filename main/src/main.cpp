#include <stdio.h>
#include "main.h"
#include "Hand.h"
#include "Mode.h"
#include "Gpio.h"
#include "global_variables.h"
#include "HardwareController.h"
#include "BleInformationTable.h"
#include "StorageController.h"
#include "BleEventTrigger.h"
#include "BleController.h"

static Main main_controller = Main();

extern "C" void app_main ( void ) {
    ESP_ERROR_CHECK( main_controller.setup() );

    while ( true ) {
        main_controller.loop();
    }
}
static BleInformationTable bleTable = BleInformationTable();
static BleEventTrigger     bleEventTrigger;
static BleController       bleController;

static Hand        hand        = Hand();

static StorageController storage;

HardwareController hController = HardwareController(
                                    &hand,
                                    &bleTable,
                                    { 
                                        FINGER_PIN_1, 
                                        FINGER_PIN_2, 
                                        FINGER_PIN_3, 
                                        FINGER_PIN_4, 
                                        FINGER_PIN_5,
                                        FINGER_PIN_6,
                                        FINGER_PIN_7,
                                        FINGER_PIN_9,
                                        // FINGER_PIN_9,
                                        // FINGER_PIN_10
                                    },
                                    { true, true, true, true, true, true, true, true },
                                    INPUT_STATE_PIN, 
                                    INPUT_MODE_PIN
                                );

esp_err_t Main::setup ( void ) {
    esp_err_t status { ESP_OK };

    bleEventTrigger = BleEventTrigger( &hand, &hController, &storage );
    bleController   = BleController( (char*) BLE_DEVICE_NAME, &bleTable, &bleEventTrigger );

    storage.init();
    if ( storage.isEmpty( "modes" ) != ESP_OK ) storage.write( "modes", 
        "name1;0.0.0,0.0.0,0.0.0,0.0.0,0.0.0;180.0.0,180.0.0,180.0.0,180.0.0,180.0.0|name2;0.0.0,0.0.0,0.0.0,0.0.0,0.0.0;180.0.0,180.0.0,180.0.0,180.0.0,180.0.0" );
    hand.initModes( &storage );

    hController.init();

    return status;
}
void Main::loop ( void ) {

    hController.listen();

    vTaskDelay(pdMS_TO_TICKS(100)); 
}