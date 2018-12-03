#include <Servo.h>   // LibrerÃ­a para poder controlar el servo
#include <Stepper.h> // Libreria para motor a pasos

#define IN1  2 //motor primer pin
#define IN2  3
#define IN3  4
#define IN4  5 //motor ultimo pin

// Declaracion de variables para controlar los servos
Servo servoPinza;
Servo servoHombro;
Servo servoCodo;

//variable que se envia desde la interfaz
char input, giro;
byte coma = 0, cstep =0;
String grdPinza = "", grdHombro = "", grdCodo = "", pasos="" ;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); //motor
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);  //motor
  
  servoPinza.attach(8);    //Servo para pinza al pin 8
  servoHombro.attach(10);  //Servo para pinza al pin 10
  servoCodo.attach(9);     //Servo para pinza al pin 9
  
  //Llamamos a la secuencia de agarrar ficha   
  servoPinza.write(180);
  servoCodo.write(0);
  servoHombro.write(90); 
}

void loop() {
 
  if (Serial.available()) {
    input = Serial.read();
    
    if(input == ','){
      coma++;
    }else if(input == '.'){
      servoPinza.write(grdPinza.toInt());
      servoCodo.write(grdCodo.toInt());
      servoHombro.write(grdHombro.toInt()); 
      secuencia();
      grdPinza = "";
      grdCodo = "";
      grdHombro = "";
      pasos = "";
      coma = 0;
    }else{
      if(coma == 0){
        grdPinza += input; //12
      }else if(coma == 1){
        grdCodo += input; //32     
      }else if(coma == 2){ //40
        grdHombro += input; 
      }else if(coma == 3){
        if(input == 'i' || input == 'd')
          giro = input;  
        else
          pasos += input;
      }
     }
    }
  
}
void secuencia(){
  for(int i=0; i<pasos.toInt(); i++){
    if(giro == 'i')
      izquierda();
    else if(giro == 'd')
      derecha();
    delayMicroseconds(2500);
  }

}

void izquierda()
{
  //stepp
  switch(cstep)
  {
   case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   case 1:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
   break; 
   case 2:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 3:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 5:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
     case 6:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 7:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
  }
   
   cstep=cstep+1;
   if(cstep==8)
     {cstep=0;}
}

void derecha()
{
  //stepp
  switch(cstep)
  {
   case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 1:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   case 2:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 3:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 5:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
     case 6:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     
   break; 
   case 7:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
     
   break; 
   default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
  }
   cstep=cstep+1;
   if(cstep==8)
     {cstep=0;}
}
