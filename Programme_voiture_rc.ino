#include <SoftwareSerial.h>
#include <Servo.h>

char command;

// Broches de commande du pont H
const int motor1Pin1 = 13;
const int motor1Pin2 = 12;
const int motor2Pin1 = 11;
const int motor2Pin2 = 9;

// Broches pour contrôler la vitesse des moteurs
const int enAPin = 10; 
const int enBPin = 7;

// Broche pour le servo moteur
const int servoPin = 8;
const int triggerPin = 4;
const int echoPin = 5;
const int buzzerPin = 6;

Servo servoMotor; 

long duree;
int distance;

void setup() {
  Serial.begin(9600); 
  servoMotor.attach(servoPin); 


  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enAPin, OUTPUT);
  pinMode(enBPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){ 
    command = Serial.read();

    Serial.println(command);
    if(command == 'F'){
      moveForward();
    }
    
    else if(command == 'B')
    {
      moveBackward();
    }
    else if(command == 'L')
    {
      moveAndTurnLeft();
    }
    else if(command == 'R')
    {
      moveAndTurnRight();
    }
    else if(command == 'C')
    {
      stopMotors();
    }
    else if(command == 'S')
    {
      backAndTurnRight();
    }
    else if(command == 'X')
    {
      backAndTurnLeft();
    }
  }

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duree = pulseIn(echoPin, HIGH);
  
  distance = duree * 0.034 / 2;


  if (distance > 0 && distance < 35) {
    digitalWrite(buzzerPin, HIGH);
    stopMotors();
    delay(500);
    moveForward();
    delay(170);
    stopMotors();
  } else {
    digitalWrite(buzzerPin, LOW);

  }

  delay(100);

}

void moveForward() {
  servoMotor.write(80);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enAPin, 255);
  analogWrite(enBPin, 255); 
}

void moveBackward() {
  servoMotor.write(80);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(enAPin, 255); 
  analogWrite(enBPin, 255);
}

void moveAndTurnLeft() {
  servoMotor.write(95); 
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enAPin, 255); 
  analogWrite(enBPin, 255); 
}

void backAndTurnLeft() {
  servoMotor.write(95); 
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(enAPin, 255); 
  analogWrite(enBPin, 255);
}

void backAndTurnRight() {
  servoMotor.write(65); 
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(enAPin, 255);
  analogWrite(enBPin, 255); 
}

void moveAndTurnRight() {
  servoMotor.write(65); 
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enAPin, 255);
  analogWrite(enBPin, 255); 
}

void stopMotors() {
  servoMotor.write(80);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enAPin, 0); 
  analogWrite(enBPin, 0); 
}
