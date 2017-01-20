char val;
const int ledPin = 13;

int stateNOW;
int stateBEFORE;
unsigned long previousMillis = 0;
const long beat = 350;
unsigned long STARTmom = 0;
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
  Serial.begin(9600); // Start serial communication at 9600 bps
}

void loop() {
  if (Serial.available()) { // If data is available to read,
    val = Serial.read(); // read it and store it in val
  }
  if (val == '1') {

    stateNOW = true;

    unsigned long currentMillis = millis();

    if (stateNOW == true) {
      //lo statoè alto?
      if (stateNOW != stateBEFORE) {
        //lo stato è alto perchè prima era basso?
        //in questo modo si capisce se lo stato si è alzato,
        //che equivale alla pressione del pulsante

        digitalWrite(ledPin, !ledState); //accendo il led
        ledState = !ledState;            //camio lo stato al led mettendolo alto
        STARTmom = millis();             //in STARTmom imagazzino l'istante di accensione del led
      }
    }

    stateBEFORE = stateNOW;
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
    digitalWrite(ledPin, ledState);
    //scrivi la variabile ledState al pin del led
    //quindi spegnilo o  accendilo

  }
  else if (val == '2') {

  }
  else if (val == '3') {

  }
  else if (val == '4') {

  }

  delay(10); // Wait 10 milliseconds for next reading

}

