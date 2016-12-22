/**
 *    \file moteur.cpp
 *    \brief Code contrôle des moteurs du grand Robot. Ce programme permet d'initialiser et d'envoyer 4 PWM (2 PWM pour chaque moteur) au driver moteur
 *
 *Codé pour "Spark core"  www.spark.io
 *
 *Par : Clément LETELLIER
 *      Mars 2014
 *Modification: Nicolas SOBCZAK
 *              Octobre 2016
 */
//_______________________________________________________________________________________________________


/* ======================================================================================================
 *      Include
 * ======================================================================================================
 */
#include "odometrie.h"
#include "Arduino.h"
#include "moteur.h"


/* ======================================================================================================
 *      Define
 * ======================================================================================================
 */
#define IN1MoteurB0 52 // IN1 moteur Gauche 
#define IN2MoteurB0 53 // IN2 moteur Gauche 
#define IN1MoteurA0 22 // IN1 moteur Droite
#define IN2MoteurA0 23 // IN2 moteur Droite 
#define PWM_FREQ 20000 // in Hertz (SET YOUR FREQUENCY)

uint16_t TIM_ARR = (uint16_t)(24000000 / PWM_FREQ) - 1; // Don't change! Calc's period.


/* ======================================================================================================
 *      Class Moteur
 * ======================================================================================================
 */
/**
 * \fn Moteur::Moteur()  
 * \brief constructeur qui initialise le moteur lors de l'appelle
 */
Moteur::Moteur()
{
  m_vitesse_moteur=0;
}


//_______________________________________________________________________________________________________
/**
 * \fn void Moteur::initPWM()
 * \brief active le timer2 et 0 pour la PWM, active la PWM selon le moteur
 */
void Moteur::initPWM()
{
   pinMode(IN1MoteurB0,OUTPUT);
   pinMode(IN2MoteurB0,OUTPUT);
   pinMode(IN1MoteurA0,OUTPUT);
   pinMode(IN2MoteurA0,OUTPUT);
   pinMode(PMW_MOTEUR_A0 ,OUTPUT);
   pinMode(PMW_MOTEUR_B0 ,OUTPUT);
}


//_______________________________________________________________________________________________________
/**
 * \fn void Moteur::brake(int choix_moteur)
 * \brief
 * \param int choix_moteur
 */
void Moteur::brake(int choix_moteur)  // potentiellement inutile pour frein mettre les motor a 0
{
  if(choix_moteur == 1){
    /*m_vitesse_moteur=-100;
    m_vitesse_moteur=convertir_pourcentage_en_octet ();
    m_PWM_G[0]= m_vitesse_moteur;
    m_PWM_G[1]=255- m_vitesse_moteur;*/
    digitalWrite(IN1MoteurA0,LOW);
    digitalWrite(IN2MoteurA0,LOW);
    analogWrite(PMW_MOTEUR_A0,255-m_vitesse_moteur);
    //analogWrite(PMW_MOTEUR_A1,255-m_vitesse_moteur);
    }

   if(choix_moteur == 2){
     /*m_vitesse_moteur=-100;
     m_vitesse_moteur=convertir_pourcentage_en_octet ();
     m_PWM_D[0]= m_vitesse_moteur;
     m_PWM_D[1]=255- m_vitesse_moteur;*/
     digitalWrite(IN1MoteurB0,LOW);
     digitalWrite(IN2MoteurB0,LOW);
     analogWrite(PMW_MOTEUR_B0,255-m_vitesse_moteur);
     //analogWrite(PMW_MOTEUR_B1,255-m_vitesse_moteur);
    }
}


//_______________________________________________________________________________________________________
/**
 * \fn void Moteur::fonctionnement_moteur(double vitesseGauche, double vitesseDroit)
 * \brief gérer le moteur pour qu'il roule vers sa destination
 * \param double vitesseGauche
 * \param double vitesseDroit
 */
void Moteur::fonctionnement_moteur(double vitesseGauche, double vitesseDroit)
{
        //moteur gauche
        //if(vitesseGauche != 0){
            m_vitesse_moteur=  vitesseGauche;
            m_vitesse_moteur=convertir_pourcentage_en_octet ();
            //m_PWM_G[0]=m_PWM_G[1]=m_vitesse_moteur;
              if(m_vitesse_moteur>127){
                digitalWrite(IN1MoteurB0,HIGH);// voir si le sens OK
                digitalWrite(IN2MoteurB0,LOW);// voir si le sens OK
                analogWrite(PMW_MOTEUR_B0,255-m_vitesse_moteur);
                
              }
              else if(m_vitesse_moteur<127){
                digitalWrite(IN1MoteurB0,LOW);// voir si le sens OK
                digitalWrite(IN2MoteurB0,HIGH);// voir si le sens OK
                analogWrite(PMW_MOTEUR_B0,255-m_vitesse_moteur);
              }

            //analogWrite(PMW_MOTEUR_A0,m_vitesse_moteur);
            //analogWrite(PMW_MOTEUR_A1,m_vitesse_moteur);
              else if(m_vitesse_moteur == 127){
                brake(1);
              }

        //}
        /*else{
            brake(1);
         }*/

        //moteur droit
        //if(vitesseDroit != 0){
            m_vitesse_moteur= vitesseDroit;
            m_vitesse_moteur=convertir_pourcentage_en_octet ();
            //m_PWM_D[0]=m_PWM_D[1]=m_vitesse_moteur;
              if(m_vitesse_moteur>127){
                digitalWrite(IN1MoteurA0,HIGH);// voire si le sens OK
                digitalWrite(IN2MoteurA0,LOW);// voire si le sens OK
                analogWrite(PMW_MOTEUR_A0,255-m_vitesse_moteur);
              }
              else if(m_vitesse_moteur<127){
                digitalWrite(IN1MoteurB0,LOW);// voire si le sens OK
                digitalWrite(IN2MoteurB0,HIGH);// voire si le sens OK
                analogWrite(PMW_MOTEUR_A0,255-m_vitesse_moteur);
              }
            //analogWrite(PMW_MOTEUR_B0,m_vitesse_moteur);
            //analogWrite(PMW_MOTEUR_B1,m_vitesse_moteur);
            //digitalWrite(PMW_MOTEUR_B1,!digitalRead(keep_B));
              else if(m_vitesse_moteur == 127){
                brake(2);
              }
        //}
     
          //envoieData();
}


//_______________________________________________________________________________________________________
/**
 * \fn int Moteur::convertir_pourcentage_en_octet ()
 * \brief permet de convertir la vitesse exprimé en pourcentage (-100 à +100) en octet (de 0 à 255)
 * \return int vitesse
 */
int Moteur::convertir_pourcentage_en_octet ()
{
        int vitesse=0;
	//vitesse moteur positif (0 à 100%)
        if((m_vitesse_moteur > 0) && (m_vitesse_moteur <= 100	)){
		      vitesse=127+((m_vitesse_moteur*128)/100);

	}

        //vitesse moteur négatif (0 à -100%)
        if((m_vitesse_moteur <= 0) && (m_vitesse_moteur >= -100	)){
		      vitesse=((100+m_vitesse_moteur)*127)/100;

	}

	return vitesse;
}


//_______________________________________________________________________________________________________
/*void Moteur::envoieData(){

        Serial1.write(m_PWM_G[0]);
        Serial1.write(m_PWM_G[1]);
        Serial1.write(m_PWM_D[0]);
        Serial1.write(m_PWM_D[1]);

}*/


// User defined analogWrite() to gain control of PWM initialization
/*void Moteur::analogWrite(uint16_t pin, uint8_t value) {
  TIM_OCInitTypeDef TIM_OCInitStructure;

  if (pin >= TOTAL_PINS || PIN_MAP[pin].timer_peripheral == NULL) {
    return;
  }
  // SPI safety check
  if (SPI.isEnabled() == true && (pin == SCK || pin == MOSI || pin == MISO)) {
    return;
  }
  // I2C safety check
  if (Wire.isEnabled() == true && (pin == SCL || pin == SDA)) {
    return;
  }
  // Serial1 safety check
  if (Serial1.isEnabled() == true && (pin == RX || pin == TX)) {
    return;
  }
  if (PIN_MAP[pin].pin_mode != OUTPUT && PIN_MAP[pin].pin_mode != AF_OUTPUT_PUSHPULL) {
    return;
  }
  // Don't re-init PWM and cause a glitch if already setup, just update duty cycle and return.
  if (PIN_MAP[pin].pin_mode == AF_OUTPUT_PUSHPULL) {
    TIM_OCInitStructure.TIM_Pulse = (uint16_t)(value * (TIM_ARR + 1) / 255);
    if (PIN_MAP[pin].timer_ch == TIM_Channel_1) {
      PIN_MAP[pin].timer_peripheral-> CCR1 = TIM_OCInitStructure.TIM_Pulse;
    } else if (PIN_MAP[pin].timer_ch == TIM_Channel_2) {
      PIN_MAP[pin].timer_peripheral-> CCR2 = TIM_OCInitStructure.TIM_Pulse;
    } else if (PIN_MAP[pin].timer_ch == TIM_Channel_3) {
      PIN_MAP[pin].timer_peripheral-> CCR3 = TIM_OCInitStructure.TIM_Pulse;
    } else if (PIN_MAP[pin].timer_ch == TIM_Channel_4) {
      PIN_MAP[pin].timer_peripheral-> CCR4 = TIM_OCInitStructure.TIM_Pulse;
    }
    return;
  }

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  //PWM Frequency : PWM_FREQ (Hz)
  uint16_t TIM_Prescaler = (uint16_t)(SystemCoreClock / 24000000) - 1; //TIM Counter clock = 24MHz

  // TIM Channel Duty Cycle(%) = (TIM_CCR / TIM_ARR + 1) * 100
  uint16_t TIM_CCR = (uint16_t)(value * (TIM_ARR + 1) / 255);

  // AFIO clock enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  pinMode(pin, AF_OUTPUT_PUSHPULL);

  // TIM clock enable
  if (PIN_MAP[pin].timer_peripheral == TIM2)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  else if (PIN_MAP[pin].timer_peripheral == TIM3)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  else if (PIN_MAP[pin].timer_peripheral == TIM4)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  // Time base configuration
  TIM_TimeBaseStructure.TIM_Period = TIM_ARR;
  TIM_TimeBaseStructure.TIM_Prescaler = TIM_Prescaler;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(PIN_MAP[pin].timer_peripheral, & TIM_TimeBaseStructure);

  // PWM1 Mode configuration
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_Pulse = TIM_CCR;

  if (PIN_MAP[pin].timer_ch == TIM_Channel_1) {
    // PWM1 Mode configuration: Channel1
    TIM_OC1Init(PIN_MAP[pin].timer_peripheral, & TIM_OCInitStructure);
    TIM_OC1PreloadConfig(PIN_MAP[pin].timer_peripheral, TIM_OCPreload_Enable);
  } else if (PIN_MAP[pin].timer_ch == TIM_Channel_2) {
    // PWM1 Mode configuration: Channel2
    TIM_OC2Init(PIN_MAP[pin].timer_peripheral, & TIM_OCInitStructure);
    TIM_OC2PreloadConfig(PIN_MAP[pin].timer_peripheral, TIM_OCPreload_Enable);
  } else if (PIN_MAP[pin].timer_ch == TIM_Channel_3) {
    // PWM1 Mode configuration: Channel3
    TIM_OC3Init(PIN_MAP[pin].timer_peripheral, & TIM_OCInitStructure);
    TIM_OC3PreloadConfig(PIN_MAP[pin].timer_peripheral, TIM_OCPreload_Enable);
  } else if (PIN_MAP[pin].timer_ch == TIM_Channel_4) {
    // PWM1 Mode configuration: Channel4
    TIM_OC4Init(PIN_MAP[pin].timer_peripheral, & TIM_OCInitStructure);
    TIM_OC4PreloadConfig(PIN_MAP[pin].timer_peripheral, TIM_OCPreload_Enable);
  }

  TIM_ARRPreloadConfig(PIN_MAP[pin].timer_peripheral, ENABLE);

  // TIM enable counter
  TIM_Cmd(PIN_MAP[pin].timer_peripheral, ENABLE);
}*/

