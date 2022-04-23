#include "RTClib.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

class class_data_controller {
    public:
        void initRTC (void);
        void initSD (int, int, int, int);
        String getDataTime (void);
        void createFile (fs::FS &fs, const char * path, const char * message );
        void appendFile(fs::FS &fs, const char * path, const char * message );
};

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void class_data_controller::initRTC ( void ){
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

String class_data_controller::getDataTime ( void ){
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
