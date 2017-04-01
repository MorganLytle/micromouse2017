

int m1Enable = 2;
int m1Logic1 = 3;
int m1Logic2 = 4;
int m2Enable = 1;
int m2Logic1 = 5;
int m2Logic2 = 6;
int leftSensor = A2;
int middleSensor = A1;
int rightSensor = A0;
int baseReadingWall = 40;//Callibrate
int baseReading = 40; //Callibrate
int encoder1 = ;//FIXME
int encoder2 = ;//FIXME
int motorStatus = 0; //0=halt/1=foward/2=left/3=right

void calibrate(){
 baseReadingWall = digitalRead(leftSensor);
 baseReading = digitalRead(middleSensor);
}
void start()
{
  int offset = 50;
  if(analogRead(middleSensor) > baseReading+offset)
  {
    forward();
  }
  else{
    halt();
  }
}
//void control() //PID control
//{
//  
//}
//void floodFill() //navigation
//{
//  
//}


void forward( )
{
  int i = 150;
  motorStatus = 1;
  digitalWrite(m1Enable, HIGH); //m1 is left motor, m2 is right motor
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m1Logic1, LOW);
  digitalWrite(m2Logic1, LOW); 
  analogWrite(m1Logic2, i);
  analogWrite(m2Logic2, i);
  }
  
}
void left()
{
  motorStatus = 2;
  digitalWrite(m1Enable, HIGH);
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m2Logic1, LOW);
  digitalWrite(m2Logic2, HIGH);
  digitalWrite(m1Logic1, HIGH);
  digitalWrite(m1Logic2, LOW);
}

void right()
{
  motorStatus = 3;
  digitalWrite(m1Enable, HIGH);
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m1Logic1, LOW);
  digitalWrite(m1Logic2, HIGH);
  digitalWrite(m2Logic1, HIGH);
  digitalWrite(m2Logic2, LOW);
  
}

//void uTurn()
//{
//  
//}


void halt()
{
  motorStatus = 0;
  digitalWrite(m1Enable, LOW);
  digitalWrite(m2Enable, LOW);
}




void setup()
{
  Serial.begin(9600);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);
  pinMode(m1Logic1, OUTPUT);
  pinMode(m1Logic2, OUTPUT);
  pinMode(m2Logic1, OUTPUT);
  pinMode(m2Logic2, OUTPUT);
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(encoder, INPUT);
  calibrate();
  
}

void loop() 
{
  //State machine
  //


}
