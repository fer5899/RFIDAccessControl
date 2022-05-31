#include "SerialESPNOW.h"
#include <espnow.h>

typedef struct mensaje_orden_rpi {
    int ms_led_rojo_encendido;
    bool parpadeo_rojo;
    int ms_led_verde_encendido;
    bool parpadeo_verde;
    bool acceso;
} mensaje_orden_rpi;

typedef struct mensaje_lectura {
    byte mac[6];
    char id_tarjeta[32];
} mensaje_lectura;


void enviar_respuesta(std::vector<std::string> mensaje_serial) {
    // Estructura de mensaje_serial
    // {MAC_destino, ms_led_rojo_encendido, parpadeo_rojo, ms_led_verde_encendido, parpadeo_verde, acceso}
    // Ej: {"48:3F:DA:0C:B3:75", "3000", "1", "0", "0" "1"}
    mensaje_orden_rpi respuesta;
    unsigned int a,b,c,d,e,f;

    std::sscanf(mensaje_serial[0].c_str(),
                "%02x:%02x:%02x:%02x:%02x:%02x",
                &a, &b, &c,
                &d, &e, &f);

    uint8_t MAC_destino[6] = {(uint8_t) a, (uint8_t) b, (uint8_t) c, 
                              (uint8_t) d, (uint8_t) e, (uint8_t) f};


    respuesta.ms_led_rojo_encendido = std::stoi(mensaje_serial[1]);
    respuesta.parpadeo_rojo = std::stoi(mensaje_serial[2]);
    respuesta.ms_led_verde_encendido = std::stoi(mensaje_serial[3]);
    respuesta.parpadeo_verde = std::stoi(mensaje_serial[4]);
    respuesta.acceso = std::stoi(mensaje_serial[5]);

    esp_now_send(MAC_destino, (uint8_t *) &respuesta, sizeof(respuesta));

}

void al_mandar_datos(uint8_t *mac_addr, uint8_t estado_envio) {
    Serial.print("Estado_envio: ");
    if (estado_envio == 0){
        Serial.println("exito");
    }
    else{
        Serial.println("error");
        ESP.reset();
    }
}

String mac_a_string(byte ar[]) {
  String s;
  for (byte i = 0; i < 6; ++i)
  {
    char buf[3];
    sprintf(buf, "%02X", ar[i]);
    s += buf;
    if (i < 5) s += ':';
  }
  return s;
}

void al_recibir_lectura(uint8_t * mac, uint8_t *datos_recibidos, uint8_t len) {
    mensaje_lectura lectura;
    memcpy(&lectura, datos_recibidos, sizeof(lectura));
    
    Serial.print("Lectura: ");
    Serial.print(mac_a_string(lectura.mac).c_str());
    Serial.print(" ");
    Serial.println(lectura.id_tarjeta);

    if (strcmp(lectura.id_tarjeta, "registro") == 0) {
        Serial.print("\nResultado de añadir peer: ");
        Serial.println(esp_now_add_peer(lectura.mac, ESP_NOW_ROLE_COMBO, 1, NULL, 0));
    }
  
}
