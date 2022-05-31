#include "SerialESPNOW.h"
#include "SerialInput.h"

// GPIOs
int LED_blink= 2;

unsigned long ultimo = 0;

int timer = 100;

const byte max_chars = 64;
char chars_recibidos_serial[max_chars];

boolean datos_nuevos_serial = false;


void recibir_serial() {
    static byte ndx = 0;
    char fin_string = '\n';
    char rc;
    
    while (Serial.available() > 0 && datos_nuevos_serial == false) {
        rc = Serial.read();

        if (rc != fin_string) {
            chars_recibidos_serial[ndx] = rc;
            ndx++;
            if (ndx >= max_chars) {
                ndx = max_chars - 1;
            }
        }
        else {
            chars_recibidos_serial[ndx] = '\0';
            ndx = 0;
            datos_nuevos_serial = true;
        }
    }
}


//-----------------------------------------------------
//-------------------- SETUP --------------------------
//-----------------------------------------------------

void setup() {
    Serial.begin(115200);
    pinMode(LED_blink, OUTPUT);   
    digitalWrite(LED_blink, LOW);   

    WiFi.mode(WIFI_STA);

    // Inicializar ESPNOW
    if (esp_now_init() != 0) {
        Serial.println("Error inicializando ESP-NOW");
        return;
    }
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_send_cb(al_mandar_datos);
    esp_now_register_recv_cb(al_recibir_lectura);

}


//-----------------------------------------------------
//--------------------- LOOP --------------------------
//-----------------------------------------------------


void loop() 
{

    recibir_serial();

    if (datos_nuevos_serial) {
        Serial.print("Retroalimentacion: ");
        Serial.println(chars_recibidos_serial);

        if (strcmp(chars_recibidos_serial, "reset") == 0) {
            Serial.println("Reiniciando placa...");
            ESP.reset();
        }

        std::string mensaje_serial_rpi(chars_recibidos_serial);
        std::vector<std::string> mensaje_separado = separar_datos(mensaje_serial_rpi);

        enviar_respuesta(mensaje_separado);

        datos_nuevos_serial = false;
    }
  
  
    if (millis()-ultimo >= timer)
    {
        ultimo = millis();
        digitalWrite(LED_blink, !digitalRead(LED_blink));
    }
}


