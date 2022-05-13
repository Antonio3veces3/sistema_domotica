/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_microSD {
    
    public:   //Métodos Públicos  
        String filename = "", JSON_STRING = "";
    public:
        void initMicroSD( void );
        void fileID( void );
        String create_json(String accion, String advertencia);
        void JSON_SaveFile(String JSON_STRING);          
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void class_microSD::initMicroSD( void ){
  
  while(!SD.begin(MICROSD_PIN)){
    Serial.println( F ( "Error :( No se reconoció la MicroSD"));
    delay(1000);
  }
  Serial.println( F ( "¡La MicroSD se inicio exitosamente!"));
}

void class_microSD::fileID( void ){

  filename = '/';
  if (RTC.day < 10) filename += '0';
  filename += RTC.dia;
  if (RTC.month < 10) filename += '0';
  filename += RTC.month;
  filename += RTC.year;
  filename += EXTENSION;
}

void class_microSD::create_json( String accion, String advertencia ){

  JSON_STRING = " ";
  RTC.get_time ();
  RTC.format_time();
  RTC.format_date();
  DynamicJsonDocument doc ( 1024 );
  doc ["tiempo"]["fecha"] = RTC.fecha;
  doc ["tiempo"]["hora"] = RTC.tiempo;
  doc ["clima"]["temperatura"] = sensor.obtener_temperatura; 
  doc ["clima"]["humedad"] = sensor.obtener_temperatura;
  doc ["notificacion"]["accion"] = accion;
  doc ["notificacion"]["advertencia"] = advertencia;
  serializeJson(*doc, JSON_STRING);
  JSON_SaveFile(JSON_STRING);

}

void class_microSD::JSON_SaveFile( String JSON_STRING ){

  FileID();
  MicroSD_File = SD.open(filename, FILE_APPEND);
  if ( MicroSD_File ){
    MicroSD_File.print(JSON_STRING);
    MicroSD_File.println( ',' );
    MicroSD_File.close();
  }
  else
    Serial.print( F ("Error fatal"));
}