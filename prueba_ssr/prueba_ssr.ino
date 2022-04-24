void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT); //Pin 5, D1 ESP8266, D5 Pin 5 ESP32
}

void loop() {
  digitalWrite(5,LOW);  
  delay(1000);
  digitalWrite(5,HIGH);  
  delay(1000);
}
