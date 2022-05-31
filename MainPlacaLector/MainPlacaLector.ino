#include "LectorESPNOW.h"
#include <SPI.h>     
#include <MFRC522.h>     


#define T_RELE 1500

#define LED_VERDE 15
#define LED_ROJO 2
#define RELE 5

#define RST_PIN  4      
#define SS_PIN  0   

uint8_t MAC_serial[6] = {0x2C, 0xF4, 0x32, 0x4A, 0x94, 0xA1};

byte mac[6];

MFRC522 mfrc522(SS_PIN, RST_PIN);
byte LecturaUID[4];
char id_tarjeta_leida[32];

unsigned long inicio_rele = 0;

unsigned long ultimo_rojo = 0;
unsigned long ultimo_parpadeo_rojo = 0;

unsigned long ultimo_verde = 0;
unsigned long ultimo_parpadeo_verde = 0;

unsigned long retraso_lectura = 0;

bool en_espera = false;

typedef struct mensaje_orden_rpi {
  int ms_led_rojo_encendido;
  bool parpadeo_rojo;
  int ms_led_verde_encendido;
  bool parpadeo_verde;
  bool acceso;
} mensaje_orden_rpi;


bool comprobar_lector(){
    bool tarjeta_leida = false;

    if (mfrc522.PICC_IsNewCardPresent()) 
    {
        if (mfrc522.PICC_ReadCardSerial()){ 
            tarjeta_leida = true;
        }
    }

    if (tarjeta_leida) {

        mensaje_lectura lectura;
        memcpy(&lectura.mac, &mac, sizeof(mac));

        for (byte i = 0; i < mfrc522.uid.size; i++){
            LecturaUID[i] = mfrc522.uid.uidByte[i];     
        }

        snprintf(id_tarjeta_leida, 32, "%x:%x:%x:%x", LecturaUID[0], LecturaUID[1], LecturaUID[2], LecturaUID[3]);
        Serial.print("Tarjeta leida con id -> ");
        Serial.println(id_tarjeta_leida);

        strcpy(lectura.id_tarjeta, id_tarjeta_leida);

        esp_now_send(MAC_serial, (uint8_t *) &lectura, sizeof(lectura));

    }
    
    return tarjeta_leida;
    
}

mensaje_orden_rpi leds;


//-----------------------------------------------------
void setup() {
    Serial.begin(115200);
    pinMode(RELE, OUTPUT);     // Inicializar el pin del relé, funciona con lógica inversa
    pinMode(LED_ROJO, OUTPUT);  
    pinMode(LED_VERDE, OUTPUT);

    digitalWrite(RELE, HIGH);

    WiFi.mode(WIFI_STA);
    WiFi.macAddress(mac);


    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_add_peer(MAC_serial, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

    esp_now_register_recv_cb(al_recibir_mensaje);
    esp_now_register_send_cb(al_mandar_datos);

    SPI.begin();        
    mfrc522.PCD_Init();    

    leds.ms_led_rojo_encendido = 0;
    leds.parpadeo_rojo = 0;
    leds.ms_led_verde_encendido = 0;
    leds.parpadeo_verde = 0;
    leds.acceso = 0;


    mensaje_lectura registro;
    memcpy(&registro.mac, &mac, sizeof(mac));
    strcpy(registro.id_tarjeta, "registro");

    esp_now_send(MAC_serial, (uint8_t *) &registro, sizeof(registro));

}

//-----------------------------------------------------

void loop() 
{

    if (millis()-inicio_rele < T_RELE && millis() > T_RELE) {

        Serial.println("La puerta se abre");
        digitalWrite(RELE, LOW);
      
    } else {

        digitalWrite(RELE, HIGH);

    }

    if (millis()-ultimo_rojo < leds.ms_led_rojo_encendido) {

        if (leds.parpadeo_rojo && millis()-ultimo_parpadeo_rojo >= 250) {

            digitalWrite(LED_ROJO, !digitalRead(LED_ROJO));
            ultimo_parpadeo_rojo = millis();

        } else if (!leds.parpadeo_rojo) {

            digitalWrite(LED_ROJO, HIGH); 

        }

    } else {

        digitalWrite(LED_ROJO, LOW); 

    }

    if (millis()-ultimo_verde < leds.ms_led_verde_encendido) {

        if (leds.parpadeo_verde && millis()-ultimo_parpadeo_verde >= 250) {

            digitalWrite(LED_VERDE, !digitalRead(LED_VERDE));
            ultimo_parpadeo_verde = millis();

        } else if (!leds.parpadeo_verde){

            digitalWrite(LED_VERDE, HIGH); 

        }

    } else {

        digitalWrite(LED_VERDE, LOW); 

    }

    if (!en_espera) {

        en_espera = comprobar_lector();
        retraso_lectura = millis();

    } 
    else {

        if (millis()-retraso_lectura >= 1000) {
            en_espera = false;
        }

    }
        
}

void al_recibir_mensaje(uint8_t * mac, uint8_t *datos_recibidos, uint8_t len) {
  mensaje_orden_rpi respuesta;
  memcpy(&respuesta, datos_recibidos, sizeof(respuesta));

  if (respuesta.ms_led_rojo_encendido == -1) {
    Serial.println("Codigo de reinicio recibido. Reiniciando placa...");
    ESP.reset();
  }

  memcpy(&leds, datos_recibidos, sizeof(leds));

  if (respuesta.acceso) {
    inicio_rele = millis();
  }
  
  ultimo_rojo = millis();
  ultimo_verde = millis();

  ultimo_parpadeo_rojo = millis();
  ultimo_parpadeo_verde = millis();

}
