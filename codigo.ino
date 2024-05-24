#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

//Pines
int bombaAgua = 8;
int sensorTemp = A0;
int boton = 10;

//bluetoth
int BluetoothTx = 12;
int BluetoothRx = 13;

//variables
int hum;
int estadoBoton;

//Objetos
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
SoftwareSerial bluetooth(BluetoothTx, BluetoothRx);

void setup() {
  //setup Pantalla
  lcd.begin(16, 2);

  //setup rele
  pinMode(bombaAgua, OUTPUT);

  //setup boton
  pinMode(boton, INPUT);

  //serial y bluetooth
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  //Inicializacion de Variables sensor
  Serial.print("Hola si entra ");
  int humedad = analogRead(sensorTemp); 
  estadoBoton = digitalRead(boton);
  String modulo = "";

  Serial.println(humedad);
  delay(1000);

  //Pantalla
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: " + String(humedad) + " °C");
  lcd.setCursor(0, 1);
  lcd.print("Humedad: " + String(humedad) + " %   ");

  if (bluetooth.available() >= 0) {
    modulo = bluetooth.readString();
  }
  Serial.println("este es el estado del modulo " + String(modulo));
delay(1000);
  if ( estadoBoton == LOW || modulo == "abrir") {  //Condicion para regar automaticamente
    Serial.println("Esta es la hum " + String(humedad));
    Serial.println(humedad);
    digitalWrite(bombaAgua, LOW);  //Prender bomba de agua

    lcd.setCursor(0, 0);
    lcd.print("**Regando*");  // Mostrar en la pantalla LCD
    lcd.setCursor(0, 1);
    lcd.print("******");
    delay(5000);  //Durante 5 segundos

  } else if(modulo == "cerrar"){
    digitalWrite(bombaAgua, HIGH);    //Apagar bomba de agua
    Serial.println("entro al segundo else if");
    Serial.println(humedad);
    lcd.setCursor(0, 0);
    lcd.print("**apa*");  // Mostrar en la pantalla LCD
    lcd.setCursor(0, 1);
    lcd.print("******");
    delay(1000);  //Durante un segundo
  }
  else if (humedad >= 870) {  //Si se presiona el botón
    digitalWrite(bombaAgua, LOW);    //Prender bomba de agua
    Serial.println("entro al primer else if");
    Serial.println(humedad);
    lcd.setCursor(0, 0);
    lcd.print("**Regando*");  // Mostrar en la pantalla LCD
    lcd.setCursor(0, 1);
    lcd.print("******");
    delay(1000);  //Durante un segundo

  } 
  else
   {  //Si ninguna de las condiciones anteriores...
   if(modulo == "abrir"){
    digitalWrite(bombaAgua, HIGH);  //Bomba apagada
   }
    Serial.println("entro al else ");
    Serial.println(humedad);
  }

  //Si no recibe informacion del sensor
  if ( humedad == 0) {
    lcd.setCursor(0, 0);
    lcd.print("**ERROR***");  // Mostrar en la pantalla LCD
    lcd.setCursor(0, 1);
    lcd.print("**NO SENSOR**");
    delay(1000);  //Actualizacion cada segundo
  }
}