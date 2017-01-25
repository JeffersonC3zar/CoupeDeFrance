#include <Wire.h>

#define _PIN_ 13
#define _SENDADRESS_ 5
#define _RECEIVEADRESS_ 8


//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
void ledOff()
{
  pinMode(_PIN_, OUTPUT);
  digitalWrite(_PIN_, LOW);  
}

void ledOn()
{
  pinMode(_PIN_, OUTPUT);
  digitalWrite(_PIN_, HIGH);
}


void ledControl(int order)
{
  if (order==0)
  {
    ledOff();
  }
  if (order==1)
  {
    ledOn();
  }
}
  

//_____________________________________________________________________________________________
// Fonction qui est exécutée lorsque des données sont envoyées par le Maître.
// Cette fonction est enregistrée comme un événement ("event" en anglais), voir la fonction setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // Lire tous les octets sauf le dernier
  {
    char c = Wire.read();     // lecture de l'octet/byte comme caractère
    Serial.print(c);          // afficher le caractère
  }
  int x = Wire.read();        // lecture de l'octet/byte ignoré comme un entier
  Serial.println(x);          // Afficher la valeur numérique
  ledControl(x);              // Allume ou éteint la led
}


void i2creceive(int adresse)
{
  Wire.begin(adresse);          // Joindre le Bus I2C avec adresse #4
  Wire.onReceive(receiveEvent); // enregistrer l'événement (lorsqu'une demande arrive)
  Serial.begin(9600);           // Démarrer une communication série
}


//_____________________________________________________________________________________________
void i2csend(int order, int adresse)
{
  Wire.begin(); // joindre le bus i2c (adresse est optionnelle pour un maître)
  Wire.beginTransmission(adresse); // Commencer transmission vers l'esclave  #4
  Wire.write("order: ");       // Envoi de 5 octets (5 bytes)
  Wire.write(order);             // envoi d'un byte/octet (valeur numérique)  
  Wire.endTransmission();        // fin transmission
}


//_____________________________________________________________________________________________
int changeOrder(int order)
{
  order++;
  if (order==2)
  {
    order = 0;
  }
  return order;
}


void changeMasterLed(byte state)
{
  i2csend(state, _SENDADRESS_);
}


//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
void setup()
{
}


int state = 0;

void loop()
{
  i2creceive(_RECEIVEADRESS_); 
  state = digitalRead(_PIN_);
  changeMasterLed(state);
  delay(500);
}


