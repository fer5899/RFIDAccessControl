#ifndef LectorESPNOW.h
#define LectorESPNOW.h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <string> 
#include <vector>

typedef struct mensaje_lectura {
  byte mac[6];
  char id_tarjeta[32];
} mensaje_lectura;

void al_recibir_mensaje(uint8_t * mac, uint8_t *datos_recibidos, uint8_t len);
void al_mandar_datos(uint8_t *mac_addr, uint8_t estado_envio);

#endif
