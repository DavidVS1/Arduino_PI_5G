#include <Arduino.h>
#include <VirtualWire.h>

void configuracionTransmisor(){
    vw_set_ptt_inverted(true);
    pinMode(1,1);
    vw_setup(2000);      //Tiempo de espera
    vw_set_tx_pin(3);    //Pin donde se conecta el transmisor
 }
 
 void configuracionReceptor(){
    Serial.begin(9600); //Se inicia la comunicación serial
    vw_set_ptt_inverted(true);
    vw_setup(2000); //Tiempo de espera
    vw_set_rx_pin(3); //Pin donde se conecta el Arduino
    vw_rx_start(); //Se inicia la recepción de datos
 }
 
 void iniciarReceptor(){
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
 int a;
 
 void enviarTrama(String cadena){
    const char *msg = cadena.c_str(); //Mensaje a enviar
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx();  //Se hace la transmisión de datos
    delay(10); //Se espera un segundo
 }