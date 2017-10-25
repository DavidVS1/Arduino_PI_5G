#include <Arduino.h>
/*
#include <VirtualWire.h>
void setup()
{
Serial.begin(9600); //Se inicia la comunicación serial
vw_set_ptt_inverted(true);
vw_setup(2000); //Tiempo de espera
vw_set_rx_pin(3); //Pin donde se conecta el Arduino
vw_rx_start(); //Se inicia la recepción de datos
}
void loop()
{
uint8_t buf[VW_MAX_MESSAGE_LEN]; //Tamaño del mensaje
uint8_t buflen = VW_MAX_MESSAGE_LEN;
if (vw_get_message(buf, &buflen)) //Se verifica si hay //mensaje disponible para ser leido
{
int i;
for (i = 0; i < buflen; i++) //Se leen todos los caracteres
{
Serial.write(buf[i]); //Se guarda la información en una //matriz
}
Serial.println(); //Se imprime el mensaje en el monitor //serial
} 
}
*/
//_________________________________________________________Humedad
// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            2         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
//#define DHTTYPE           DHT11     // DHT 11 
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
//_________________________________________________________Humedad

//__________________________________________________Ultrasonico
int Pin_echo = 13; 
int Pin_trig = 12;    
int Pinrojo=6;
int Pinverde=5;
int buzzer=4;
//___________________________________________________
void setup() { 
 Serial.begin (9600); 

 pinMode(Pinverde,OUTPUT); //Definimos los pines
 pinMode(Pinrojo, OUTPUT); 
 pinMode(buzzer,OUTPUT);
 pinMode(Pin_trig, OUTPUT); 
 pinMode(Pin_echo, INPUT); 

 dht.begin();
 Serial.println("DHTxx Unified Sensor Example");
 // Print temperature sensor details.
 sensor_t sensor;
 dht.temperature().getSensor(&sensor);
 Serial.println("------------------------------------");
 Serial.println("Temperature");
 Serial.print  ("Sensor:       "); Serial.println(sensor.name);
 Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
 Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
 Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
 Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
 Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
 Serial.println("------------------------------------");
 // Print humidity sensor details.
 dht.humidity().getSensor(&sensor);
 Serial.println("------------------------------------");
 Serial.println("Humidity");
 Serial.print  ("Sensor:       "); Serial.println(sensor.name);
 Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
 Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
 Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
 Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
 Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
 Serial.println("------------------------------------");
 // Set delay between sensor readings based on sensor details.
 delayMS = sensor.min_delay / 1000;



} 

void loop() { 
 int duracion, cm; 
 digitalWrite(Pin_trig, LOW); 
 delayMicroseconds(2); 
 digitalWrite(Pin_trig, HIGH); 
 delayMicroseconds(10); 
 digitalWrite(Pin_trig, LOW); 
 duracion = pulseIn(Pin_echo, HIGH); 
 cm = duracion / 29 / 2;
 Serial.print("Distancia:");
 Serial.print(cm); 
 Serial.println(" cm");
 if (cm>20) //20 cm es la distancia de emergencia
{
 digitalWrite(Pinverde, HIGH); //En caso que un objeto esté lejos, pintamos el LED verde
 digitalWrite(Pinrojo, LOW);
 digitalWrite(buzzer, LOW);
}
else if (cm<20)
{
 digitalWrite(Pinverde, LOW); //Si el objeto está muy cerca, hacemos sonar la alarma buzzer y el LED rojo
 digitalWrite(Pinrojo, HIGH);
 tone(buzzer, 440, 500);
}
 delay(500); 


 // Delay between measurements.
 delay(delayMS);
 // Get temperature event and print its value.
 sensors_event_t event;  
 dht.temperature().getEvent(&event);
 if (isnan(event.temperature)) {
   Serial.println("Error reading temperature!");
 }
 else {
   Serial.print("Temperature: ");
   Serial.print(event.temperature);
   Serial.println(" *C");
 }
 // Get humidity event and print its value.
 dht.humidity().getEvent(&event);
 if (isnan(event.relative_humidity)) {
   Serial.println("Error reading humidity!");
 }
 else {
   Serial.print("Humidity: ");
   Serial.print(event.relative_humidity);
   Serial.println("%");
 }
}
