/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_actuators {
  public: 
      String date_time;
  
  public:   //Métodos Públicos  
      void initBuzzer( void );           
      void EncenderLED( void ); 
      void ApagarLED( void );  
      void EncenderBuzzer( void );
      void ApagarBuzzer( void );
      void initLCD( void );          
      void printLCD( int, int, int ); 
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

byte customGrade[] = { //Icono personalizado para el simbolo de los grados (°)
        B00011,
        B00011,    
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
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

//Inicializar la LCD
void class_actuators::initLCD( void ){ 
    lcd.init();
    lcd.backlight();
}

//Muestra los datos obtenidos en la LCD
void class_actuators::printLCD( int temp, int hum, int lum ){  
 
    RTC.formatDate(); //Obtiene la fecha en el formato dia/mes/año
    RTC.formatTime();  //Obtiene la hora en el formato hora:minuto

    date_time = RTC.fecha + " " + RTC.hora;  //Guarda la fecha y hora en un string

    lcd.clear();
    lcd.createChar(0, customGrade); //Crea el icono personalizado
    lcd.setCursor(0,0); //Coloca el cursor en la posición dada
    lcd.print(date_time);  //Imprime la fecha 
    lcd.setCursor(0,1); 
    lcd.print(String(temp)); //Imprime la temperatura 
    lcd.setCursor(2,1); 
    lcd.write(0); //Escribe un espacio
    lcd.setCursor(3,1);  
    lcd.print("C");  //Imprime la letra "C" para la temperatura
    lcd.setCursor(5,1); 
    lcd.print("H:" + String(hum)+"%");  //Imprime la humedad
    lcd.setCursor(11,1);
    lcd.print("L:" + String(lum)); //Imprime la luminosidad
}
