char valNOW;
char valNOW2;

char valBEFORE;
char valBEFORE2;


int martello1 = 3;
int martello2 = 2;

unsigned long previousMillis = 0;
const long beat = 400;
unsigned long STARTmom = 0;
int ledState = LOW;

unsigned long previousMillis2 = 0;
unsigned long STARTmom2 = 0;
int ledState2 = LOW;

#include <SPI.h>
#include <gpio_MCP23S17.h>   // import library
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

gpio_MCP23S17 mart(10, 0x20); //instance (address A0,A1,A2 tied to +)


void setup() {

  mart.begin();//x.begin(1) will override automatic SPI initialization
  mart.gpioPinMode(OUTPUT);


  Serial.begin(9600); // Start serial communication at 9600 bps

  pwm.begin();
  pwm.setPWMFreq(100);  // This is the maximum PWM frequency
  uint8_t twbrbackup = TWBR;
  TWBR = 12;
}

void loop() {

  //--------------PROVA MARTELLO 2---------------
  if (Serial.available()) { // If data is available to read,
    valNOW2 = Serial.read(); // read it and store it in val


  }

  unsigned long currentMillis2 = millis();


  if (valNOW2 == 'b' && valNOW2 != valBEFORE2) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello2, ledState2);
    ledState2 = !ledState2;            //camio lo stato al led mettendolo alto
    STARTmom2 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    viola();
  }

  valBEFORE2 = valNOW2;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis2 - STARTmom2 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis2 = currentMillis2;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState2 == HIGH) {
      ledState2 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello2, ledState2);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo

  //-----martello1 ----

  if (Serial.available()) { // If data is available to read,
    valNOW = Serial.read(); // read it and store it in val

  }

  unsigned long currentMillis = millis();


  if (valNOW == 'a' && valNOW != valBEFORE) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello1, ledState);
    ledState = !ledState;            //camio lo stato al led mettendolo alto
    STARTmom = millis();             //in STARTmom imagazzino l'istante di accensione del led

    viola();
  }

  valBEFORE = valNOW;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis - STARTmom >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis = currentMillis;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState == HIGH) {
      ledState = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello1, ledState);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo

}

void viola() {
  pwm.setPWM(0, 0, 1043); //r
  pwm.setPWM(2, 0, 738); //g
  pwm.setPWM(1, 0, 2087); //b

  pwm.setPWM(3, 0, 1043); //r
  pwm.setPWM(4, 0, 738); //g
  pwm.setPWM(5, 0, 2087); //b
}

void arancio() {
  pwm.setPWM(0, 0, 4095); //r
  pwm.setPWM(2, 0, 750); //g
  pwm.setPWM(1, 0, 30); //b

  pwm.setPWM(3, 0, 4095); //r
  pwm.setPWM(4, 0, 750); //g
  pwm.setPWM(5, 0, 30); //b
}

void giallo() {
  pwm.setPWM(0, 0, 3886); //r
  pwm.setPWM(2, 0, 3083); //g
  pwm.setPWM(1, 0, 0); //b

  pwm.setPWM(3, 0, 3886); //r
  pwm.setPWM(4, 0, 3083); //g
  pwm.setPWM(5, 0, 0); //b
}
