const int LDRPin = A0;
int ldrStatus;

void setup() {
Serial.begin(9600);
pinMode(LDRPin, INPUT);
}
void loop() {

ldrStatus = analogRead(LDRPin);

if (ldrStatus >= 40) {
Serial.print(" LIGHT ON : ");

Serial.println(ldrStatus);

} else {

Serial.print("LIGHT OFF: ");

Serial.println(ldrStatus);
}
}   
