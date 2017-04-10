/**
 *    \file CoupeDeFranceDetection.ino
 *    \brief code de la carte cateurs
 *    \author Arthur D.
 *    \date Mars 2017
 *  This version of code sends messages with only data from the IR sensors.
 *  During final testing, the ultrasonic sensors were found to be too inconsistent.
 */
//_______________________________________________________________________________________________________


/* ======================================================================================================
 *      Initialisation
 * ======================================================================================================
 */
#include <Arduino.h>
//Librairie OF Infra RED :
#include "SharpIR.h"
#include "i2cCommunication.h"

#define _SENSORSBOARD_SENDADRESS_ 11


#define _DEBUG_ false
#define OWN_STD_ID 01 //avant = 23
#define OWN_EXT_ID 1000
#define ULTRASONIC_EXT_ID 1002
#define IR_EXT_ID 1001


/* === IR pins === */
const int IRPinB = A6, IRPinL = A3, IRPinR = A2, IRPinFL = A1, IRPinFR = A0;
const int NUM_IR_SAMPLES = 25;
SharpIR sharpBT(IRPinFR, NUM_IR_SAMPLES, 93, 1080);
SharpIR sharpFT(IRPinFL, NUM_IR_SAMPLES, 93, 1080);
SharpIR sharpFBR(IRPinR, NUM_IR_SAMPLES, 93, 1080);
SharpIR sharpFBC(IRPinL, NUM_IR_SAMPLES, 93, 1080);
SharpIR sharpFBL(IRPinB, NUM_IR_SAMPLES, 93, 1080);
SharpIR infrared[] = {sharpBT, sharpFT, sharpFBR, sharpFBC, sharpFBL};
const int NUM_IR = 5; // Number of IR sensor

/* === pin for UltraSound === */
//Trig
int trigPin = 11;
//echo
const int echoPinR = 10, echoPinB2 = 9, echoPinB1 = 8, echoPinL = 7, echoPinFL = 6;
const int ultrasonic[] = {echoPinR, echoPinL, echoPinB1, echoPinB2}; //echoPinFL,
const int NUM_ULTRASONIC = 4; // Number of ultrasonic sensor
//Use Variable
//int durationFR, durationFL, durationR, durationL, durationB,
//      distanceCMFR, distanceCMFL, distanceCMR, distanceCML, distanceCMB;

/* === pin For MUX === */
int A=2;
int B=3;
int C=12;


/* ======================================================================================================
 *      Fonctions
 * ======================================================================================================
 */
/**
 * \fn void setup()
 * \brief fonction setup d'arduino
 */
void setup()
{
        // === Setup Ultrasonic ===
        pinMode(trigPin, OUTPUT); //trig
        pinMode(echoPinR, INPUT); //echo
        // === Setup MUX ===
        pinMode(A,OUTPUT);
        pinMode(B,OUTPUT);
        pinMode(C,OUTPUT);

        Serial.begin(9600);
}

/**
 * \fn void loop()
 * \brief fonction loop d'arduino : Takes readings (and sends via I2C)
 */
void loop() {
        int irValue[NUM_IR];
        int ultrasonicValue[NUM_ULTRASONIC];
        // long start = millis();

        for(int i = 0; i < NUM_IR; i++)
        {
                irValue[i] = getIRValue(infrared[i]);
                // conversion sur 2 octets de la valeur à envoyer
                byte bytesTab[2];
                intTo2Bytes(bytesTab, irValue[i]);
                i2csend3bytes(i, bytesTab[0], bytesTab[1], _SENSORSBOARD_SENDADRESS_);
                delay(100); //TODO: see if it's useful to have time to receive and update all value
        }
        for(int i = 0; i < NUM_ULTRASONIC; i++)
        {
                ultrasonicValue[i] = getUltrasonicValue(ultrasonic[i]);
                // conversion sur 2 octets de la valeur à envoyer
                byte bytesTab[2];
                intTo2Bytes(bytesTab, ultrasonicValue[i]);
                i2csend3bytes(i + NUM_IR, bytesTab[0], bytesTab[1], _SENSORSBOARD_SENDADRESS_);
                delay(100); //TODO: see if it's useful to have time to receive and update all value
        }

        if (_DEBUG_) {
                Serial.println("=== IR values ===");
                for(int i = 0; i < NUM_IR; i++)
                {
                        Serial.print("\tirValue = \t");
                        Serial.println(irValue[i]);
                }
                Serial.println("=== Ultrasonic values ===");
                for(int i = 0; i < NUM_ULTRASONIC; i++)
                {
                        Serial.print("\tUltrasonic value = \t");
                        Serial.println(ultrasonicValue[i]);
                }
        }

        delay(300);
}


int getIRValue(SharpIR sharpIR){
        return sharpIR.distance();
}


int getUltrasonicValue(int echoPin){
        int channel = 0;
        switch(echoPin) {
        case echoPinB2:
                channel = 0;
                break;
        case echoPinB1:
                channel = 1;
                break;
        case echoPinL:
                channel = 2;
                break;
        case echoPinFL:
                channel = 3;
                break;
        case echoPinR:
                channel = 4;
                break;
        default:
                break;
        }

        setChannel(channel);

        delay(10);
        //Take Data
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        //calculations made, but not necessary to use other variables
        //  duration = pulseIn(echoPin , HIGH);
        //
        //  distanceCM = durationFR/58.2;

        //Wait for maximum 15 ms, should be able to see about 2.5m from sensor
        return pulseIn(echoPin, HIGH, 15000)/58.2;
}

boolean setChannel(int channelNumber){
        //Set MUX
        switch(channelNumber) {
        case 0: //Back
                digitalWrite(A,LOW);
                digitalWrite(B,LOW);
                digitalWrite(C,LOW);
                break;
        case 1: //Left
                digitalWrite(A,HIGH);
                digitalWrite(B,LOW);
                digitalWrite(C,LOW);
                break;
        case 2: //Right
                digitalWrite(A,LOW);
                digitalWrite(B,HIGH);
                digitalWrite(C,LOW);
                break;
        case 3: //Front Left
                digitalWrite(A,HIGH);
                digitalWrite(B,HIGH);
                digitalWrite(C,LOW);
                break;
        case 4:  //Front Right
                digitalWrite(A,LOW);
                digitalWrite(B,LOW);
                digitalWrite(C,HIGH);
                break;
        default:
                break;
        }
}
