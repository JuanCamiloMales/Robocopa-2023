#include <Ps3Controller.h>
#include <Arduino.h>

//Right motor
int PWM_A=23; 
int MOTOR_A1=22;
int MOTOR_A2=1;
//Left motor
int PWM_B=19;
int MOTOR_B1=21;
int MOTOR_B2=3;

void notify(){
  int yAxisValue =(Ps3.data.analog.stick.ly);  //Left stick  - y axis - forward/backward car movement
  int xAxisValue =(Ps3.data.analog.stick.rx);  //Right stick - x axis - left/right car movement
  
  int yValue = (yAxisValue + 1)*2;
  int xValue = (xAxisValue + 1)*2;

  if(yValue > 255){
    yValue = 255;
  }else if(yValue < -255){
    yValue = -255;
  }

  if(xValue > 255){
    xValue = 255;
  }else if(xValue < -255){
    xValue = -255;
  }

  Serial.print(yValue);
  Serial.print(",");
  Serial.println(xValue);

  if (yValue >= 100){

    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, yValue);
    analogWrite(MOTOR_B1, 0);
    analogWrite(MOTOR_B2, yValue);

  }else if (yValue <= -100){

    yValue = abs(yValue);
    analogWrite(MOTOR_A1, yValue);
    analogWrite(MOTOR_A2, 0);
    analogWrite(MOTOR_B1, yValue);
    analogWrite(MOTOR_B2, 0);

  }else{
    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, 0);
    analogWrite(MOTOR_B1, 0);
    analogWrite(MOTOR_B2, 0);
  }
}

void onConnect(){
  Serial.println("Connected!.");
}

void setUpPinModes(){
  pinMode(MOTOR_A1,OUTPUT);
  pinMode(MOTOR_A2,OUTPUT);
  pinMode(MOTOR_B1,OUTPUT);
  pinMode(MOTOR_B2,OUTPUT);

  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, 0);
}

void setup()
{
  setUpPinModes();
  Serial.begin(115200);
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin();
  Serial.println("Ready.");
}

void loop(){

}