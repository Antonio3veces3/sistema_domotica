int inputPin  = 15;

void setup(){
    pinMode(inputPin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
}

void loop(){
    int val = digitalRead(inputPin);
    if (val == HIGH) {
        Serial.println("Motion detected!");
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
        Serial.println("No Motion detected!");
        digitalWrite(LED_BUILTIN, LOW);
    }
}
