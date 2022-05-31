#include "LectorESPNOW.h"

void al_mandar_datos(uint8_t *mac_addr, uint8_t estado_envio) {
  Serial.print("Estado del ultimo envio: ");
  if (estado_envio == 0){
    Serial.println("Mensaje enviado con exito");
  }
  else{
    Serial.println("Error en el envio del mensaje. Reiniciando...");
    ESP.reset();
  }
}