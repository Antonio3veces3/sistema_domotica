/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_actuators {

  public:  //Variables Públicas
     int sinVal = 0;
     int toneVal = 0;

 public:   //Métodos Públicos             
    //void initLCD(void);
    void EncenderLED(void);
    void ApagarLED(void);  
    void EncenderBuzzer(void);
    void ApagarBuzzer(void);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~*/
void class_actuators::EncenderLED(void){
    digitalWrite(36,LOW); //PIN RELAY
}

void class_actuators::ApagarLED(void){
    digitalWrite(36,HIGH);  //PIN RELAY
}

void class_actuators::EncenderBuzzer(void){
    for(int x=0; x<180; x++){
        sinVal = (sin(x*(3.1412/180)));
        toneVal = 2000 + (int(sinVal*1000));
        //tone(35, toneVal); //PIN BUZZER
        delay(2);
    }
}
void class_actuators::ApagarBuzzer(void){
   //noTone(35); //PIN BUZZER
}
