/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_ejemplo {             // Nombre de la clase.     
        
  public:                         // Variables públicas.
    char byte_recibido;           // Recibe los bytes provenientes del puerto serial.
    String trama_recibida;        // String donde se almacenan los bytes recibidos.
    uint8_t x;                    // Ejemplo variable sin signo de 8 bits.
    
  public:                         // Métodos públicos.
    void metodo_ejemplo1 ( void );  // [tipo de variable que retorna] + [nombre del método] + [(] + (parametros) +  [)] + [;]
    uint8_t metodo_ejemplo2 ( void );
    int16_t metodo_ejemplo3 ( void );
    char metodo_ejemplo4 ( void );
    void SerialEvent ( void );
    
};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void class_ejemplo::metodo_ejemplo1 ( void ){
  
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~Potencia de un número~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  int64_t z, x = 2, y = 8;  
  z = pow ( x, y );    // Potencia de un número: pow ( base, potencia );
  
}

uint8_t class_ejemplo::metodo_ejemplo2 ( void ){
  
  uint8_t i = 255;
  return i;  // Retorna un número sin signo de 8 bits.
  
}

int16_t class_ejemplo::metodo_ejemplo3 ( void ){
  
  int16_t i = 255;
  return i;  // Retorna un número entero de 16 bits.
  
}

char class_ejemplo::metodo_ejemplo4 ( void ){
  
  char a = 'a';
  return a;  // Retorna un caracter de 8 bits.
  
}

/*  Mientras existan datos en el buffer esta función va a invocarse en cada byte, 
 *  es decir si el mensaje "HOLA" llega al puerto serial, la función primero leerá la letra "H";
 *  para la letra "O", la función "Serial.available (  )" verificará si todavía existe información en el buffer
 *  posteriormente llamará de nuevo la función "SerialEvent" y leerá la letra O, y así sucesivamente hasta 
 *  que ya no existan caracteres en el buffer.
*/
void class_ejemplo::SerialEvent ( void ) {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Leer información del puerto serial~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  
  
  
}
