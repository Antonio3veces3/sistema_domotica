void setup() {
  Serial.begin(115200);
  pinMode(25, OUTPUT); //Pin 5, D1 ESP8266, D5 Pin 5 ESP32
}

void loop() {
  digitalWrite(25,LOW);  
  delay(1000);
  digitalWrite(25,HIGH);  
  delay(1000);
}
