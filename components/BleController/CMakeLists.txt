idf_component_register(SRCS "BleController.cpp" "callbacks.cpp"
                    INCLUDE_DIRS "include" "./../../main/inc"
                    REQUIRES NimBLE BleInformationTable BleEventTrigger )
