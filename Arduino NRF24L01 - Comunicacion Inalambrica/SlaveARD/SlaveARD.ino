#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

#define CE_PIN 8
#define CSN_PIN 9

//Direccion fisica del Arduino
const byte mac []={ 0xDE, 0xAD, 0xBE, 0xEF, 0xF0, 0x00 };

RF24 radio(CE_PIN, CSN_PIN); // CE, CSN

float datos[2];

void setup() {
radio.begin();
Serial.begin(9600);
radio.openWritingPipe(mac);
radio.setPALevel(RF24_PA_MIN);
radio.stopListening();
}

void loop() {
  
 datos[1]=analogRead(A1);

 bool ok=radio.write(datos, sizeof(datos));

 if(ok)
 { 
 Serial.print("Datos enviados:");
 Serial.println(datos[1]);
 }
 else
 {
    Serial.println("No se ha enviado");
 }
 delay(10000);
}
