#ifndef FOTA.h
#define FOTA.h

#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h> 

// datos para actualización   >>>> SUSTITUIR IP <<<<<
#define HTTP_OTA_ADDRESS      F("192.168.1.132")         // Address of OTA update server
#define HTTP_OTA_PATH         F("/esp8266-ota/update") // Path to update firmware
#define HTTP_OTA_PORT         1880                     // Port of update server
                                                       // Name of firmware
#define HTTP_OTA_VERSION      "MainPlacaSerial.ino"                                                    

#define LED_OTA 16

#define NETWORK_SSID F("")
#define PASSWORD F("")

void intenta_OTA();
void final_OTA();
void inicio_OTA();
void error_OTA(int);
void progreso_OTA(int,int);
void conecta_wifi();

#endif
