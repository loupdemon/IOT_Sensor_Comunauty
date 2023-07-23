/**
 * \file main.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo, r.mers and a.azzoug)
 * \brief Main component that manage tasks
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "base.h"

#include "header.h"
#include "footer.h"
#include "body.h"

#include "SemtechSx1276M5Lora.h"

TaskHandle_t mainTaskHandle = NULL;
bool mainTaskWDTEnabled;

/* env data getting on lora net */
char* env_data[5];
int i = 0;

/* MQTT client var */
WiFiClient espClient;
PubSubClient client(espClient);

/* Wi-Fi connection var */
WiFiMulti wiFiMulti;

WebServer server(80);

/* Style */
String style =
"<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
"input{background:#f1f1f1;border:0;padding:0 15px}body{background:#3498db;font-family:sans-serif;font-size:14px;color:#777}"
"#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
"#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
"form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
".btn{background:#3498db;color:#fff;cursor:pointer}</style>";

/* Login page */
String loginIndex = 
"<form name=loginForm>"
"<h1>ESP32 Login</h1>"
"<input name=userid placeholder='User ID'> "
"<input name=pwd placeholder=Password type=Password> "
"<input type=submit onclick=check(this.form) class=btn value=Login></form>"
"<script>"
"function check(form) {"
"if(form.userid.value=='admin' && form.pwd.value=='admin')"
"{window.open('/serverIndex')}"
"else"
"{alert('Error Password or Username')}"
"}"
"</script>" + style;
 
/* Server Index Page */
String serverIndex = 
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
"<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
"<label id='file-input' for='file'>   Choose file...</label>"
"<input type='submit' class=btn value='Update'>"
"<br><br>"
"<div id='prg'></div>"
"<br><div id='prgbar'><div id='bar'></div></div><br></form>"
"<script>"
"function sub(obj){"
"var fileName = obj.value.split('\\\\');"
"document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
"};"
"$('form').submit(function(e){"
"e.preventDefault();"
"var form = $('#upload_form')[0];"
"var data = new FormData(form);"
"$.ajax({"
"url: '/update',"
"type: 'POST',"
"data: data,"
"contentType: false,"
"processData:false,"
"xhr: function() {"
"var xhr = new window.XMLHttpRequest();"
"xhr.upload.addEventListener('progress', function(evt) {"
"if (evt.lengthComputable) {"
"var per = evt.loaded / evt.total;"
"$('#prg').html('progress: ' + Math.round(per*100) + '%');"
"$('#bar').css('width',Math.round(per*100) + '%');"
"}"
"}, false);"
"return xhr;"
"},"
"success:function(d, s) {"
"console.log('success!') "
"},"
"error: function (a, b, c) {"
"}"
"});"
"});"
"</script>" + style;

/**********************************************************************************************************************/
/* PRIVATE FUNCTION CODE                                                                                              */
/**********************************************************************************************************************/

static void m5_esp32_mqtt_callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

static void m5_esp32_mqtt_reConnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID.
        String clientId = "g2a_";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect.
        if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
            Serial.printf("\nSuccess\n");
            // Once connected, publish an announcement to the topic.
            client.publish(MQTT_WELCOME_TOPIC, "hello world");
            //client.subscribe("M5Stack");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println("try again in 5 seconds");
            delay(5000);
        }
    }
}

static void configTask(void) {
    // core config
    m5_esp32_board_init();

    // Lora protocol config
    if (!m5_sx1276_lora_turn_on(866E6)) {
        Serial.println("Starting LoRa failed!");
        while (1)
            ;
    }

   // WI-FI config
    //wifi_connect(&wiFiMulti);
    //Init WiFi as Station, start SmartConfig
    WiFi.mode(WIFI_AP_STA);
    WiFi.beginSmartConfig();

    //Wait for SmartConfig packet from mobile
    Serial.println("Waiting for SmartConfig.");
    while (!WiFi.smartConfigDone()) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("SmartConfig received.");

    //Wait for WiFi to connect to AP
    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi Connected.");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // MQTT config
    client.setServer(MQTT_HOST, MQTT_PORT);
    client.setCallback(m5_esp32_mqtt_callback);

    // M5 screen design config
    m5_esp32_screen_pre_header();
    m5_esp32_screen_header();
    m5_esp32_screen_body_cfTask();
    m5_esp32_screen_footer();

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

  /*use mdns for host name resolution*/
  if (!MDNS.begin("esp32")) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  /*return index page which is stored in serverIndex */
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  server.begin();
}

static void loopTask() {
    // Lora receiver mode
    char data[100];
    int packetSize = m5_sx1276_lora_analyze_packet_get_size();
    if (packetSize) {
        // received a packet
        Serial.println("Received packet:");

        int data_counter = 0;
        // read packet
        while (m5_sx1276_lora_data_process()) {
            char ch = (char)m5_sx1276_lora_get_data();
            data[data_counter] = ch;
            data_counter++;
        }
        
        // connect to broker and publish packet got from lora
        if (!client.connected()) {
            m5_esp32_mqtt_reConnect();
        }
        client.loop();
        client.publish(MQTT_ENVDATA_TOPIC, (const char*)&data);

        // process data for updating screen
        char* env_data_split = strtok(data, " ");
        while(env_data_split != NULL)
        {
            env_data[i] = env_data_split;
            env_data_split = strtok(NULL, " ");
            ++i;
        }

        i = 0;

        delay(5000);

        M5BOARD.update();

        m5_esp32_screen_body_lpTask((String)env_data[2], (String)env_data[3], (String)env_data[4], (String)env_data[0], (String)env_data[1]);

        server.handleClient();
        delay(1);
    }
}

void mainTask(void *pvParameters)
{
    configTask();

    for(;;) {
        if(mainTaskWDTEnabled){
            esp_task_wdt_reset();
        }
        
        // loop code should be here
        loopTask();
    }
}

extern "C" void app_main()
{
    mainTaskWDTEnabled = true;

    ard_esp32_cpt_init();

    xTaskCreateUniversal(mainTask, "mainTask", 8192, NULL, 1, &mainTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/