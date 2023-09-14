#include <Ps3Controller.h>

// //-------------- Pines de motores

// #define MOTOR_A1 22
// #define MOTOR_A2 1
// #define MOTOR_B1 21
// #define MOTOR_B2 3

// //-------------- Velocidades

// const int Vmin = 100;
// const int Vavance = 200;
// const int Vgiro = 100;
// const int Vsprint = 255;

// // ------------- Estados de movimiento

// #define REPOSO 0
// #define ADELANTE 1
// #define ATRAS 2
// #define DERECHA 3
// #define IZQUIERDA 4
// #define ADELANTE_DERECHA 5
// #define ADELANTE_IZQUIERDA 6
// #define ATRAS_DERECHA 7
// #define ATRAS_IZQUIERDA 8

// // ------------- PID

// #define KP 0
// #define KI 0
// #define KD 0

// // -------------- Velocidades motores

// int Vderecha = 0;
// int Vizquierda = 0;

// // -------------- Variables de estado
// int Estado = 0;
// boolean HabilitarMovimiento = true;
// int yValue = 0;
// int xValue = 0;

void onConnect(){
  Serial.println("Connected!.");
}

void notify(){

  boolean habilidarMovimiento = Ps3.event.button_down.square;
  int yAxisValue =(Ps3.data.analog.stick.ly) + 1;  //Left stick  - y axis - forward/backward car movement
  int xAxisValue =(Ps3.data.analog.stick.rx) + 1;  //Right stick - x axis - left/right car movement

  Serial.print("habilidarMovimiento: ");
  Serial.println(habilidarMovimiento);
  Serial.print("yAxisValue: ");
  Serial.println(yAxisValue);
  Serial.print("xAxisValue: ");
  Serial.println(xAxisValue);
}

void setup(){

  Serial.begin(115200);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin();
  
}

void loop(){
}




