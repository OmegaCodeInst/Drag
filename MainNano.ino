#include <AFMotor.h>
#include <util/delay.h>
#include <IRremote.h>

#define KEY1 0x86288A23  // вперед 
#define KEY11 0x20DF00FF
#define KEY2 0x169CDC1F // назад
#define KEY22 0x20DF807F
#define KEY3 0x8EEF4B83  // влево
#define KEY33 0x20DF40BF
#define KEY4 0x9E0A10FF  // вправо
#define KEY44 0x20DFC03F
#define KEY5 0x20DF22DD
#define KEY55 0xDE8D48A3
#define KEY6 0x20DF4EB1
#define KEY7 0x20DF8E71


int RECV_PIN = 2;
bool flag_AI=false;
int statusSens=0;

IRrecv irrecv(RECV_PIN);

decode_results results;

AF_DCMotor motorR(3, MOTOR34_64KHZ);
AF_DCMotor motorL(4, MOTOR34_64KHZ);
int key;

void Left()
{
  motorL.setSpeed(255);
  motorR.setSpeed(255);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  _delay_ms(250);
  motorL.run(FORWARD);
  motorR.run(BACKWARD);
}
void Right()
{
  motorL.setSpeed(255);
  motorR.setSpeed(255);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  _delay_ms(250);
  motorL.run(BACKWARD);
  motorR.run(FORWARD);
}

void setup() {
  Serial.begin(9600);
  pinMode(9, INPUT);
  irrecv.enableIRIn(); // Start the receiver
  motorL.setSpeed(255);
  motorR.setSpeed(210);
  motorL.run(RELEASE);
  motorR.run(RELEASE);

}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == KEY1||results.value == KEY11)
          {
            key=1;
          }
         else if (results.value == KEY2||results.value == KEY22)
         {
          key = 2;
         }
         else if (results.value == KEY3||results.value == KEY33)
  {
          key = 3;
  }
           else if (results.value == KEY4||results.value == KEY44)
           {
          key = 4;
           }
           else if (results.value == KEY5||results.value == KEY55)
           {
          key = 5;
           }
           else if (results.value == KEY6)
           {
          key = 6;
           }
           else if (results.value == KEY7)
           {
          key = 7;
           }
    if(results.value==0xFFFFFFFF){
      key=key;
    }
    //Serial.println(results.value, HEX);
    if(key==1){
  motorL.setSpeed(245);
  motorR.setSpeed(215);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  _delay_ms(250);
  motorL.run(FORWARD);
  motorR.run(FORWARD);
  }
if(key==2){
  motorL.setSpeed(245);
  motorR.setSpeed(215);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  _delay_ms(250);
  motorL.run(BACKWARD);
  motorR.run(BACKWARD);
}
if(key==3){
  Left();
}
if(key==4){
   Right();
}
if(key==5){
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}

if(key==7){
  Serial.println('M');
}
    irrecv.resume();// Receive the next value
  }
  else {
    statusSens=digitalRead(A0);
    if(key==6){
  if(statusSens==1) {
  motorL.setSpeed(255);
  motorR.setSpeed(210);
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  _delay_ms(250);
  motorL.run(FORWARD);
  motorR.run(FORWARD);
  _delay_ms(1000);
  }
  else if(statusSens==0) {
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);
    _delay_ms(750);
    Left();
    _delay_ms(750);
  }
}
  }
}
