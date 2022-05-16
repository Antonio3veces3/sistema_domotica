/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class class_lcd {
    public:

    public:   //Métodos Públicos 
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Inicializar la LCD
void class_lcd::initLCD( void ){ 
    lcd.init();
    lcd.backlight();
}

//Muestra los datos obtenidos en la LCD
void class_lcd::printLCD( int temp, int hum, int lum ){  
 
    RTC.formatDate(); //Obtiene la fecha en el formato dia/mes/año
    RTC.formatTime();  //Obtiene la hora en el formato hora:minuto

    String date_time = RTC.fecha + " " + RTC.hora;  //Guarda la fecha y hora en un string

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
