#include <Ps3Controller.h>

//Right motor
int MOTOR_A1=1;
int MOTOR_A2=22;
//Left motor
int MOTOR_B1=3;
int MOTOR_B2=21;

//Right motor
int MOTOR2_A1=5;
int MOTOR2_A2=17;
//Left motor
int MOTOR2_B1=16;
int MOTOR2_B2=4;

//-------------- Velocidades

const int Vmin = 100;
const int Vavance = 200;
const int Vgiro = 100;
const int VavanceComb = 255;
const int VgiroComb = 70;
const int Vsprint = 255;

int limitarPWM(int pwm){
  if(pwm > 255){
    pwm = 255;
  }else if(pwm < -255){
    pwm = -255;
  }
}

void MoverMotores(int MA1, int MA2, int MB1, int MB2){
  analogWrite(MOTOR_A1, MA1);
  analogWrite(MOTOR_A2, MA2);
  analogWrite(MOTOR_B1, MA1);
  analogWrite(MOTOR_B2, MA2);

  analogWrite(MOTOR2_A1, MB1);
  analogWrite(MOTOR2_A2, MB2);
  analogWrite(MOTOR2_B1, MB1);
  analogWrite(MOTOR2_B2, MB2);
}

void notify(){
  int yAxisValue =(Ps3.data.analog.stick.ly);  //Left stick  - y axis - forward/backward car movement
  int xAxisValue =(Ps3.data.analog.stick.rx);  //Right stick - x axis - left/right car movement

  if(yAxisValue < 50 && yAxisValue > -50 && xAxisValue < 50 && xAxisValue > -50){
    //REPOSO
    MoverMotores(0,0,0,0);

  }else if(yAxisValue > 50 && xAxisValue < 50 && xAxisValue > -50){
    //ADELANTE
    MoverMotores(0,Vavance,0,Vavance);

  }else if(yAxisValue < -50 && xAxisValue < 50 && xAxisValue > -50){
    //ATRAS
    MoverMotores(Vavance,0,Vavance,0);

  }else if(yAxisValue < 50 && yAxisValue > -50 && xAxisValue > 50){
    //DERECHA
    MoverMotores(Vgiro,0,0,Vgiro);

  }else if(yAxisValue < 50 && yAxisValue > -50 && xAxisValue < -50){
    //IZQUIERDA
    MoverMotores(0,Vgiro,Vgiro,0);

  }else if(yAxisValue > 50 && xAxisValue > 50){
    //ADELANTE_DERECHA
    MoverMotores(0,VavanceComb,0,VgiroComb);
    
  }else if(yAxisValue > 50 && xAxisValue < -50){
    //ADELANTE_IZQUIERDA
    MoverMotores(0,VgiroComb,0,VavanceComb);

  }else if(yAxisValue < -50 && xAxisValue > 50){
    //ATRAS_DERECHA
    MoverMotores(VavanceComb,0,VgiroComb,0);

  }else if(yAxisValue < -50 && xAxisValue < -50){
    //ATRAS_IZQUIERDA
    MoverMotores(VgiroComb,0,VavanceComb,0);
    
  }
}

void onConnect(){
  Serial.println("Connected");
}

void setUpPinModes(){
  pinMode(MOTOR_A1,OUTPUT);
  pinMode(MOTOR_A2,OUTPUT);
  pinMode(MOTOR_B1,OUTPUT);
  pinMode(MOTOR_B2,OUTPUT);
  pinMode(MOTOR2_A1,OUTPUT);
  pinMode(MOTOR2_A2,OUTPUT);
  pinMode(MOTOR2_B1,OUTPUT);
  pinMode(MOTOR2_B2,OUTPUT);
}

void setup()
{
  setUpPinModes();
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin();
}

void loop(){

}