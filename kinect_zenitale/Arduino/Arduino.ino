char valNOW;
char valNOW2;
char valNOW3;
char valNOW4;
char valNOW5;
char valNOW6;
char valNOW7;
char valNOW8;
char valNOW9;
char valNOW10;
char valNOW11;
char valNOW12;
char valNOW13;
char valNOW14;


char valBEFORE;
char valBEFORE2;
char valBEFORE3;
char valBEFORE4;
char valBEFORE5;
char valBEFORE6;
char valBEFORE7;
char valBEFORE8;
char valBEFORE9;
char valBEFORE10;
char valBEFORE11;
char valBEFORE12;
char valBEFORE13;
char valBEFORE14;


int martello1 = 0;
int martello2 = 1;
int martello3 = 2;
int martello4 = 3;
int martello5 = 4;
int martello6 = 5;
int martello7 = 6;
int martello8 = 7;
int martello9 = 8;
int martello10 = 9;
int martello11 = 10;
int martello12 = 11;
int martello13 = 12;
int martello14 = 13;


const long beat = 400;

unsigned long previousMillis = 0;
unsigned long STARTmom = 0;
int ledState = LOW;

unsigned long previousMillis2 = 0;
unsigned long STARTmom2 = 0;
int ledState2 = LOW;

unsigned long previousMillis3 = 0;
unsigned long STARTmom3 = 0;
int ledState3 = LOW;

unsigned long previousMillis4 = 0;
unsigned long STARTmom4 = 0;
int ledState4 = LOW;

unsigned long previousMillis5 = 0;
unsigned long STARTmom5 = 0;
int ledState5 = LOW;

unsigned long previousMillis6 = 0;
unsigned long STARTmom6 = 0;
int ledState6 = LOW;

unsigned long previousMillis7 = 0;
unsigned long STARTmom7 = 0;
int ledState7 = LOW;

unsigned long previousMillis8 = 0;
unsigned long STARTmom8 = 0;
int ledState8 = LOW;

unsigned long previousMillis9 = 0;
unsigned long STARTmom9 = 0;
int ledState9 = LOW;

unsigned long previousMillis10 = 0;
unsigned long STARTmom10 = 0;
int ledState10 = LOW;

unsigned long previousMillis11 = 0;
unsigned long STARTmom11 = 0;
int ledState11 = LOW;

unsigned long previousMillis12 = 0;
unsigned long STARTmom12 = 0;
int ledState12 = LOW;

unsigned long previousMillis13 = 0;
unsigned long STARTmom13 = 0;
int ledState13 = LOW;

unsigned long previousMillis14 = 0;
unsigned long STARTmom14 = 0;
int ledState14 = LOW;

#include <SPI.h>
#include <gpio_MCP23S17.h>   // import library
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//primo pwm declare
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//secondo pwm declare
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
//declare adress multiplexer
gpio_MCP23S17 mart(10, 0x20); //instance (address A0,A1,A2 tied to +)


void setup() {
  //multiplexer begin
  mart.begin();//x.begin(1) will override automatic SPI initialization
  mart.gpioPinMode(OUTPUT);

  Serial.begin(9600); // Start serial communication at 9600 bps
  //pwm begin
  pwm.begin();
  pwm2.begin();

  pwm.setPWMFreq(100);  // This is the maximum PWM frequency
  pwm2.setPWMFreq(100);  // This is the maximum PWM frequency

  uint8_t twbrbackup = TWBR;
  TWBR = 12;
}

void loop() {
  //----------------------------MARTELLO 14-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW14 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis14 = millis();


  if (valNOW14 == 'p' && valNOW14 != valBEFORE14) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello14, ledState14);
    ledState14 = !ledState14;            //camio lo stato al led mettendolo alto
    STARTmom14 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE14 = valNOW14;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis14 - STARTmom14 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis14 = currentMillis14;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState14 == HIGH) {
      ledState14 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello14, ledState14);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo


  //----------------------------MARTELLO 13-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW13 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis13 = millis();


  if (valNOW13 == 'o' && valNOW13 != valBEFORE13) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello13, ledState13);
    ledState13 = !ledState13;            //camio lo stato al led mettendolo alto
    STARTmom13 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE13 = valNOW13;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis13 - STARTmom13 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis13 = currentMillis13;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState13 == HIGH) {
      ledState13 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello13, ledState13);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo



  //----------------------------MARTELLO 12-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW12 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis12 = millis();


  if (valNOW12 == 'n' && valNOW12 != valBEFORE12) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello12, ledState12);
    ledState12 = !ledState12;            //camio lo stato al led mettendolo alto
    STARTmom12 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE12 = valNOW12;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis12 - STARTmom12 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis12 = currentMillis12;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState12 == HIGH) {
      ledState12 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello12, ledState12);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo


  //----------------------------MARTELLO 11-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW11 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis11 = millis();


  if (valNOW11 == 'm' && valNOW11 != valBEFORE11) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello11, ledState11);
    ledState11 = !ledState11;            //camio lo stato al led mettendolo alto
    STARTmom11 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE11 = valNOW11;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis11 - STARTmom11 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis11 = currentMillis11;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState11 == HIGH) {
      ledState11 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello11, ledState11);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo

  //----------------------------MARTELLO 10-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW10 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis10 = millis();


  if (valNOW10 == 'l' && valNOW10 != valBEFORE10) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello10, ledState10);
    ledState10 = !ledState10;            //camio lo stato al led mettendolo alto
    STARTmom10 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE10 = valNOW10;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis10 - STARTmom10 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis10 = currentMillis10;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState10 == HIGH) {
      ledState10 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello10, ledState10);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo

  //----------------------------MARTELLO 9-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW9 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis9 = millis();


  if (valNOW9 == 'i' && valNOW9 != valBEFORE9) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello9, ledState9);
    ledState9 = !ledState9;            //camio lo stato al led mettendolo alto
    STARTmom9 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE9 = valNOW9;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis9 - STARTmom9 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis9 = currentMillis9;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState9 == HIGH) {
      ledState9 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello9, ledState9);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo

  //----------------------------MARTELLO 8-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW8 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis8 = millis();


  if (valNOW8 == 'h' && valNOW8 != valBEFORE8) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello8, ledState8);
    ledState8 = !ledState8;            //camio lo stato al led mettendolo alto
    STARTmom8 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE8 = valNOW8;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis8 - STARTmom8 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis8 = currentMillis8;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState8 == HIGH) {
      ledState8 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello8, ledState8);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo

  //----------------------------MARTELLO 7-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW7 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis7 = millis();


  if (valNOW7 == 'g' && valNOW7 != valBEFORE7) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello7, ledState7);
    ledState7 = !ledState7;            //camio lo stato al led mettendolo alto
    STARTmom7 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE7 = valNOW7;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis7 - STARTmom7 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis7 = currentMillis7;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState7 == HIGH) {
      ledState7 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello7, ledState7);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo

  //----------------------------MARTELLO 6-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW6 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis6 = millis();


  if (valNOW6 == 'f' && valNOW6 != valBEFORE6) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello6, ledState6);
    ledState6 = !ledState6;            //camio lo stato al led mettendolo alto
    STARTmom6 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE6 = valNOW6;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis6 - STARTmom6 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis6 = currentMillis6;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState6 == HIGH) {
      ledState6 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello6, ledState6);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo

  //----------------------------MARTELLO 5-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW5 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis5 = millis();


  if (valNOW5 == 'e' && valNOW5 != valBEFORE5) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello5, ledState5);
    ledState5 = !ledState5;            //camio lo stato al led mettendolo alto
    STARTmom5 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE5 = valNOW5;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis5 - STARTmom5 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis5 = currentMillis5;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState5 == HIGH) {
      ledState5 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello5, ledState5);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo

  //----------------------------MARTELLO 4-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW4 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis4 = millis();


  if (valNOW4 == 'd' && valNOW4 != valBEFORE4) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello4, ledState4);
    ledState4 = !ledState4;            //camio lo stato al led mettendolo alto
    STARTmom4 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE4 = valNOW4;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis4 - STARTmom4 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis4 = currentMillis4;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState4 == HIGH) {
      ledState4 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello4, ledState4);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo


  //----------------------------MARTELLO 3-----------------------------
  if (Serial.available()) { // If data is available to read,
    valNOW3 = Serial.read(); // read it and store it in val
  }

  unsigned long currentMillis3 = millis();


  if (valNOW3 == 'c' && valNOW3 != valBEFORE3) {
    //lo stato è alto?
    //lo stato è alto perchè prima era basso?
    //in questo modo si capisce se lo stato si è alzato
    //che equivale alla pressione del pulsante

    mart.gpioDigitalWrite(martello3, ledState3);
    ledState3 = !ledState3;            //camio lo stato al led mettendolo alto
    STARTmom3 = millis();             //in STARTmom imagazzino l'istante di accensione del le

    giallo();
  }

  valBEFORE3 = valNOW3;
  // lo "Stato di adesso" è ormai passato e quindi diventa lo "stato di prima"

  if (currentMillis3 - STARTmom3 >= beat) {
    //la diferenza tra il clock e l'istante di accensione
    //è magg/ugua al tempo in cui il led deve rimanere acceso?

    previousMillis3 = currentMillis3;
    // non lo so: è copiato dallo sketch che ho trovato

    if (ledState3 == HIGH) {
      ledState3 = LOW;
      //se lo stato del led è "acceso", cambialo in "spento"
    }
  }
  mart.gpioDigitalWrite(martello3, ledState3);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo


  //----------------------------MARTELLO 2-----------------------------
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

  //---------------------------MARTELLO 1------------------------

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

  //colore primo pwm
  pwm.setPWM(0, 0, 1043); //r
  pwm.setPWM(2, 0, 738); //g
  pwm.setPWM(1, 0, 2087); //b

  pwm.setPWM(3, 0, 1043); //r
  pwm.setPWM(4, 0, 738); //g
  pwm.setPWM(5, 0, 2087); //b

  pwm.setPWM(6, 0, 1043); //r
  pwm.setPWM(7, 0, 738); //g
  pwm.setPWM(8, 0, 2087); //b

  pwm.setPWM(9, 0, 1043); //r
  pwm.setPWM(10, 0, 738); //g
  pwm.setPWM(11, 0, 2087); //b

  pwm.setPWM(12, 0, 1043); //r
  pwm.setPWM(13, 0, 738); //g
  pwm.setPWM(14, 0, 2087); //b

  //colore secondo pwm
  pwm2.setPWM(0, 0, 1043); //r
  pwm2.setPWM(2, 0, 738); //g
  pwm2.setPWM(1, 0, 2087); //b

  pwm2.setPWM(3, 0, 1043); //r
  pwm2.setPWM(4, 0, 738); //g
  pwm2.setPWM(5, 0, 2087); //b

  pwm2.setPWM(6, 0, 1043); //r
  pwm2.setPWM(7, 0, 738); //g
  pwm2.setPWM(8, 0, 2087); //b

  pwm2.setPWM(9, 0, 1043); //r
  pwm2.setPWM(10, 0, 738); //g
  pwm2.setPWM(11, 0, 2087); //b

  pwm2.setPWM(12, 0, 1043); //r
  pwm2.setPWM(13, 0, 738); //g
  pwm2.setPWM(14, 0, 2087); //b
}

void arancio() {

  //colore primo pwm
  pwm.setPWM(0, 0, 4095); //r
  pwm.setPWM(2, 0, 750); //g
  pwm.setPWM(1, 0, 30); //b

  pwm.setPWM(3, 0, 4095); //r
  pwm.setPWM(4, 0, 750); //g
  pwm.setPWM(5, 0, 30); //b

  pwm.setPWM(6, 0, 4095); //r
  pwm.setPWM(7, 0, 750); //g
  pwm.setPWM(8, 0, 30); //b

  pwm.setPWM(9, 0, 4095); //r
  pwm.setPWM(10, 0, 750); //g
  pwm.setPWM(11, 0, 30); //b

  pwm.setPWM(12, 0, 4095); //r
  pwm.setPWM(13, 0, 750); //g
  pwm.setPWM(14, 0, 30); //b

  //colore secondo pwm
  pwm2.setPWM(0, 0, 4095); //r
  pwm2.setPWM(2, 0, 750); //g
  pwm2.setPWM(1, 0, 30); //b

  pwm2.setPWM(3, 0, 4095); //r
  pwm2.setPWM(4, 0, 750); //g
  pwm2.setPWM(5, 0, 30); //b

  pwm2.setPWM(6, 0, 4095); //r
  pwm2.setPWM(7, 0, 750); //g
  pwm2.setPWM(8, 0, 30); //b

  pwm2.setPWM(9, 0, 4095); //r
  pwm2.setPWM(10, 0, 750); //g
  pwm2.setPWM(11, 0, 30); //b

  pwm2.setPWM(12, 0, 4095); //r
  pwm2.setPWM(13, 0, 750); //g
  pwm2.setPWM(14, 0, 30); //b
}

void giallo() {

  //colore primo pwm
  pwm.setPWM(0, 0, 3886); //r
  pwm.setPWM(2, 0, 3083); //g
  pwm.setPWM(1, 0, 0); //b

  pwm.setPWM(3, 0, 3886); //r
  pwm.setPWM(4, 0, 3083); //g
  pwm.setPWM(5, 0, 0); //b

  pwm.setPWM(6, 0, 3886); //r
  pwm.setPWM(7, 0, 3083); //g
  pwm.setPWM(8, 0, 0); //b

  pwm.setPWM(9, 0, 3886); //r
  pwm.setPWM(10, 0, 3083); //g
  pwm.setPWM(11, 0, 0); //b

  pwm.setPWM(12, 0, 3886); //r
  pwm.setPWM(13, 0, 3083); //g
  pwm.setPWM(14, 0, 0); //b

  //colore secondo pwm
  pwm2.setPWM(0, 0, 3886); //r
  pwm2.setPWM(2, 0, 3083); //g
  pwm2.setPWM(1, 0, 0); //b

  pwm2.setPWM(3, 0, 3886); //r
  pwm2.setPWM(4, 0, 3083); //g
  pwm2.setPWM(5, 0, 0); //b

  pwm2.setPWM(6, 0, 3886); //r
  pwm2.setPWM(7, 0, 3083); //g
  pwm2.setPWM(8, 0, 0); //b

  pwm2.setPWM(9, 0, 3886); //r
  pwm2.setPWM(10, 0, 3083); //g
  pwm2.setPWM(11, 0, 0); //b

  pwm2.setPWM(12, 0, 3886); //r
  pwm2.setPWM(13, 0, 3083); //g
  pwm2.setPWM(14, 0, 0); //b

}
