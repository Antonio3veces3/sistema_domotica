#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Inicia el LCD en la dirección 0x27, 16 caracteres y 2 líneas
DHT dht(D3, DHT11);

float temp = 0.0, hum = 0.0;

byte customChar1[] = {
  B00011,
  B00011,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.init();
  dht.begin();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  
  lcd.clear();
  lcd.createChar(0, customChar1);
  lcd.setCursor(0,0);
  lcd.print("Temp: " + String(temp) + " C");
  lcd.setCursor(11,0);
  lcd.write(0);
  lcd.setCursor(12,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Hum: " + String(hum) + " %");

  delay(1000);
}
