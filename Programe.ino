// setting up the servo
#include <Servo.h>
Servo SirR;
Servo SirL;
int x = 0;
int y = 1;
int pos;
#define SirR_Start 180
#define SirR_End 90
#define SirL_Start 0
#define SirL_End 90

// setting Cytron dual channel Motor driver
#define Left_Motor 6 // Dir 1
#define MotorL_Speed 7 // PWM 1
#define Right_Motor 8 // Dir 2
#define MotorR_Speed 9 // PWM 2

// setting HC-SR04
#define trigPin 30
#define echoPin 31

// setting wings switches
#define Left_Switch 34 // left limit switch
#define Right_Switch 35 // right limit switch

//setting condition switch
#define cond_sw1 38
#define cond_sw2 39

//setting IR
#define Ir_L 36
#define Ir_R 37

int black = 0; //1
int white = 0; //0

void setup() {

  // Setting Motor outputs
  pinMode(Right_Motor, OUTPUT);
  pinMode(MotorR_Speed, OUTPUT);
  pinMode(Left_Motor, OUTPUT);
  pinMode(MotorL_Speed, OUTPUT);

  // Setting UltraSonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Setting Limiting switches
  pinMode(Right_Switch, INPUT); 
  pinMode(Left_Switch, INPUT);

  // Setting conditional switch
  pinMode(cond_sw1, INPUT_PULLUP);
  pinMode(cond_sw2, INPUT_PULLUP);
 
  // Starting the Duel
  delay(5200);

   // Setting servo pins and position
  SirL.attach(3);
  SirR.attach(5);
  SirR.write(SirR_End);
  SirL.write(SirL_End);

  delay(100);

  if(digitalRead(cond_sw1) == 1 && digitalRead(cond_sw2) == 1)
  {
    right_rev(255);
    delay(300);
    front(255);
  }

  else if(digitalRead(cond_sw1) == 1 && digitalRead(cond_sw2) == 0){
    left_rev(255);
    delay(300);
    front(255);
  }

  else if(digitalRead(cond_sw1) == 0 && digitalRead(cond_sw2) == 1)
  {
    front(255);
    delay(300);
  }
  delay(350);
  SirR.write(SirR_Start);
  SirL.write(SirL_Start);
  
}

void loop() {
  if(digitalRead(cond_sw1) == 0 && digitalRead(cond_sw2) == 0)
  {
    front(255);
  }
  else
  {
    if(digitalRead(Ir_L) == black && digitalRead(Ir_R) == black)
    {
      front(255);

      while(digitalRead(Left_Switch) == 1 && digitalRead(Right_Switch)== 1)
      {
        front(255);
        while(US(50) == 1)
        {
          front(255);
          if (US(50) == 0)
          {
            break;
          }
        }
      }
      
      while(digitalRead(Left_Switch) == 1)
      {
        left(255);
        while(US(50) == 1)
        {
          front(255);
        }
      } 
      while (digitalRead(Right_Switch)== 1) 
      {
        right(255);
        while(US(50) == 1)
        {
          front(255);
        }
      }
    }
    
    else if(digitalRead(Ir_L) == black && digitalRead(Ir_R) == white)
    {
      back(255);
      delay(450);
      left_rev(255);
      delay(250);
    }

    else if(digitalRead(Ir_L) == white && digitalRead(Ir_R) == black)
    {
      back(255);
      delay(450);
      right_rev(255);
      delay(250);
    }
    
    else 
    {
      back(255);
      delay(700);
      
       if(digitalRead(cond_sw1) == 1 && digitalRead(cond_sw2) == 1)
      {
        left_rev(255);
        delay(500);
      }
    
      else{
        right_rev(255);
        delay(500);
      }
    
     }
  }
}


void front(int spd) {
  // Moving forward
  digitalWrite(Right_Motor, HIGH);
  analogWrite(MotorR_Speed, spd);
  digitalWrite(Left_Motor, HIGH);
  analogWrite(MotorL_Speed, spd);
}

void back(int spd) {
  // Moving backward
  digitalWrite(Right_Motor, LOW);
  analogWrite(MotorR_Speed, spd);
}

void right_rev(int spd) {
  // Turning right, by the two wheels
  // right wheel moves backward and left wheel moves forward
  digitalWrite(Right_Motor, LOW);
  analogWrite(MotorR_Speed, spd);
  digitalWrite(Left_Motor, HIGH);
  analogWrite(MotorL_Speed, spd);
}

void right(int spd) {
  // Turning right, by only one wheels
  // right wheel freezes and left wheel moves forward
  analogWrite(MotorR_Speed, 0);
  digitalWrite(Left_Motor, HIGH);
  analogWrite(MotorL_Speed, spd);
}

void left_rev(int spd) {
  // Turning left, by the two wheels
  // left wheel moves backward and right wheel moves forward
  digitalWrite(Right_Motor, HIGH);
  analogWrite(MotorR_Speed, spd);
  digitalWrite(Left_Motor, LOW);
  analogWrite(MotorL_Speed, spd);
}

void left(int spd) {
  // Turning left, by only one wheels
  // left wheel freezes and right wheel moves forward
  digitalWrite(Right_Motor, HIGH);
  analogWrite(MotorR_Speed, spd);
  analogWrite(MotorL_Speed, 0);
}

void equi() {
  // equilibrium, no move
  // no need to setting high or low directions as no speed :)
  analogWrite(MotorR_Speed, 0);
  analogWrite(MotorL_Speed, 0);
}

int US(int x){
  long duration;
  int distance;


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (x >= distance) {
    return 1;
  } else {
    return 0;
  }
}
