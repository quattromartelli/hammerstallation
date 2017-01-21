char valNOW;
char valNOW2;

char valBEFORE;
char valBEFORE2;


int martello1 = 13;
int martello2 = 12;

unsigned long previousMillis = 0;
const long beat = 350;
unsigned long STARTmom = 0;
int ledState = LOW;

unsigned long previousMillis2 = 0;
unsigned long STARTmom2 = 0;
int ledState2 = LOW;

#include <MCP23S17.h>         // Here is the new class to make using the MCP23S17 easy.
MCP martellouno(7, 10);

void setup() {
  pinMode(martello1, OUTPUT); // Set pin as OUTPUT
  pinMode(martello2, OUTPUT); // Set pin as OUTPUT

  //digitalWrite(ledPin, HIGH);
  //digitalWrite(ledPin, LOW);

  Serial.begin(9600); // Start serial communication at 9600 bps
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

    digitalWrite(martello2, !ledState2); //accendo il led
    ledState2 = !ledState2;            //camio lo stato al led mettendolo alto
    STARTmom2 = millis();             //in STARTmom imagazzino l'istante di accensione del led
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
  digitalWrite(martello2, ledState2);
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

    digitalWrite(martello1, !ledState); //accendo il led
    ledState = !ledState;            //camio lo stato al led mettendolo alto
    STARTmom = millis();             //in STARTmom imagazzino l'istante di accensione del led
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
  digitalWrite(martello1, ledState);
  //scrivi la variabile ledState al pin del led
  //quindi spegnilo o  accendilo





}
