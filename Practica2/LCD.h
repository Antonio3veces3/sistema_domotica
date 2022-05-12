/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class class_lcd {
    public:   //Métodos Públicos 
        void initLCD(void);          
        void printLCD(void); 
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
void class_lcd::initLCD(void){ 
    lcd.init();
    lcd.backlight();
}

//Muestra los datos obtenidos en la LCD
void class_lcd::printLCD(void){  
    lcd.clear();
    lcd.createChar(0, customGrade); //Crea el icono personalizado
    lcd.setCursor(0,0); //Coloca el cursor en la posición dada
    lcd.print(String("T: " + String()); //Imprime la temperatura
    lcd.setCursor(2,0); 
    lcd.write(0); //Escribe un espacio
    lcd.setCursor(3,0);  
    lcd.print("C");  //Imprime la letra "C"
    lcd.setCursor(5,0); 
    lcd.print("H:" + String(hum)+"%");  //Imprime la humedad
}