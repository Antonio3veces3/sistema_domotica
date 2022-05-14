/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_microSD {
    
    public:   //Métodos Públicos  
        String filename = "", JSON_STRING = "";
    public:
        void initMicroSD( void );
        void fileID( void );
        String create_json(String, String);
        void JSON_SaveFile(String);          
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void class_microSD::initMicroSD( void ){
  
  while(!SD.begin(MICROSD_PIN)){
    Serial.println( F ( "Error :( No se reconoció la MicroSD"));
    delay(1000);
  }
  Serial.println( F ( "¡La MicroSD se inicio exitosamente! :D"));
}

void class_microSD::fileID( void ){

  filename = '/';
  if (RTC.dia < 10) filename += '0';
  filename += RTC.dia;
  if (RTC.mes < 10) filename += '0';
  filename += RTC.mes;
  filename += RTC.ano;
  filename += EXTENSION;
}

String class_microSD::create_json( String accion, String advertencia ){

  JSON_STRING = " ";
  RTC.getDataTime();
  RTC.formatTime();
  RTC.formatDate();
  DynamicJsonDocument doc(1024);
  doc ["tiempo"]["fecha"] = RTC.fecha;
  doc ["tiempo"]["hora"] = RTC.hora;
  doc ["clima"]["temperatura"] = sensor.temperatura; 
  doc ["clima"]["humedad"] = sensor.humedad;
  doc ["notificacion"]["accion"] = accion;
  doc ["notificacion"]["advertencia"] = advertencia;
  serializeJson(doc, JSON_STRING);
  JSON_SaveFile(JSON_STRING);

}

void class_microSD::JSON_SaveFile( String JSON_STRING ){

  fileID();
  microSD_file = SD.open(filename, FILE_APPEND);
  if ( microSD_file ){
    microSD_file.print(JSON_STRING);
    microSD_file.println( ', \n' );
    microSD_file.close();
  }
  else
    Serial.print( F ("Error fatal. No se pudo guardar la información :("));
}
