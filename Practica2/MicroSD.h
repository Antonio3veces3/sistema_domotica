/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_microSD {
    
    public:   //Métodos Públicos  
        String filename = "", JSON_STRING = "";
    public:
        void initMicroSD( void );
        void fileID( void );
        void JSON( void );
        void JSON_SaveFile( DynamicJsonDocument * );          
        
        String create_json_temp_hum(String date, int temp, int hum);
        String create_json_action(String date, String action); 
        String create_json_warning(String date, String warning);
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
  if (RTC.dia < 10) filename += '0';
  filename += RTC.dia;
  if (RTC.mes < 10) filename += '0';
  filename += RTC.mes;
  filename += RTC.ano;
  filename += EXTENSION;
}

void class_microSD::JSON( void ){

  RTC.get_time ();
  RTC.format_time();
  RTC.format_date();
  DynamicJsonDocument doc ( 1024 );
  doc ["temperatura"] = sensor.obtener_temperatura;
  doc ["humedad"] = sensor.obtener_humedad;
  doc["action"] = 
  doc ["tiempo"] = RTC.tiempo;
  doc ["fecha"] = RTC.fecha;
  JSON_SaveFile(&doc);

}

void class_microSD::JSON_SaveFile( DynamicJsonDocument *doc ){

  JSON_STRING = "";
  FileID();
  MicroSD_File = SD.open(filename, FILE_APPEND);
  if ( MicroSD_File ){
    serializeJson(*doc, JSON_STRING);
    MicroSD_File.print( JSON_STRING );
    MicroSD_File.println( ',' );
    MicroSD_File.close();
  }
  else
    Serial.print( F ("Error fatal"));
}

//Crea el JSON para la fecha y las acciones realizadas
String class_data_controller::create_json_action(String date, String action){
    String newJson;
    DynamicJsonDocument doc(1024); //Crea documento JSON

    //Agrega los valores de la fecha, hora y acciones realizadas
    doc["date"]  = date;
    doc["accion"]= action; 

    serializeJson(doc, newJson); //Guarda documento JSON en la variable String
    return newJson;//Retorna el JSON
}

//Crea el JSON para la fecha y las alertas emitidas
String class_data_controller::create_json_warning(String date, String warning){
    String newJson;
    DynamicJsonDocument doc(1024); //Crea documento JSON

    //Agrega los valores de la fecha, hora y advertencias emitidas
    doc["date"]  = date;
    doc["advertencia"]= warning; 

    serializeJson(doc, newJson); //Guarda documento JSON en la variable String
    return newJson; //Retorna el JSON
}
