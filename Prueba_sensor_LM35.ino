//Librerias

#include <LiquidCrystal.h>
#include <Servo.h>


//Variables para pines digitales y analogicos
const int  pot = A2;
const int sensorPin = A1;
const int fotoresistenciaPin = A0;
// Variables de calibración

//Sensor LM35 
float lm35Calibracion = -15;  // Ajuste para el sensor LM35 (en grados Celsius)

//Fotoresistencia
int fotoresistenciaCalibracion = -2;  // Ajuste para la fotoresistencia
double luz;

//Display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



void setup()
{
  //inicializar objetos
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop()
{
  // Lectura del sensor LM35
  
  int lm35Value = analogRead(sensorPin);
  float millivolts = (lm35Value / 1023.0) * 5000;
  float celsius = (millivolts / 10) + lm35Calibracion;  // Aplicar la calibración
  Serial.print("Temperatura: ");
  Serial.print(celsius);
  Serial.println(" C");

  // Lectura de la fotoresistencia
  
  int fotoresistenciaValue = analogRead(fotoresistenciaPin);
  luz = (double)(fotoresistenciaValue /9.74)-fotoresistenciaCalibracion; //doble calibracion
  Serial.print("Valor de la fotoresistencia: ");
  Serial.println(luz);

  
  //Potenciometro----------
  int potenciometro = analogRead(pot);
  float voltaje = potenciometro * (5.0 / 1023.0);
  Serial.print("voltaje:   \n" );
  //-----------------------

// Actualizar pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(celsius);
  lcd.print(" C ");
  
  lcd.setCursor(0, 1);
  lcd.print("Luz: ");
  lcd.print(luz);
  

  // Esperar un breve periodo de tiempo antes de repetir el ciclo
  delay(1000);
  

  
}
