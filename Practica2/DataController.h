/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <LiquidCrystal_I2C.h>

//Librería para manejo de JSON
#include <ArduinoJson.h>

//Librería para módulo Tiny RTC
#include "RTClib.h"

//Librería para módulo Micro-SD
#include "FS.h"
#include "SD.h"
#include "SPI.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_data_controller {
    public:   //Métodos Públicos            
       String getDataTime(void); 
       void imprimirLCD(int temp, int hum, String date); 
       void createFile(fs::FS &fs, const char * path, const char * message);
       void appendFile(fs::FS &fs, const char * path, const char * message); 
       String crear_json_temp_hum(String date, int temp, int hum);
       String crear_json_action(String date, String action); 
       String crear_json_warning(String date, String warning);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

LiquidCrystal_I2C lcd(0x27, 16, 2); //Configura la LCD a 16x2

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

//Inicializar la LCD
void initLCD(void){ 
    lcd.init();
    lcd.backlight();
}

RTC_DS1307 rtc; //Crea instancia módulo Tiny RTC

//Inicializar el RTC
void initRTC(void){ 
    if (! rtc.begin()) { //Si no lo encuentra muestra un mensaje de error
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }

    if (! rtc.isrunning()) { //Si no se inicializa muestra un mensaje de error
        Serial.println("RTC is NOT running, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Muestra los datos obtenidos en la LCD
void class_data_controller::imprimirLCD(int temp, int hum, String date){  
    lcd.clear();
    lcd.createChar(0, customGrade); //Crea el icono personalizado
    lcd.setCursor(0,0); //Coloca el cursor en la posición dada
    lcd.print(date); //Imprime la fecha y hora
    lcd.setCursor(0,1); 
    lcd.print(String(temp)); //Imprime la temperatura
    lcd.setCursor(2,1); 
    lcd.write(0); //Escribe un espacio
    lcd.setCursor(3,1);  
    lcd.print("C");  //Imprime la letra "C"
    lcd.setCursor(5,1); 
    lcd.print("Hum:" + String(hum)+"%");  //Imprime la humedad
}

//Obtiene la hora y fecha
String class_data_controller::getDataTime(void){ 
    DateTime now = rtc.now(); //Variable que almacena los valores del RTC

    //Variables que almacenan los años, meses y días
    int y = now.year();
    int mon = now.month(); 
    int d = now.day();

    //Variables que almacenan las horas, minutos y segundos
    int h = now.hour();
    int m = now.minute();
    int s = now.second();

    //Variable que muestra el formato de la fecha y hora
    String date = String(d) + "/" + String(mon) + "/" + String(y) + " " + String(h) + ":" + String(m);
    return date; //Retornamos la variable date
}

//Crea un archivo en la micro-SD
void class_data_controller::createFile(fs::FS &fs, const char * path, const char * message){  
  Serial.printf("Creating file: %s\n", path);

  File file = fs.open(path, FILE_WRITE); //Abre el archivo
  if(!file){ //Si no lo encuentra, imprime un mensaje de error
      Serial.println("Failed to open file for create");
      return;
  } 
  if(file.print(message)){ //Si lo encuentra, imprime que se creo exitosamente
      Serial.println("File created");
  } else {
      Serial.println("Create failed"); //De lo contrario, imprime un mensaje de error
  }
  file.close(); //Cierra el archivo
}

//Agrega los datos obtenidos al archivo almacenado en la micro-SD
void class_data_controller::appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND); //Abre el archivo
  if(!file){ //Si no lo encuentra, imprime un mensaje de error
      Serial.println("Failed to open file for appending");
      return;
  }
  if(file.print(message)){ //Si escribe el mensaje, imprime un mensaje de exito
      file.print(",\n");
      Serial.println("Message appended");
  } else {
      Serial.println("Append failed"); //De lo contario, imprime un mensaje de error
  }
  file.close(); //Cierra el archivo
}

//Crea el JSON para la fecha, hora, temperatura y humedad 
String class_data_controller::crear_json_temp_hum(String date, int temp, int hum){
  String newJson; 
  DynamicJsonDocument doc(1024); //Crea documento JSON

  //Agrega los valores de la fecha, hora, temperatura y humedad
  doc["date"] = date;
  doc["temperatura"] = temp;
  doc["humedad"] = hum;

  serializeJson(doc, newJson); //Guarda documento JSON en la variable String
  return newJson; //Retorna el JSON
}

//Crea el JSON para la fecha y las acciones realizadas
String class_data_controller::crear_json_action(String date, String action){
    String newJson;
    DynamicJsonDocument doc(1024); //Crea documento JSON

    //Agrega los valores de la fecha, hora y acciones realizadas
    doc["date"]  = date;
    doc["accion"]= action; 

    serializeJson(doc, newJson); //Guarda documento JSON en la variable String
    return newJson;//Retorna el JSON
}

//Crea el JSON para la fecha y las alertas emitidas
String class_data_controller::crear_json_warning(String date, String warning){
    String newJson;
    DynamicJsonDocument doc(1024); //Crea documento JSON

    //Agrega los valores de la fecha, hora y advertencias emitidas
    doc["date"]  = date;
    doc["advertencia"]= warning; 

    serializeJson(doc, newJson); //Guarda documento JSON en la variable String
    return newJson; //Retorna el JSON
}
