#include <Ethernet.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

#define CE_PIN 8
#define CSN_PIN 9

int F01T01SHum; // Constante para la humedad

//Direccion fisica del Arduino
byte mac []={ 0xDE, 0xAD, 0xBE, 0xEF, 0xF0, 0x00 };

//Direccion IP a utilizar por el Arduino
byte ip []={ 172, 16, 30, 207 };

//Direccion IP del servidor
byte server []={ 172, 16, 30, 201 };

//Inicializar libreria ethernet y configurar parametros de red
EthernetClient cliente;

RF24 radio(CE_PIN, CSN_PIN);
float datos[2];

void setup() {
  
Serial.begin(9600);
radio.setPALevel(RF24_PA_MIN);
radio.openReadingPipe(0, mac);
  radio.begin();
radio.startListening();

Ethernet.begin(mac, ip); // Inicializamos el Ethernet Shield

}

void loop() {

 if(radio.available())
 {
  radio.read(datos, sizeof(datos));
  Serial.print("F01T01SHum=");
  Serial.print(datos[1]);
 }
 else
 {
  Serial.println("No hay datos");
 }
 delay(10000);

F01T01SHum=datos[1];

if (isnan(F01T01SHum)) { // Comprobamos si ha habido algun error en la lectura
    Serial.println("Error obteniendo datos");
     delay(10000);
     return;
}

Serial.print("Envio de dato, conectando...");

  if (cliente.connect(server, 80)>0) {//Conexion con el servidor
    cliente.print("GET /arduino/control/conexion_arduino.php?F01T01SHum_php="); // Enviamos los datos por GET
    cliente.print(F01T01SHum);
    cliente.println("HTTP/1.8");
    cliente.println("User-Agent: Arduino 1.8");
    cliente.println();
    Serial.println("envio con exito");
    delay(10000);
  } else{
    Serial.println("Fallo en la conexion");
    delay(10000);
    }
}
