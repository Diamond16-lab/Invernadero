//Incluimos la librería para controlar el motor paso a paso
#include <Stepper.h>

//Definimos los pines a los que está conectado el motor paso a paso
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

//Creamos un objeto de la clase Stepper
//28BYJ-48 tiene 2048 pasos por revolución
Stepper motor(2048, IN1, IN3, IN2, IN4);

void setup()
{
  //Configuramos los pines como salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  //Giramos el motor 2048 pasos en una dirección
  motor.setSpeed(10); // Velocidad en RPM
  motor.step(2048);
  delay(1000);

  //Giramos el motor 2048 pasos en la dirección opuesta
  motor.setSpeed(10);
  motor.step(-2048);
  delay(1000);
}
