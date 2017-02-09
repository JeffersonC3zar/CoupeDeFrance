/**
 *    \file caraterisationVitesseMoteur.ino
 *    \brief asservissement vitesse
 *
 *    \author Arthur Duytschaever et Nicolas Sobczak
 *    \date Février 2017
 */
//_______________________________________________________________________________________________________
/* ======================================================================================================
 *      Include
 * ======================================================================================================
 */
#include <Arduino.h>
#include <SimpleTimer.h>           // http://arduino.cc/playground/Code/SimpleTimer


/* ======================================================================================================
 *      Variables globales
 * ======================================================================================================
 */

#define _DEBUG true
#define encoder0PinA_L 13   //encodeur gauche A
#define encoder0PinB_L 12   //encodeur gauche B
#define encoder0PinA_R 11   //encodeur droit A
#define encoder0PinB_R 10   //encodeur droit B

#define MotorR 3 // Attention sur Due PWM ou Pwm sont des keyword -> donc ne pas les utiliser pour des nom de variable
#define MotorL 6
#define IN1MotorL 22
#define IN2MotorL 23
#define IN1MotorR 52
#define IN2MotorR 53

SimpleTimer timer;                 // Timer pour échantillonnage
unsigned int tick_codeuse_R = 0;   // Compteur de tick de la codeuse
unsigned int tick_codeuse_L = 0;   // Compteur de tick de la codeuse
unsigned int tick_codeuse_moyenne = 0;   // Compteur de tick de la codeuse
int cmd = 0;                       // Commande du moteur

const int frequence_echantillonnage = 25;  // Fréquence du pid
const int tick_par_tour_codeuse = 2500;      // Nombre de tick codeuse par tour de roue codeuse
const int tick_par_tour_non_codeuse = 3836;      // Nombre de tick codeuse par tour de roue non codeuse
const float rapport_roueCodeuse_roueNonCodeuse = (52.28)/(80.22);


float consigne_moteur_nombre_tours_par_seconde = 7.0;  //  Nombre de tours de roue par seconde

float erreur_precedente = consigne_moteur_nombre_tours_par_seconde;
float somme_erreur = 0;   // Somme des erreurs pour l'intégrateur
float kp = 0;           // Coefficient proportionnel
float ki = 0;           // Coefficient intégrateur
float kd = 0;           // Coefficient dérivateur

int i; //Arthur pwm
unsigned long duration;


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
        Serial.begin(115200);     // Initialisation port COM
        pinMode(MotorR,OUTPUT);
        pinMode(MotorL,OUTPUT);
        pinMode(IN1MotorR,OUTPUT);
        pinMode(IN2MotorR,OUTPUT);
        pinMode(IN1MotorL,OUTPUT);
        pinMode(IN2MotorL,OUTPUT);

        pinMode(encoder0PinA_L, INPUT);
        pinMode(encoder0PinB_L, INPUT);
        pinMode(encoder0PinA_R, INPUT);
        pinMode(encoder0PinB_R, INPUT);

        //Moteur droit
        digitalWrite(IN1MotorR, HIGH);
        digitalWrite(IN2MotorR, LOW);
        //Moteur gauche
        digitalWrite(IN1MotorL, HIGH);
        digitalWrite(IN2MotorL, LOW);

        //attachInterrupt(encoder0PinA_R, compteur_tick_R, CHANGE);    // Interruption sur tick de la codeuse (interruption 0 = pin2 arduino mega)
        attachInterrupt(encoder0PinA_L, compteur_tick_L, CHANGE); // Interruption sur tick de la codeuse (interruption 0 = pin2 arduino mega)
        timer.setInterval(1000/frequence_echantillonnage, asservissement); // Interruption pour calcul du PID et asservissement

        i = 255;

        delay(5000);              // Pause de 5 sec pour laisser le temps au moteur de s'arréter si celui-ci est en marche
}


/**
 * \fn void loop()
 * \brief fonction loop d'arduino
 */
void loop(){
        timer.run();
        delay(10);
}


/**
 * \fn void compteur_tick_R()
 * \brief Interruption sur tick de la codeuse right
 */
void compteur_tick_R(){
        tick_codeuse_R++; // On incrémente le nombre de tick de la codeuse
}


/**
 * \fn void compteur_tick_L()
 * \brief Interruption sur tick de la codeuse right
 */
void compteur_tick_L(){
        tick_codeuse_L++; // On incrémente le nombre de tick de la codeuse

        /*Calcul du nombre de ticks dans un certain temps (pulseIn)*/
        //Peut poser pb parce qu'on est dans une interruption et on veut mesurer la durée de l'interruption
        duration += pulseIn(encoder0PinA_L, HIGH); // in microsecond
        // duration = duration/2500 // durée / 2500tick = nb de tours/microsecond
}


/**
 * \fn asservissement()
 * \brief Interruption pour calcul du PID
 */
void asservissement()
{
        // Réinitialisation du nombre de tick de la codeuse
        tick_codeuse_R = 0;
        tick_codeuse_L = 0;
        duration = 0;


        //===============================================
        // Calcul des erreurs
        // int frequence_codeuse = frequence_echantillonnage*tick;
        // float nb_tour_par_sec = (float)frequence_codeuse/(float)tick_par_tour_non_codeuse/rapport_roueCodeuse_roueNonCodeuse;
        // float erreur = consigne_moteur_nombre_tours_par_seconde - nb_tour_par_sec;
        // somme_erreur += erreur;
        // float delta_erreur = erreur-erreur_precedente;
        // erreur_precedente = erreur;

        // PID : calcul de la commande
        // cmd = kp*erreur + ki*somme_erreur + kd*delta_erreur;
        //===============================================

        // Normalisation et contrôle du moteur
        //  if(cmd < 0) cmd=255;
        //  else if(cmd > 255) cmd = 0;
        //  analogWrite(MotorR, (-1)*(cmd-255));
        //  analogWrite(MotorL, (-1)*(cmd-255));

        //analogWrite(MotorR, i);
        analogWrite(MotorL, i);
        // i = i-2;
        if (i < 0) {
                i=0;
                //Moteur droit
                digitalWrite(IN1MotorR, LOW);
                digitalWrite(IN2MotorR, LOW);
                //Moteur gauche
                digitalWrite(IN1MotorL, LOW);
                digitalWrite(IN2MotorL, LOW);
        }

        // DEBUG
        if(_DEBUG)
        {
                //Serial.print("\t pwm :\t");
                // Serial.println(i);

                //Serial.print("\t tick_codeuse_moyenne  :\t");
                //Serial.println(tick_codeuse_moyenne, 8);

                //Serial.print("\t nb_tour_par_sec : \t");
                // Serial.println(nb_tour_par_sec, 8);

                Serial.print("\t tick_codeuse_L : \t");
                Serial.println(tick_codeuse_L);

                Serial.print("\t duration : \t");
                Serial.println(duration);
        }

        delay(100);

}
