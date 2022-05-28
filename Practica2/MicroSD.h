/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_microSD {
    
    public:   //Variables Públicas  
        String filename = "", JSON_STRING = "";

    public: //Métodos Públicas  
        void initMicroSD( void );
        void fileID( void );
        void create_json(String, String);
        void JSON_SaveFile(DynamicJsonDocument *);          
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Inicializa la microSD
void class_microSD::initMicroSD( void ){
  
  while(!SD.begin(MICROSD_PIN)){  //Verifica si se reconoce la micro SD
    Serial.println( F ( "Error :( No se reconoció la MicroSD"));
    delay(1000);
  }
  Serial.println( F ( "¡La MicroSD se inicio exitosamente! :D"));
}

//Da el nombre al archivo que se guarda en la SD, el cual será la fecha que recopile el RTC (dia/mes/año)
void class_microSD::fileID( void ){

  filename = '/';
  if (RTC.dia < 10) filename += '0'; //Agrega un 0 en caso de que DIA sea menor a 10
  filename += RTC.dia;
  if (RTC.mes < 10) filename += '0'; //Agrega un 0 en caso de que MES sea menor a 10
  filename += RTC.mes;
  filename += RTC.ano;
  filename += EXTENSION; //Guarda el nombre del archivo json
}

//Crea el JSON con todos los valores obtenidos
void class_microSD::create_json( String accion, String advertencia ){

  RTC.getDataTime(); //Obtiene las variables para la fecha y hora
  RTC.formatTime(); //Obtiene el formato de la fecha
  RTC.formatDate(); //Obtiene el formato de la hora
  DynamicJsonDocument doc(1024); //Inicializa el doc JSON
  doc ["tiempo"]["fecha"] = RTC.fecha; //Guarda la fecha
  doc ["tiempo"]["hora"] = RTC.hora;  //Crea el vector tiempo para guardar la fecha y hora
  doc ["clima"]["temperatura"] = sensor.temperatura; //Agrega la temperatura
  doc ["clima"]["humedad"] = sensor.humedad;   //Crea el vector clima para guarda la temperatura y humedad
  doc ["notificacion"]["accion"] = accion; //Agrega una acción
  doc ["notificacion"]["advertencia"] = advertencia;   //Crea el vector notificacion para guardar las acciones y advertencias
  JSON_SaveFile(&doc); //Guarda el json en un archivo .json de la micro SD
}

//Guarda el JSON en el archivo .json
void class_microSD::JSON_SaveFile( DynamicJsonDocument *doc ){

  JSON_STRING = " "; //Variable string para ahi guardar el objeto json
  fileID();
  microSD_file = SD.open(filename, FILE_APPEND); //Abre el archivo
  if ( microSD_file ){ //Pregunta si esta disponible la tarjeta para guardar los datos
    serializeJson(*doc, JSON_STRING); //Guarda el objeto json en un string
    Serial.print( F ("DATOS GUARDADOS :D \n")); 
    microSD_file.print(JSON_STRING); //Guarda los valores obtenidos
    microSD_file.println( ',' ); 
    microSD_file.close(); //Cierra el archivo
  }
  else
    Serial.print( F ("Error fatal. No se pudo guardar la información en la tarjeta SD :( \n")); //Mensaje de que no guardó la información

}
