/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_data_controller {
    public:   //Métodos Públicos            
       void initLCD(void);
       void initRTC(void);
       //void initSD (int, int, int, int);
       String getDataTime(void);
       void imprimirLCD(int temp, int hum, String date);
       void createFile(fs::FS &fs, const char * path, const char * message);
       void appendFile(fs::FS &fs, const char * path, const char * message);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

LiquidCrystal_I2C lcd(0x27, 16, 2); 
byte customChar1[] = {
        B00011,
        B00011,    
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

void initLCD(void){
    lcd.init();
    lcd.backlight();
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~*/

void class_data_controller::imprimirLCD(int temp, int hum, String date){
    lcd.clear();
    lcd.createChar(0, customChar1);
    lcd.setCursor(0,0);
    lcd.print(date);
    lcd.setCursor(0,1);
    lcd.print(String(temp));
    lcd.setCursor(2,1);
    lcd.write(0);
    lcd.setCursor(3,1);
    lcd.print("C");
    lcd.setCursor(5,1);
    lcd.print("Hum:" + String(hum)+"%");
}

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void class_data_controller::initRTC(void){
    if (! rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }

    if (! rtc.isrunning()) {
        Serial.println("RTC is NOT running, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

String class_data_controller::getDataTime(void){
    DateTime now = rtc.now();
    int y = now.year();
    int mon = now.month();
    int d = now.day();

    int h = now.hour();
    int m = now.minute();
    int s = now.second();

    String date = String(d) + "/" + String(mon) + "/" + String(y) + " " + String(h) + ":" + String(m);
    return date;
}

/*void class_data_controller::initSD (int SD_SCK, int SD_MISO, int SD_MOSI, int SD_CS){
    SPIClass sd_spi(HSPI);
    sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  
    if (!SD.begin(SD_CS, sd_spi))
        Serial.println("SD Card: mounting failed.");
    else
        Serial.println("SD Card: mounted.");
}*/

void class_data_controller::createFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
      Serial.println("Failed to open file for writing");
      return;
  }
  if(file.print(message)){
      Serial.println("File written");
  } else {
      Serial.println("Write failed");
  }
  file.close();
}

void class_data_controller::appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
      Serial.println("Failed to open file for appending");
      return;
  }
  if(file.print(message)){
      Serial.println("Message appended");
  } else {
      Serial.println("Append failed");
  }
  file.close();
}
