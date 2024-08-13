#include <Servo.h>

// creating servo object for motor
Servo servo;

// initializing pin for servo motor
int servopin = 11;
// initiaizing pins connected to logic pins 
// i.e (In1,In2,In3,In4) of motor driver
#define m1 3
#define m2 5
#define m3 6
#define m4 9

// initializing echo and trig pin of ranging sensor
#define echopin 13
#define trigpin 12

// initializing movement and turning speed
int speed = 255;
int turn =  255;

void setup() {
  // put your setup code here, to run once:
  
  // initializing pin for servo
  servo.attach(servopin);

  // setting pins of the motor driver to output
    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(m3, OUTPUT);
    pinMode(m4, OUTPUT);

  // set trig pin to output, to send signal
    pinMode(trigpin, OUTPUT);

  // set echo pin to input, to record signal 
    pinMode(echopin, INPUT);

    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 
  // initializing distance of the echo signal 
  // and the duration of the signal
  long distance,duration;

  // first we will send a signal of 10 micro second with trig pin
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  // now we will store the total distance travelled by the echo signal
  duration = pulseIn(echopin, HIGH);

  // now we will find the distance from the object by following formula
  // v = d / t
  // d = v * t
  // here v is the speed of sound in air (in cm/s)
  distance = (duration / 2) / 29.1 ;  // here distance is in centimeter (cm)
  //
  //servo.write(90);

  if (distance > 25)
  {
    forward();
    //digitalWrite(m1, HIGH);
    //digitalWrite(m3, HIGH);
  }

  else if ( (distance < 25) && (distance >= 0) )
  {
    stop();
    delay(200);

    reverse();
    delay(300);

    stop();
    delay(200);

    for (int pos = 90; pos >= 0; pos--)
    {
      servo.write(pos);
      delay(3);
    }

    for (int pos = 0; pos <= 90; pos++)
    {
      servo.write(pos);
      delay(3);
    }

    for (int pos = 90; pos <= 180; pos++)
    {
      servo.write(pos);
      delay(3);
    }

    for (int pos = 180; pos >= 90; pos--)
    {
      servo.write(pos);
      delay(3);
    }
    

    //left();
    digitalWrite(m1, LOW);
    analogWrite(m2, 255);
    analogWrite(m3, 255);
    digitalWrite(m4, LOW);
    delay(400);
  }  

}


void stop()
{
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}

// initiaizing function for forward movement
void forward()
{
  analogWrite(m1, 210);
  digitalWrite(m2, LOW);
  analogWrite(m3, 210);
  digitalWrite(m4, LOW);
}

// initiaizing function for reverse movement
void reverse()
{
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}

// initiaizing function for left turn
void left()
{
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}
