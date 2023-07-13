#include <LedControl.h>
#include <Ticker.h>

#define Din 4
#define CLK 2
#define CS 3
#define Sensor_Pin  14

void Lectura_De_Gas();
LedControl Matriz_De_Javier = LedControl(Din, CLK, CS, 1);
Ticker Sens_Gas(Lectura_De_Gas, 3000); 

const int Matriz_Altitud = 8; 
int Estado_Gas;
int Prop;


//Animaciones de la matriz LED
byte Anim_Fuego1[8] = {
B00011000,
B00111000,
B01111100,
B01111100,
B01111100,
B00111010,
B00010001,
B00010000
};


byte Anim_Fuego2[8] = {
B00110000,
B00111000,
B01111100,
B01111100,
B01111100,
B01011000,
B10001000,
B00001000
};


byte Anim_Copo_De_Nieve1 [8] = {
B01001001,
B00101010,
B00011100,
B01110111,
B00011100,
B00101010,
B01000001,
B00000000
};

byte Anim_Copo_De_Nieve2 [8] = {
B10011001,
B01011010,
B00111100,
B11100111,
B11100111,
B00111100,
B01011010,
B10011001
};

void setup() {

  Serial.begin(9600);
  Matriz_De_Javier.shutdown(0, false); 
  Matriz_De_Javier.setIntensity(0, 15); 
  Matriz_De_Javier.clearDisplay(0); 
  pinMode(Sensor_Pin, INPUT); 
  Sens_Gas.start();

}

void loop()

{

Sens_Gas.update();
  if (Prop > 30) {
    Alerta();
}
  else {

    for (int i = 0; i < Matriz_Altitud; i++) {
    Matriz_De_Javier.setColumn(0, i, Anim_Copo_De_Nieve1[i]);
    } 
    delay(300);   
    for (int i = 0; i < Matriz_Altitud; i++) {
    Matriz_De_Javier.setColumn(0, i, Anim_Copo_De_Nieve2[i]);
  } 
  
  delay(1000);
}
}

void Lectura_De_Gas(){

  int suma = 0;
  for(int j = 0; j < 5; j++){
  Estado_Gas = map(analogRead(Lectura_De_Gas),0,1023,0,100);
  suma = suma + Estado_Gas;
  delay(100);
  }

  Prop = suma/5;
  Serial.println(Estado_Gas);
}

void Alerta() {

  Matriz_De_Javier.clearDisplay(0);
for(int t = t; t<5; t++){
  for (int i = Matriz_Altitud; i > 0; i--) 
    Matriz_De_Javier.setColumn(0, i, Anim_Fuego1[i]);

  }
  delay(500);

  for (int i = Matriz_Altitud; i > 0; i--) {
    Matriz_De_Javier.setColumn(0, i, Anim_Fuego2[i]);

  }
  delay(500);
}
