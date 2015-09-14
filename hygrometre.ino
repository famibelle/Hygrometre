//****************************************************
// Mesure analogique et digitale de l'humidité du sol 
// Avec le module Humidit� Sol 
//  TipTopboards.com
//  23 12 2013  demo_hsol
//****************************************************
// Brancher +V -> 5V et GND
// Sortie analogique du capteur -> A0 Arduino
// Sortie digitale du capteur -> pin 3 Arduino (avec seuil)

//On rajoute une LEd témoin sur pin 4

#include <VirtualWire.h>
int Nombre = 0;
char Message[VW_MAX_MESSAGE_LEN]; 

int PinAnalogiqueHumidite=0;       //Broche Analogique de mesure d'humidit�
int PinNumeriqueHumidite=2;        //Broche Num�rique mesure de l'humidit�
int PinLed=3;    //LED t�moin de seuilde  s�cheresse

int PinLEDStrip=9;

int hsol;  //Humidite su sol, mesure analogique
int secheresse;  //0 ou 1 si seuil atteint

void setup(){ // Initialisation 
    Serial.begin(9600);  //Connection s�rie � 9600 baud
    pinMode(PinAnalogiqueHumidite, INPUT);       //pin A0 en entr�e analogique
    pinMode(PinNumeriqueHumidite, INPUT);  //pin 3 en entr�e num�rique
    pinMode(PinLed, OUTPUT);   //LED t�moin
    pinMode(PinLEDStrip,OUTPUT); //LED Strip connecté au MOSFET

    vw_setup(2000); // Bits par seconde
}

void loop() { //boucle principale
    hsol = analogRead(PinAnalogiqueHumidite); // Lit la tension analogique
    secheresse = digitalRead(PinNumeriqueHumidite); 
    Serial.print("Humidite Sol");
    Serial.print("\t");
    Serial.print(hsol); // afficher la mesure
    Serial.print("\t");
    Serial.print("Secheresse");
    Serial.print("\t");
    Serial.print(secheresse);  //0 ou 1 si le seuil est d�pass�
    Serial.print("\n");
    if (secheresse==1) 
    {
      digitalWrite(PinLed, HIGH);   // LED allum�e
      digitalWrite(PinLEDStrip, HIGH);
    }
    else {
      digitalWrite(PinLed, LOW);   // LED off
      digitalWrite(PinLEDStrip, LOW);
    }

    analogWrite(PinLEDStrip, hsol);

    // Conversion du int en tableau de chars 
    itoa(hsol,Message,10);  // 10 car décimal
    //itoa(Nombre,Message,10); // 10 car décimal
    Nombre = Nombre +5;
    Serial.print("Envoie message\t");
    Serial.println(Message);
    vw_send((uint8_t *)Message, strlen(Message));
    vw_wait_tx(); // On attend la fin de la transmission
    delay(200);  // et on se repose un peu...
}
