//
//void start()
//{
//  
//}
//void control() //PID control
//{
//  
//}
//void floodFill() //navigation
//{
//  
//}


void forward_accelerate()
{
  digitalWrite(m1Enable, HIGH); //m1 is left motor, m2 is right motor
  digitalWrite(m2Enable, HIGH);
  analogWrite(m1Logic1, LOW);
  analogWrite(m2Logic1, LOW); 
  for(int i = 0; i <= 255; ++i)
  {
    analogWrite(m1Logic2, i);
    analogWrite(m2Logic2, i);
  }
  
}
//void left()
//{
//  digitalWrite(m1Enable, LOW);
//  digitalWrite(m2Enable, HIGH);
//  digitalWrite(m2Logic1, HIGH);
//  digitalWrite(m2Logic2, LOW);
//}
//
//void left_accelerate()
//{
//  
//}
//
//void right()
//{
//  digitalWrite(m1Enable, HIGH);
//  digitalWrite(m2Enable, LOW);
//  digitalWrite(m1Logic1, HIGH);
//  digitalWrite(m1Logic2, LOW);
//}
//
//void left_accelerate()
//{
//  
//}

void halt()
{
  digitalWrite(m1Enable, LOW);
  digitalWrite(m2Enable, LOW);
}

int m1Enable = 7;
int m1Logic1 = 6;
int m1Logic2 = 5;
int m2Enable = 4;
int m2Logic1 = 11;
int m2Logic2 = 10;
//int leftSensor = ;
int middleSensor = ;
//int rightSensor = ;
//int encoder = ;


void setup()
{
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
  
}

void loop() {


}
