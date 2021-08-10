idf_component_register(SRCS "HardwareController.cpp" "bluetoothFunctions.cpp"
                    INCLUDE_DIRS "include" "./../../main/inc"
                    REQUIRES Gpio Hand BleInformationTable StorageController )
