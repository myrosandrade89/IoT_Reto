#include <ArduinoJson.h>
//#include <ESP8266WiFi.h>
#include <ArduinoHttpClient.h>
#include <Arduino.h>


//Declaramos el puerto de salida para el gas
const int Gas = 9;

/* Transformación a objeto JSON para el código de Myros:) 
StaticJsonBuffer<200> jsonBuffer;
JsonObject& objetoGas = jsonBuffer.createObject();

objetoGas["sensor"] = "gas" 
objetoGas["data"] =  //Lo que leas del serial

*/ 


void setup() {
  pinMode(Gas, INPUT); //Establecemos que el puerto 9 (Gas) será de input
  Serial.begin(9600); //Establecemos el serial y su respectiva velocidad
}

void loop() {
  //Si detecta gas
  if(digitalRead(Gas) == HIGH){
      //Escribimos en el serial un uno      
      Serial.println("1");
    }

}
