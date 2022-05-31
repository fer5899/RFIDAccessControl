#ifndef SerialESPNOW.h
#define SerialESPNOW.h

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <string> 
#include <vector>

void enviar_respuesta(std::vector<std::string> mensaje_serial);
void al_mandar_datos(uint8_t *mac_addr, uint8_t estado_envio);
void al_recibir_lectura(uint8_t * mac, uint8_t *datos_recibidos, uint8_t len);

#endif
