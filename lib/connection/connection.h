#ifndef CONNECTION_H
#define CONNECTION_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

String urlencode(String str);  // Function used for encoding the url
void postData();    //userDefine function used to call api(POST data)
void  message_to_whatsapp(String message);       // user define function to send meassage to WhatsApp app
void connectWiFI();
void sendPGN(); 

#endif /*CONNECTION_H*/