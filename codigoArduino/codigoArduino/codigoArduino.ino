#include <Arduino.h>

const int gasPin=9;
const int LDRPin = A0;
const int triggerPin = 7;
const int echoPin = 6;

long duration, distance;
int ldrStatus;
int gasStatus;

void setup() {
  Serial.begin(9600);
  
  pinMode(LDRPin, INPUT);
  pinMode(gasPin, INPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(triggerPin, OUTPUT);

}

void loop() {
  //Comienza proceso de sensor ultrasónico
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  //Envía señal HIGH por diez microsegundos
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);
  //Lee señal de echo (tiempo) y calcula distancia
  distance = microsecondsToCentimeters(pulseIn(echoPin, HIGH));

  //Lee datos de sensor ldr y de gas
  ldrStatus = analogRead(LDRPin);
  gasStatus = digitalRead(gasPin);

  //Enviar datos
  Serial.println(gasStatus);
  delay(100);
  Serial.println(distance);
  delay(100);
  Serial.println(ldrStatus);
  delay(500);
}

long microsecondsToCentimeters(long microseconds)
{
return microseconds / 29 / 2;
}
