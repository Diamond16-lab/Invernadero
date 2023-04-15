#include <LiquidCrystal.h>
#include <Servo.h>
#include <Stepper.h>

Servo Servomotor;
// Definir pines
//-*****Ventilador*****
const int ventilador = 13;
//***********************

//-*****Fotoresistencia*****-
int fotoresistencia = 0;
double luz;
//***********************

//-*****Temperatura*****-
double temperatura;
const int sensorTemperatura;
//***********************

//-*****Polea*****-
const int stepsPerRevolution = 2038;
Stepper myStepper = Stepper(stepsPerRevolution, 38, 40, 39, 41);
const int vueltas = 6;//Cuantas vueltas necesita???
bool abierto;
//***********************

// Declaración de objetos
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo myservo;
const int inPin=0;

void setup() {
  // Inicializar objetos
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(ventilador, OUTPUT);
  Servomotor.attach(9);
  //pinMode(relevador1, OUTPUT);
  //pinMode(relevador2, OUTPUT);  
}

void loop() {
  // Leer valores del potenciómetro, sensor de temperatura y fotresistencia

  //Potenciometro----------
  
  int potenciometro = analogRead(A2);
  float voltaje = potenciometro * (5.0 / 1023.0);
  Serial.print("voltaje:   \n" );
  //-----------------------
  
  //Calculo De Temperatura A Centigrados

  
  //int value = analogRead(A1);
  //float sensorTemperatura = analogRead(A1) * 0.48875; // Convertir valor a grados Celsius
  //Serial.print(sensorTemperatura);
  //Serial.println(" C");
  
  int value = analogRead(A1);
  float millivolts = (value / 1023.0) * 5000;
  float celsius = (millivolts / 10)-12.5; 
  Serial.print(celsius);
  Serial.println(" C");
  delay(1000);
  

  //Fotoresistencia-----------  
  fotoresistencia = analogRead(A0);
  luz = (double)fotoresistencia /9.74;
  //----

  // Controlar servo en base a la temperatura

  if (celsius > 3000) {
    Servomotor.write(90); // Activar servo
    digitalWrite (ventilador,HIGH);
    if (!abierto){
      myStepper.setSpeed(vueltas);
      myStepper.step(stepsPerRevolution);
    }
    abierto = true;
    lcd.setCursor(11,1);
    lcd.print("Open ");
  } else {
    myservo.write(0); // Desactivar servo
    digitalWrite (ventilador, LOW);
     if (abierto){
      myStepper.setSpeed(vueltas);
      myStepper.step(-stepsPerRevolution);
    }
    abierto = false;
    lcd.setCursor(11,1);
    lcd.print("Close");
  }
// Actualizar pantalla
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(celsius);
  lcd.print(" C  ");
  
  lcd.setCursor(0, 1);
  lcd.print("Luz: ");
  lcd.print(luz);
  
  // Esperar un breve periodo de tiempo antes de repetir el ciclo
  delay(1000);
  
  Serial.println(analogRead(A0));
  Serial.println("\n");
  delay(100);
}
