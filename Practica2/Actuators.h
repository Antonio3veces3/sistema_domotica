/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_actuators {
 public:   //Métodos Públicos  
    void initBuzzer( void );           
    void EncenderLED( void ); 
    void ApagarLED( void );  
    void EncenderBuzzer( void );
    void ApagarBuzzer( void );
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Inicializa el buzzer
void class_actuators::initBuzzer( void ){
  EasyBuzzer.setPin(BUZZER_PIN); 
}

//Enciende el LED
void class_actuators::EncenderLED( void ){
    digitalWrite(RELAY_PIN,LOW); //PIN RELAY
}

//Apaga el LED
void class_actuators::ApagarLED( void ){
    digitalWrite(RELAY_PIN,HIGH);  //PIN RELAY
}

//Enciende el buzzer
void class_actuators::EncenderBuzzer( void ){
  EasyBuzzer.update();
  EasyBuzzer.beep(1000);
}

//Apaga el buzzer
void class_actuators::ApagarBuzzer( void ){
   EasyBuzzer.update();
   EasyBuzzer.stopBeep();
}
