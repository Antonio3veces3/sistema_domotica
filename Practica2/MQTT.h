
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~VARIABLES PARA MQTT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
const char* HOTSPOT_WIFI = "zaholy";
const char* HOTSPOT_PWD = "pelusatony";  
const char* MQTT_SERVER = "test.mosquitto.org";
#define MQTT_PORT 1883
#define TOPIC "esp32-RALMT/data"
#define BUFFER_SIZE (50)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_MQTT {
  public:
    unsigned long lastMsg = 0;
    char msg[BUFFER_SIZE];
    int value = 0;

  public: //Métodos públicos
    void subscribe_MQTT( void );
    void publish_MQTT( void );
    void reconnect_MQTT( void );
    void setup_WiFi( void ); 
    void set_MQTT_server( void );
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Función que se ejecuta cuando se recibe un mensaje
void callback(char* topic, byte* payload, unsigned int length){

  Serial.print("Mensaje del tema [");
  Serial.print(topic);
  Serial.print("] : ");

  //Almacenamiento del mensaje que llega desde el mqtt
  String message;
  for(int i = 0; i < length; i++){
    message = message + (char) payload[i];
  }
  
  Serial.print(message);
  Serial.println();
 
}

//Inicializar el servidor 
void class_MQTT::set_MQTT_server( void ){

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  
}

//Método para publicar el JSON por MQTT
void class_MQTT::publish_MQTT( void ){

  Serial.println ("Publicando información...");
  client.publish(TOPIC, MSD.JSON_STRING.c_str());
  
}

//Función para reconectarse a MQTT
void class_MQTT::reconnect_MQTT( void ){

 //El condicional y bucle sirven para saber si el cliente está correctamente conectado
  if ( !client.connected() ){
    while (!client.connected () ){
      Serial.print("Intentando la conexión MQTT...");
  
      String clientId = "ESP32Client-"; //Crea id del cliente MQTT
      clientId += String(random(0xffff), HEX); //Concatena un numero random hexadecimal

      //Conexión con el cliente y subscripción al topic para la recepción de mensajes del cliente
      if ( client.connect( clientId.c_str() ) ) {
        Serial.println("CONECTADO :D");
        client.subscribe("RALMT/#");
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

//Conecta al HOSTPOT configurado
void class_MQTT::setup_WiFi( void ){

  delay(10);
  Serial.println("CONFIGURANDO WiFi:");
  WiFi.begin(HOTSPOT_WIFI, HOTSPOT_PWD);

  //Bucle para saber si está conectado a Wifi
  while ( WiFi.status ( ) != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  
  Serial.print("WiFi configurado con la IP: " );
  Serial.println(WiFi.localIP());

}
