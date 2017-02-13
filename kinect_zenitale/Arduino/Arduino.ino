
int martello1 = 11;
int martello2 = 12;
int martello3 = 24;
int martello4 = 25;
int martello5 = 26;
int martello6 = 27;
int martello7 = 7;
int martello8 = 8;
int martello9 = 9;
int martello10 = 14;
int martello11 = 19;
int martello12 = 46;
int martello13 = 48;
int martello14 = 10;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//primo pwm declare
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//secondo pwm declare
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

char cmdChar;

const int onTimeMs = 350; // The time the led should be on
const int timeoutCmdChar = 100; // The time the char should be off

// In this state the board waits
// for the user input
#define STATE_WAITING 0
// In this state the character was
// received (so the led is on)
#define STATE_RECEIVED 1
// In this state the board is waiting
// for the char to be absent
#define STATE_WAITABS 2

byte currState;
unsigned long recvTime;
unsigned long lastTimeCmdChar;

void setup() {

  pinMode(martello1, OUTPUT);
  pinMode(martello2, OUTPUT);
  pinMode(martello3, OUTPUT);
  pinMode(martello4, OUTPUT);
  pinMode(martello5, OUTPUT);
  pinMode(martello6, OUTPUT);
  pinMode(martello7, OUTPUT);
  pinMode(martello8, OUTPUT);
  pinMode(martello9, OUTPUT);
  pinMode(martello10, OUTPUT);
  pinMode(martello11, OUTPUT);
  pinMode(martello12, OUTPUT);
  pinMode(martello13, OUTPUT);
  pinMode(martello14, OUTPUT);

  Serial.begin(9600); // Start serial communication at 9600 bps
  
  //pwm begin
  pwm.begin();
  pwm2.begin();

  pwm.setPWMFreq(100);  // This is the maximum PWM frequency
  pwm2.setPWMFreq(100);  // This is the maximum PWM frequency

  //provare a cancellare
  uint8_t twbrbackup = TWBR;
  TWBR = 12;

  currState = STATE_WAITING;
}

void loop() {
  bool cmdCharReceived = false;
  
  while (Serial.available())
  {
      cmdCharReceived = true;
      lastTimeCmdChar = millis();
      cmdChar = Serial.read();
  }

  switch (currState)
  {
    case STATE_WAITING:
      if (cmdCharReceived)
      {
        if (cmdChar == 'x') {
          digitalWrite(martello1, HIGH);
          arancio();
        } else if (cmdChar == 'b') {
          digitalWrite(martello2, HIGH);
          viola();
        } else if (cmdChar == 'c') {
          digitalWrite(martello3, HIGH);
          giallo();
        }
        recvTime = millis();
        currState = STATE_RECEIVED;
      }
      break;
    case STATE_RECEIVED:
      if ((millis() - recvTime) > onTimeMs)
      {
        if (cmdChar == 'x') {
          digitalWrite(martello1, LOW);
        } else if (cmdChar == 'b') {
          digitalWrite(martello2, LOW);
        } else if (cmdChar == 'c') {
          digitalWrite(martello3, LOW);
        }
        currState = STATE_WAITABS;
      }
      break;
    case STATE_WAITABS:
      if ((millis() - lastTimeCmdChar) > timeoutCmdChar) {
        currState = STATE_WAITING;
        spenti();
      }
      break;
  }
}


void spenti() {
  pwm.setPWM(0, 0, 0); //r
  pwm.setPWM(2, 0, 0); //b
  pwm.setPWM(1, 0, 0); //g

  pwm.setPWM(3, 0, 0); //r
  pwm.setPWM(4, 0, 0); //b
  pwm.setPWM(5, 0, 0); //g

  pwm.setPWM(6, 0, 0); //r
  pwm.setPWM(7, 0, 0); //b
  pwm.setPWM(8, 0, 0); //g

  pwm.setPWM(9, 0, 0); //r
  pwm.setPWM(10, 0, 0); //g
  pwm.setPWM(11, 0, 0); //b

  pwm.setPWM(12, 0, 0); //g
  pwm.setPWM(13, 0, 0); //b
  pwm.setPWM(14, 0, 0); //r

  pwm2.setPWM(0, 0, 0); //r
  pwm2.setPWM(2, 0, 0); //b
  pwm2.setPWM(1, 0, 0); //g

  pwm2.setPWM(3, 0, 0); //r
  pwm2.setPWM(4, 0, 0); //b
  pwm2.setPWM(5, 0, 0); //g

  pwm2.setPWM(6, 0, 0); //r
  pwm2.setPWM(7, 0, 0); //b
  pwm2.setPWM(8, 0, 0); //g

  pwm2.setPWM(9, 0, 0); //g
  pwm2.setPWM(10, 0, 0); //b
  pwm2.setPWM(11, 0, 0); //r

  pwm2.setPWM(12, 0, 0); //g
  pwm2.setPWM(13, 0, 0); //b
  pwm2.setPWM(14, 0, 0); //r
}

void arancio() {
  pwm.setPWM(0, 0, 4095); //r
  pwm.setPWM(2, 0, 30); //b
  pwm.setPWM(1, 0, 750); //g

  pwm.setPWM(3, 0, 4095); //r
  pwm.setPWM(4, 0, 30); //b
  pwm.setPWM(5, 0, 750); //g

  pwm.setPWM(6, 0, 4095); //r
  pwm.setPWM(7, 0, 30); //b
  pwm.setPWM(8, 0, 750); //g

  pwm.setPWM(9, 0, 4095); //r
  pwm.setPWM(10, 0, 750); //g
  pwm.setPWM(11, 0, 30); //b

  pwm.setPWM(12, 0, 750); //g
  pwm.setPWM(13, 0, 30); //b
  pwm.setPWM(14, 0, 4095); //r

  pwm2.setPWM(0, 0, 4095); //r
  pwm2.setPWM(2, 0, 30); //b
  pwm2.setPWM(1, 0, 750); //g

  pwm2.setPWM(3, 0, 4095); //r
  pwm2.setPWM(4, 0, 30); //b
  pwm2.setPWM(5, 0, 750); //g

  pwm2.setPWM(6, 0, 4095); //r
  pwm2.setPWM(7, 0, 30); //b
  pwm2.setPWM(8, 0, 750); //g

  pwm2.setPWM(9, 0, 750); //g
  pwm2.setPWM(10, 0, 30); //b
  pwm2.setPWM(11, 0, 4095); //r

  pwm2.setPWM(12, 0, 750); //g
  pwm2.setPWM(13, 0, 30); //b
  pwm2.setPWM(14, 0, 4095); //r
}

void viola() {

  pwm.setPWM(0, 0, 1043); //r
  pwm.setPWM(2, 0, 2087); //b
  pwm.setPWM(1, 0, 738); //g

  pwm.setPWM(3, 0, 1043); //r
  pwm.setPWM(4, 0, 2087); //b
  pwm.setPWM(5, 0, 738); //g

  pwm.setPWM(6, 0, 1043); //r
  pwm.setPWM(7, 0, 2087); //b
  pwm.setPWM(8, 0, 738); //g

  pwm.setPWM(9, 0, 1043); //r
  pwm.setPWM(10, 0, 738); //g
  pwm.setPWM(11, 0, 2087); //b

  pwm.setPWM(12, 0, 738); //g
  pwm.setPWM(13, 0, 2087); //b
  pwm.setPWM(14, 0, 1043); //r

  pwm2.setPWM(0, 0, 1043); //r
  pwm2.setPWM(2, 0, 2087); //b
  pwm2.setPWM(1, 0, 738); //g

  pwm2.setPWM(3, 0, 1043); //r
  pwm2.setPWM(4, 0, 2087); //b
  pwm2.setPWM(5, 0, 738); //g

  pwm2.setPWM(6, 0, 1043); //r
  pwm2.setPWM(7, 0, 2087); //b
  pwm2.setPWM(8, 0, 738); //g

  pwm2.setPWM(9, 0, 738); //g
  pwm2.setPWM(10, 0, 2087); //b
  pwm2.setPWM(11, 0, 1043); //r

  pwm2.setPWM(12, 0, 738); //g
  pwm2.setPWM(13, 0, 2087); //b
  pwm2.setPWM(14, 0, 1043); //r

}


void giallo() {
  pwm.setPWM(0, 0, 3886); //r
  pwm.setPWM(2, 0, 0); //b
  pwm.setPWM(1, 0, 3083); //g

  pwm.setPWM(3, 0, 3886); //r
  pwm.setPWM(4, 0, 0); //b
  pwm.setPWM(5, 0, 3083); //g

  pwm.setPWM(6, 0, 3886); //r
  pwm.setPWM(7, 0, 0); //b
  pwm.setPWM(8, 0, 3083); //g

  pwm.setPWM(9, 0, 3886); //r
  pwm.setPWM(10, 0, 3083); //g
  pwm.setPWM(11, 0, 0); //b

  pwm.setPWM(12, 0, 3083); //g
  pwm.setPWM(13, 0, 0); //b
  pwm.setPWM(14, 0, 3886); //r

  pwm2.setPWM(0, 0, 3886); //r
  pwm2.setPWM(2, 0, 0); //b
  pwm2.setPWM(1, 0, 3083); //g

  pwm2.setPWM(3, 0, 3886); //r
  pwm2.setPWM(4, 0, 0); //b
  pwm2.setPWM(5, 0, 3083); //g

  pwm2.setPWM(6, 0, 3886); //r
  pwm2.setPWM(7, 0, 0); //b
  pwm2.setPWM(8, 0, 738); //g

  pwm2.setPWM(9, 0, 3083); //g
  pwm2.setPWM(10, 0, 2087); //b
  pwm2.setPWM(11, 0, 3886); //r

  pwm2.setPWM(12, 0, 3083); //g
  pwm2.setPWM(13, 0, 0); //b
  pwm2.setPWM(14, 0, 3886); //r

}
