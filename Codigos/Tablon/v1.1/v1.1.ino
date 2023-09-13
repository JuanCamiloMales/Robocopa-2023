#include <Ps3Controller.h>
#include <Arduino.h>

//-------------- Pines de motores

#define MOTOR_A1 22
#define MOTOR_A2 1
#define MOTOR_B1 21
#define MOTOR_B2 3

//-------------- Velocidades

const int Vmin = 100;
const int Vavance = 200;
const int Vgiro = 100;
const int Vsprint = 255;

// ------------- Estados de movimiento

#define REPOSO 0
#define ADELANTE 1
#define ATRAS 2
#define DERECHA 3
#define IZQUIERDA 4
#define ADELANTE_DERECHA 5
#define ADELANTE_IZQUIERDA 6
#define ATRAS_DERECHA 7
#define ATRAS_IZQUIERDA 8

// ------------- PID

#define KP 0
#define KI 0
#define KD 0

// -------------- Velocidades motores

int Vderecha = 0;
int Vizquierda = 0;

// -------------- Variables de estado
int Estado = 0;
boolean HabilitarMovimiento = false;
int yValue = 0;
int xValue = 0;


void setup(){

  InicializacionPines();
  Ps3.attach(notify);
  Ps3.begin();
  
  HabilitarMovimiento = false; //El movimiento del carro comienza deshabilitado
  Estado = 0;  //Inicializa en reposo
}

void loop(){
  
  if(HabilitarMovimiento == true){

    if(Estado == REPOSO){
      MoverMotores(0,0,0,0);

    }else if(Estado == ADELANTE){
      MoverMotores(0,Vavance,0,Vavance);

    }else if(Estado == ATRAS){
      MoverMotores(Vavance,0,Vavance,0);

    }else if(Estado == DERECHA){
      MoverMotores(0,Vgiro,Vgiro,0);

    }else if(Estado == IZQUIERDA){
      MoverMotores(Vavance,0,0,Vavance);

    }else if(Estado == ADELANTE_DERECHA){
      MoverMotores(0,Vavance,0,Vgiro);

    }else if(Estado == ADELANTE_IZQUIERDA){
      MoverMotores(0,Vgiro,0,Vavance);

    }else if(Estado == ATRAS_DERECHA){
      MoverMotores(Vgiro,0,Vavance,0);
      
    }else if(Estado == ATRAS_IZQUIERDA){
      MoverMotores(Vavance,0,Vgiro,0);

    }
  }
}

void notify(){
  boolean habilidarMovimiento = Ps3.event.button_down.square;
  int yAxisValue =(Ps3.data.analog.stick.ly) + 1;  //Left stick  - y axis - forward/backward car movement
  int xAxisValue =(Ps3.data.analog.stick.rx) + 1;  //Right stick - x axis - left/right car movement

  //Habilitar y deshabilitar movimiento carro
  if (habilidarMovimiento == true && HabilitarMovimiento == false){
    HabilitarMovimiento = true;
  }else if (habilidarMovimiento == true && HabilitarMovimiento == true){
    HabilitarMovimiento = false;
  }

  if(yAxisValue < 50 && yAxisValue > -50 && xAxisValue < 50 && xAxisValue > -50){
    Estado = REPOSO;
  }else if(yAxisValue > 50 && xAxisValue < 50 && xAxisValue > -50){
    Estado = ADELANTE;
  }else if(yAxisValue < -50 && xAxisValue < 50 && xAxisValue > -50){
    Estado = ATRAS;
  }else if(yAxisValue < 50 && yAxisValue > -50 && xAxisValue > 50){
    Estado = DERECHA;
  }else if(yAxisValue < 50 && yAxisValue > -50 && xAxisValue < -50){
    Estado = IZQUIERDA;
  }else if(yAxisValue > 50 && xAxisValue > 50){
    Estado = ADELANTE_DERECHA;
  }else if(yAxisValue > 50 && xAxisValue < -50){
    Estado = ADELANTE_IZQUIERDA;
  }else if(yAxisValue < -50 && xAxisValue > 50){
    Estado = ATRAS_DERECHA;
  }else if(yAxisValue < -50 && xAxisValue < -50){
    Estado = ATRAS_IZQUIERDA;
  }

  yValue = abs(yAxisValue);
  xValue = abs(xAxisValue);
}

void MoverMotores(int MA1, int MA2, int MB1, int MB2){
  analogWrite(MOTOR_A1, MA1);
  analogWrite(MOTOR_A2, MA2);
  analogWrite(MOTOR_B1, MB1);
  analogWrite(MOTOR_B2, MB2);
}

void InicializacionPines(){
  pinMode(MOTOR_A1,OUTPUT);
  pinMode(MOTOR_A2,OUTPUT);
  pinMode(MOTOR_B1,OUTPUT);
  pinMode(MOTOR_B2,OUTPUT);
}


