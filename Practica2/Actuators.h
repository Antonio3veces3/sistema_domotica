#include <LiquidCrystal_I2C.h>

class class_actuators {

  public:                                   //Variables Públicas
     int sinVal = 0;
     int toneVal = 0;

 public:        
                          //Métodos Públicas
    void initLCD(void);
    void EncenderLED(void);
    void ApagarLED(void);  
    void imprimirLCD(float temp, float hum);
    void EncenderBuzzer(void);
    void ApagarBuzzer(void);
                         

             //Método para inicilizar el sensor DHT11
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PINES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

LiquidCrystal_I2C lcd(0x27, 16, 2); 
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~*/


void initLCD(void){
    lcd.init();
    lcd.backlight();
}

void class_actuators::imprimirLCD(float temp, float hum){
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
}

void class_actuators::EncenderLED(void){
    digitalWrite(0,LOW); 
}

void class_actuators::ApagarLED(void){
    digitalWrite(0,HIGH); 
}

void class_actuators::EncenderBuzzer(void){
    for(int x=0; x<180; x++){
        sinVal = (sin(x*(3.1412/180)));
        toneVal = 2000 + (int(sinVal*1000));
        tone(14, toneVal);
        delay(2);
    }
}
void class_actuators::ApagarBuzzer(void){
    noTone(14);
}
