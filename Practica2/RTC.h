/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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
    if (! rtc.begin()) { //Si no encuentra el RTC muestra un mensaje de error
        Serial.println("No se pudo encontrar el módulo RTC");
        Serial.flush();
        while (1) delay(10);
    }

    if (! rtc.isrunning()) { //Si no se inicializa el RTC muestra un mensaje de error
        Serial.println("Sucedió un error inesperado. El módulo RTC no esta corriendo");
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

//Da el formato de fecha (dia/mes/año)
void class_rtc::formatDate(void){

    fecha = "";
    if (dia < 10) fecha += '0'; //Agrega un 0 en caso de que el DÍA sea menor a 10
    fecha += dia;
    fecha += '/';
    if (mes < 10) fecha += '0'; //Agrega un 0 en caso de que el MES sea menor a 10
    fecha += mes;
    fecha += '/';
    fecha += ano; //Guarda el formato de la fecha

}

//Da el formato de la hora (hora:minuto)
void class_rtc::formatTime(void){

    hora = "";
    if (horas < 10) hora += '0';  //Agrega un 0 en caso de que la HORAS sean menores a 10
    hora += horas;
    hora += ':';
    if (minuto < 10) hora += '0'; //Agrega un 0 en caso de que el MINUTOS sean menores a 10
    hora += minuto;
    hora += ':';
    if (segundo < 10) hora += '0'; //Agrega un 0 en caso de que los SEGUNDOS sean menores a 10
    hora += segundo; //Guarda el formato de la hora
}
