/**
 * \file base.c
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to implement some base functions of the arduino as esp-idf component
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "base.h"

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

extern "C" String m5_esp32_update_err2str(uint8_t _error) {
    if(_error == UPDATE_ERROR_OK){
        return ("No Error");
    } else if(_error == UPDATE_ERROR_WRITE){
        return ("Flash Write Failed");
    } else if(_error == UPDATE_ERROR_ERASE){
        return ("Flash Erase Failed");
    } else if(_error == UPDATE_ERROR_READ){
        return ("Flash Read Failed");
    } else if(_error == UPDATE_ERROR_SPACE){
        return ("Not Enough Space");
    } else if(_error == UPDATE_ERROR_SIZE){
        return ("Bad Size Given");
    } else if(_error == UPDATE_ERROR_STREAM){
        return ("Stream Read Timeout");
    } else if(_error == UPDATE_ERROR_MD5){
        return ("MD5 Check Failed");
    } else if(_error == UPDATE_ERROR_MAGIC_BYTE){
        return ("Wrong Magic Byte");
    } else if(_error == UPDATE_ERROR_ACTIVATE){
        return ("Could Not Activate The Firmware");
    } else if(_error == UPDATE_ERROR_NO_PARTITION){
        return ("Partition Could Not be Found");
    } else if(_error == UPDATE_ERROR_BAD_ARGUMENT){
        return ("Bad Argument");
    } else if(_error == UPDATE_ERROR_ABORT){
        return ("Aborted");
    }
    return ("UNKNOWN");
}

void m5_esp32_update_progress(int done, int total) {
    SCREEN.fillCircle(0, 0, 320, TFT_WHITE);

    SCREEN.setTextColor(TFT_BLACK, TFT_WHITE);
    SCREEN.println((done * 100) / total);
}

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" void ard_esp32_cpt_init(void) {
    initArduino();
}

extern "C" void m5_esp32_board_init(void) {
    M5.begin();
    M5.Power.begin();
}

extern "C" String wifi_connect(WiFiMulti * wiFiMulti) {
    String ip = "";

    for(uint8_t t = 4; t > 0; t--) {
        delay(1000);
    }

    // disable AP
    if(WiFi.getMode() & WIFI_AP) {
        WiFi.softAPdisconnect(true);
    }

    wiFiMulti->addAP(WIFI_SSID, WIFI_PASS);

    while(wiFiMulti->run() != WL_CONNECTED) {
        delay(1000);

        return "";
    }

    ip = WiFi.localIP().toString();
    Serial.printf("[SETUP] WiFi Connected %s\n", ip.c_str());

    return ip.c_str();
}

extern "C" bool m5_esp_32_ota_update(String url, const char* root_cert) {
    if (!WiFi.isConnected()) {
        Serial.println("No WiFi connection.");
        return false;
    }

    if (!url.startsWith("https://")) {
        Serial.println("URL must start with 'https://'");
        return false;
    }

    url = url.substring(8);

    String host, file;
    uint16_t port;
    int16_t first_slash_pos = url.indexOf("/");
    if (first_slash_pos == -1) {
        host = url;
        file = "/";
    } else {
        host = url.substring(0, first_slash_pos);
        file = url.substring(first_slash_pos);
    }
    int16_t colon = host.indexOf(":");

    if (colon == -1) {
        port = 443;
    } else {
        host = host.substring(0, colon);
        port = host.substring(colon + 1).toInt();
    }

    WiFiClientSecure client;
    client.setTimeout(20000);
    client.setCACert(root_cert);

    int contentLength = 0;

    if (!client.connect(host.c_str(), port)) {
        Serial.print("Connection to ");
        Serial.print(String(host));
        Serial.println(" failed.");
        return false;
    }

    client.print(String("GET ") + file + " HTTP/1.1\r\n" +
        "Host: " + host + "\r\n" +
        "Cache-Control: no-cache\r\n" +
        "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (!client.available()) {
        if (millis() - timeout > 10000) {
            Serial.println("Client Timeout");
            client.stop();
            return false;
        }
    }

    // Process header
    while (client.available()) {
        String line = client.readStringUntil('\n');
        line.trim();
        if (!line.length()) break; // empty line, assume headers done

        if (line.startsWith("HTTP/1.1")) {
            String http_response = line.substring(line.indexOf(" ") + 1);
            http_response.trim();
            if (http_response.indexOf("200") == -1) {
                Serial.print("Got response: \"");
                Serial.print(String(http_response));
                Serial.println("\", must be 200");
                return false;
            }
        }

        if (line.startsWith("Content-Length: ")) {
            contentLength = atoi(line.substring(  line.indexOf(":") + 1  ).c_str());
            if (contentLength <= 0) {
                Serial.print("Content-Length zero");
                return false;
            }
        }

        if (line.startsWith("Content-Type: ")) {
            String contentType = line.substring(line.indexOf(":") + 1);
            contentType.trim();
            if (contentType != "application/octet-stream") {
                Serial.print("Content-Type must be \"application/octet-stream\", got \"");
                Serial.print(String(contentType));
                Serial.println("\"");
                return false;
            }
        }
    }

    // Process payload
    Update.onProgress(m5_esp32_update_progress);

    if (!Update.begin(contentLength)) {
        Serial.print("Not enough space to begin OTA");
        client.flush();
        return false;
    }

    size_t written = Update.writeStream(client);

    if (!Update.end()) {
        Serial.print("Error: ");
        Serial.print(String(String(m5_esp32_update_err2str(Update.getError()))));
        Serial.print(" | (after ");
        Serial.print(String(written));
        Serial.print(" of ");
        Serial.print(String(contentLength));
        Serial.println(" bytes)");
        return false;
    }

    if (!Update.isFinished()) {
        Serial.print("Update not finished. Something went wrong.");
        return false;
    }

    return true;

}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/