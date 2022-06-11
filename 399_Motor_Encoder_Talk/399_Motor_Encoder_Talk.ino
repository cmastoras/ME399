// Simple LED blink

#include <Servo.h>
#define HWSERIAL Serial2

#define MAX_RX_MESSAGE 100



String s1 ;

Servo EndE1;
Servo EndE2;
Servo BStop;
Servo BigMotor;

bool state = 0;
bool stet;
bool donePID;
int PIDError = 70;
const int led = LED_BUILTIN;
int counter = 0;
int error;
//float Kp = 0.02;
//float Ki = 0.12;
//float Kd = 0.000013;
float Kp = 0;
float Ki = 0;
float Kd = 0;
float deriv =0;


int middle = 109;

float intError = 0 ;
float newVel;
float newVelAbs;
float dt = 0.02;
int prevError = 1;
int velCap = 60;
boolean calState = false;
boolean shotReset = true;
int statFricAdd = 30;


void setup() {
  pinMode(led, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(4,INPUT);
  pinMode(18,INPUT);
  pinMode(19,INPUT);
  pinMode(0,INPUT);
  EndE1.attach(10,1000,2000);
  EndE2.attach(11,1000,2000);
  BStop.attach(12,1000,2000);
  BigMotor.attach(14,400,2200);
  BigMotor.write(0);
  digitalWrite(23,HIGH);
  HWSERIAL.begin(230400,SERIAL_8N1);
  HWSERIAL.write('b'); 
  HWSERIAL.write('\n');
  digitalWrite(led,HIGH);
  analogWrite(22,110);
  //Serial.println("Calibrating encoder");
  while(calState != HIGH){
    calState = digitalRead(18);
  }
  analogWrite(22,0);
  HWSERIAL.write('b'); 
  HWSERIAL.write('\n');
  Serial.println("Encoder Calibrated");
  Serial.println("Testing Servos");
  for(int i = 0; i < 36; i++){  
    counter = (counter *3) % 180 ; 
    EndE1.write(counter);   
    EndE2.write(180 - counter);   
    delay(5);
  }
  
  for(int i = 0; i < 36; i++){
    counter = (counter +5) % 180 ; 
    BStop.write(counter);   
    delay(5);
  }
  //PID(goal);
  Serial.println("Servos Have been tested");
  Serial.println("ensuring bigmotor safety");
  //BigMotor.write(87);
  //while(shotReset != LOW){
  //      shotReset = digitalRead(0);
        //Serial.println("waiting");
        
  //    }
  shotReset = true;
  //BigMotor.write(0);
  //analogWrite(13,0);
  Serial.println("Done");
}

String getEncPos(){
    HWSERIAL.write('a'); 
    HWSERIAL.write('\n'); 

    //recieve the shit
    int incomingByte;
    //while( HWSERIAL.available() == 0){
    //  delay(1);
    //}
    //if (HWSERIAL.available() > 0) {
    //Serial.print("Reading now");
    String s1 = HWSERIAL.readStringUntil("\n");
      
      //incomingByte = HWSERIAL.read();
      
      
      //Serial.println(incomingByte, DEC);
      //HWSERIAL.print("UART received:");
      //HWSERIAL.println(incomingByte, DEC);
      //}
    //Serial.print("UART received: ");
    //Serial.println(s1);
    return s1;
}

void PID(int PIDGoal){
  donePID = false;
  
  shotReset = digitalRead(1);
  while(donePID == false){
    String pos = getEncPos();
    
    error = PIDGoal - pos.toInt(); 
    Serial.println(error);
    intError = intError + error*dt;
    deriv = (error-prevError)/dt;
    newVel = (Kp*error) + (Ki*intError) + (Kd * (deriv));
        //Serial.print(newVel);
        //Serial.print("\n");
        
    
    //Serial.println(deriv);
    //if(newVel < 0){
    //  digitalWrite(23,HIGH);
    //      newVel = newVel - statFricAdd;
    //}else{
    //      digitalWrite(23,LOW);
    //      newVel = newVel + statFricAdd;
    //  }
        //Serial.print("\n error:");
    
        //Serial.print("    ");
        
        //newVelAbs = (1 + statFricAdd/100) * abs(newVel);
    //newVelAbs = abs(newVel);
    //if(newVel > velCap){
    //      if(newVel > 0 ){
    //        newVel = velCap;
    //      }else{
    //        newVel = -1* velCap;
    //      }
    //    }
    newVel = -1* constrain(newVel,-100,100);
    newVel = map(newVel,-100,100,middle-velCap,middle+velCap);
    //analogWrite(22,newVelAbs);
    shotReset = digitalRead(1);
    if(shotReset == LOW){
      Serial.println("FUCK");
      newVel = 0;
      donePID = true;
      
      };
    BigMotor.write(newVel);
    //Serial.println(newVel);
    prevError = error;
    
    if(abs(error) < PIDError && abs(deriv) < 0.5){
      donePID = true;
      //Serial.println("FUCKKK YES");
      BigMotor.write(0);
    }
  }
     
}


void loop() {
  
  stet = digitalRead(4);
//  while(true){
//    digitalWrite(led,HIGH);
//    delay(200);
//    digitalWrite(led,LOW);
//    delay(200);
//  }
  
  if (stet == HIGH){
    delay(300);
    //Serial.print("THIS SHIT HIGH AS FUCK");
    digitalWrite(led, LOW);
    if(state == HIGH){
      state = false;
    }else{
      state = true;
    }
    //Serial.print(state);
  }else{
    delay(1);
    //Serial.print("lowwwww \n");
  }
  if (state == 1){
      HWSERIAL.write('b'); 
      HWSERIAL.write('\n'); 
      Serial.println("Doing a shoot");
      //Serial.println("if");
      counter = 70;
      EndE1.write(counter);   
      EndE2.write(180 - counter); 
      
        
      //PID(goal);
      BStop.write(250);
      delay(200);
      BigMotor.write(80);
      delay(80);
      //BigMotor.write(100);
      BigMotor.write(125);
      Serial.println("This shoot went:");
      BigMotor.write(0);
      Serial.println(getEncPos());
      delay(3000);
      
      //PID(0);
      delay(100);
      //BigMotor.write(100);
      shotReset = true;
      
      
      
      
      
      
     
      state = 0;
      BStop.write(0);
      counter = 0;
      EndE1.write(counter);   
      EndE2.write(180 - counter); 
      
      
      
  }else{
    analogWrite(22,0);
    digitalWrite(23,HIGH);
    //for(int i = middle-velCap; i < middle+velCap; i++){
    //  Serial.println(i);
    //  BigMotor.write(i);  
    //  delay(80);
    //}
    
    
  }
  
  
  digitalWrite(4,LOW);
 
}
