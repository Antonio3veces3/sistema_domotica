/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_rtc {
    public:
        String date = "", time = "";
        uint8_t hour, minute, second, day, month;
        uint16_t year;
  
    public:   //Métodos Públicos 
        void initRTC(void);           
        String getDataTime(void);
        void formatDate(void);
        void formatTime(void); 
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Inicializar el RTC
void initRTC(void){ 
    if (! rtc.begin()) { //Si no lo encuentra muestra un mensaje de error
        Serial.println("No se pudo encontrar el módulo RTC");
        Serial.flush();
        while (1) delay(10);
    }

    if (! rtc.isrunning()) { //Si no se inicializa muestra un mensaje de error
        Serial.println("Sucedió un error inesperado. El módulo RTC no esta corriendo, hay que ajustar la fecha.");
    }
}


//Obtiene la hora y fecha
String class_rtc::getDataTime(void){ 
    DateTime now = rtc.now(); //Variable que almacena los valores del RTC

    //Variables que almacenan los años, meses y días
    year = now.year();
    month = now.month(); 
    day = now.day();

    //Variables que almacenan las horas, minutos y segundos
    hour = now.hour();
    minute = now.minute();
    second = now.second();
}

void class_rtc::formatDate(void){

    date = "";
    if (day < 10) date += '0';
    date += day;
    date += '/';
    if (month < 10) date += '0';
    date += month;
    date += '/';
    date += year;

}

void class_rtc::formatTime(void){

    time = "";
    if (hora < 10) time += '0';
    time += hora;
    time += ':';
    if (minute < 10) time += '0';
    time += minute;
    time += ':';
    if (second < 10) time += '0';
    time += second;
}