/*
 Actividad 5 - Brazo robótico con ESP32
 Lee 3 potenciómetros como sensores de posición y envía sus valores por UART/USB.
 También recibe comandos desde Python para mover 3 servos.
 Conexiones sugeridas:
 Potenciómetros: GPIO 34, 35, 32
 Servos: GPIO 18, 19, 21
 IMPORTANTE: alimentar servos con fuente externa de 5 V y unir GND con ESP32.
*/
#include <ESP32Servo.h>

Servo servoBase, servoBrazo, servoPinza;

const int POT_BASE = 34;
const int POT_BRAZO = 35;
const int POT_PINZA = 32;
const int SERVO_BASE = 18;
const int SERVO_BRAZO = 19;
const int SERVO_PINZA = 21;

int basePos=90, brazoPos=90, pinzaPos=45;
unsigned long ultimoEnvio=0;

int adcAGrados(int lectura){
  return map(constrain(lectura,0,4095),0,4095,0,180);
}

void moverServos(){
  servoBase.write(constrain(basePos,0,180));
  servoBrazo.write(constrain(brazoPos,0,180));
  servoPinza.write(constrain(pinzaPos,0,90));
}

void procesarComando(String dato){
  dato.trim();
  int a,b,c;
  if(sscanf(dato.c_str(),"MOVE,%d,%d,%d",&a,&b,&c)==3){
    basePos=a; brazoPos=b; pinzaPos=c;
    moverServos();
    Serial.println("ACK,MOVE");
  } else if(dato=="OPEN"){
    pinzaPos=90; moverServos(); Serial.println("ACK,OPEN");
  } else if(dato=="CLOSE"){
    pinzaPos=10; moverServos(); Serial.println("ACK,CLOSE");
  }
}

void setup(){
  Serial.begin(115200);
  servoBase.attach(SERVO_BASE);
  servoBrazo.attach(SERVO_BRAZO);
  servoPinza.attach(SERVO_PINZA);
  moverServos();
}

void loop(){
  if(Serial.available()){
    String dato=Serial.readStringUntil('\n');
    procesarComando(dato);
  }

  if(millis()-ultimoEnvio>=200){
    ultimoEnvio=millis();
    int s1=adcAGrados(analogRead(POT_BASE));
    int s2=adcAGrados(analogRead(POT_BRAZO));
    int s3=map(analogRead(POT_PINZA),0,4095,0,90);
    Serial.printf("SENS,%d,%d,%d\n",s1,s2,s3);
  }
}