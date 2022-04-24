/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Librerías para manejo del Buzzer
#include <Config.h>
#include <EasyBuzzer.h> 

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_actuators {
 public:   //Métodos Públicos             
    void EncenderLED(void); 
    void ApagarLED(void);  
    void EncenderBuzzer(void);
    void ApagarBuzzer(void);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Inicializa el buzzer
void initBuzzer(void){
  EasyBuzzer.setPin(buzzer); 
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Enciende el LED
void class_actuators::EncenderLED(void){
    digitalWrite(relay,LOW); //PIN RELAY
}

//Apaga el LED
void class_actuators::ApagarLED(void){
    digitalWrite(relay,HIGH);  //PIN RELAY
}

//Enciende el buzzer
void class_actuators::EncenderBuzzer(void){
  EasyBuzzer.update();
  EasyBuzzer.beep(1000);
}

//Apaga el buzzer
void class_actuators::ApagarBuzzer(void){
   EasyBuzzer.update();
   EasyBuzzer.stopBeep();
}
