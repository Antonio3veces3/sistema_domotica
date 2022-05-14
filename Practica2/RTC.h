/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_rtc {
    public:
        String fecha = "", hora = "";
        uint8_t horas, minuto, segundo, dia, mes;
        uint16_t ano;
  
    public:   //Métodos Públicos 
        void initRTC(void);           
        void getDataTime(void);
        void formatDate(void);
        void formatTime(void); 
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Inicializar el RTC
void class_rtc::initRTC(void){ 
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
void class_rtc::getDataTime(void){ 
    DateTime now = rtc.now(); //Variable que almacena los valores del RTC

    //Variables que almacenan los años, meses y días
    ano = now.year();
    mes = now.month(); 
    dia = now.day();

    //Variables que almacenan las horas, minutos y segundos
    horas = now.hour();
    minuto = now.minute();
    segundo = now.second();
}

void class_rtc::formatDate(void){

    fecha = "";
    if (dia < 10) fecha += '0';
    fecha += dia;
    fecha += '/';
    if (mes < 10) fecha += '0';
    fecha += mes;
    fecha += '/';
    fecha += ano;

}

void class_rtc::formatTime(void){

    hora = "";
    if (horas < 10) hora += '0';
    hora += horas;
    hora += ':';
    if (minuto < 10) hora += '0';
    hora += minuto;
    hora += ':';
    if (segundo < 10) hora += '0';
    hora += segundo;
}
