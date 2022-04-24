/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <Config.h>
#include <EasyBuzzer.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_actuators {

  public:  //Variables Públicas
     int sinVal = 0;
     int toneVal = 0;

 public:   //Métodos Públicos             
    void initBuzzer(void);
    void EncenderLED(void);
    void ApagarLED(void);  
    void EncenderBuzzer(void);
    void ApagarBuzzer(void);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~*/

void class_actuators::initBuzzer(void){
  EasyBuzzer.setPin(26);
}

void class_actuators::EncenderLED(void){
    digitalWrite(25,LOW); //PIN RELAY
}

void class_actuators::ApagarLED(void){
    digitalWrite(25,HIGH);  //PIN RELAY
}

void class_actuators::EncenderBuzzer(void){
  EasyBuzzer.update();
  EasyBuzzer.beep(1000);
}
void class_actuators::ApagarBuzzer(void){
   EasyBuzzer.update();
   EasyBuzzer.stopBeep();
}
