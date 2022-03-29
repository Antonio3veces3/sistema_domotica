/*#define PIN_SSR 0
#define PIN_BZZ 14*/

class class_actuators {

  public:                                   //Variables Públicas
     int sinVal = 0;
     int toneVal = 0;


 public:                                  //Métodos Públicas
    void EncenderLED(void);
    void ApagarLED(void);  
    
    void EncenderBuzzer(void);
    void ApagarBuzzer(void);
                         //Método para obtener la temperatura del sensor DHT11  //Método para obtener el movimiento

             //Método para inicilizar el sensor DHT11
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PINES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~*/

void class_actuators::EncenderLED(void){
    digitalWrite(12,LOW); 
}

void class_actuators::ApagarLED(void){
    digitalWrite(12,HIGH); 
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
    //
}
