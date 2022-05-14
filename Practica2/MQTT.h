
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~VARIABLES PARA MQTT~~~~~~~~~~~~~~~~~~~~~~~~*/
const char* HOTSPOT_WIFI = "zaholy";
const char* HOTSPOT_PWD = "pelusatony";  
const char* MQTT_SERVER = "test.mosquitto.org";
#define MQTT_PORT 1883
#define TOPIC "esp32-RALMT/data"

class class_MQTT {

  public:
    void subscribe_MQTT( void );
    void publish_MQTT( void );
    void reconnect_MQTT( void );
    void setup_WiFi( void ); 
    void set_MQTT_server( void );
};

void class_MQTT::set_MQTT_server( void ){

  client.setServer(MQTT_SERVER, MQTT_PORT);
  
}

//Función para publicar
void class_MQTT::publish_MQTT( void ){

  Serial.println ("Publicando información...");
  client.publish(TOPIC, MSD.JSON_STRING.c_str());
  
}

//Función para reconectarse a MQTT
void class_MQTT::reconnect_MQTT( void ){

  if (!client.connected()){

    while (!client.connected()){
      Serial.print("Intentando la conexión MQTT...");
      String clientId = "ESP32Client-"; //Crea id del cliente MQTT
      clientId += String(random(0xffff), HEX); //Concatena un numero random hexadecimal
      if (client.connect(clientId.c_str())) {
        Serial.println("CONECTADO :D");
      } else {
        Serial.print("CONEXIÓN FALLIDA, rc =");
        Serial.print(client.state()); //Imprime estado del cliente
        Serial.println("Inténtalo de nuevo en 5 segundos");
        delay(5000);
      }
    }
  }
  client.loop();
  
}

void class_MQTT::setup_WiFi ( void ){

  delay(10);
  Serial.println("CONFIGURANDO WiFi:");
  WiFi.begin(HOTSPOT_WIFI, HOTSPOT_PWD);
  
  while ( WiFi.status ( ) != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  
  Serial.print("WiFi configurado con la IP: " );
  Serial.println(WiFi.localIP());
}
