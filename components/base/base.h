/**
 * \file base.h
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief Main header of the Base component
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* MACROS                                                                                                   */
/**********************************************************************************************************************/

#ifndef BASE_H
#define BASE_H

#define SCREEN M5.Lcd
#define M5BOARD M5

/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

// credentials file
#include "credentials.h"

// Core
#include <Arduino.h>
#include <M5Stack.h>
#include "Free_Fonts.h"

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"

#include "esp_task_wdt.h"

// Wi-Fi
#include "WiFi.h"
#include "WiFiMulti.h"

// Request HTTP
#include "HTTPClient.h"
#include "WiFiClient.h"

#include "WiFiClientSecure.h"
#include "Update.h"

#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>


// MQTT
#include <PubSubClient.h>

#include "screen.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/**********************************************************************************************************************/
/* PRIVATE ENUM AND VARIABLE                                                                                          */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* PRIVATE METHODS PROTOTYPES                                                                                         */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* PUBLIC METHODS PROTOTYPES                                                                                          */
/**********************************************************************************************************************/

void ard_esp32_cpt_init(void);

void m5_esp32_board_init(void);

/**
 * Connect to Wifi
 * @param WiFiMulti
 */
String wifi_connect(WiFiMulti * WiFiMulti);

bool m5_esp_32_ota_update(String url, const char* root_cert);


#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/