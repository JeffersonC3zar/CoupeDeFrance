/**
 *    \file SensorsBoard.cpp
 *    \brief classe carte capteurs
 *
 *    \author Nicolas SOBCZAK
 *    \date Mars 2017
 */
//_______________________________________________________________________________________________________
/* ======================================================================================================
 *      Initialisation
 * ======================================================================================================
 */
#include "SensorsBoard.h"

int SensorsBoard::infraredSensorFrontBottomRightValue = 0;
int SensorsBoard::infraredSensorFrontBottomLeftValue = 0;
int SensorsBoard::infraredSensorFrontBottomCenterValue = 0;
int SensorsBoard::infraredSensorFrontTopValue = 0;
int SensorsBoard::infraredSensorBackValue = 0;
int SensorsBoard::ultrasonicFrontValue = 0;
int SensorsBoard::ultrasonicRightValue = 0;
int SensorsBoard::ultrasonicLeftValue = 0;
int SensorsBoard::ultrasonicBackValue = 0;


/* ======================================================================================================
 *      Constructor, getter, setter
 * ======================================================================================================
 */
SensorsBoard::SensorsBoard()
{
}

int SensorsBoard::getInfraredSensorFrontBottomRightValue()
{
        return SensorsBoard::infraredSensorFrontBottomRightValue;
}

int SensorsBoard::getInfraredSensorFrontBottomLeftValue()
{
        return SensorsBoard::infraredSensorFrontBottomLeftValue;
}

int SensorsBoard::getInfraredSensorFrontBottomCenterValue()
{
        return SensorsBoard::infraredSensorFrontBottomCenterValue;
}

int SensorsBoard::getInfraredSensorFrontTopValue()
{
        return SensorsBoard::infraredSensorFrontTopValue;
}

int SensorsBoard::getInfraredSensorBackValue()
{
        return SensorsBoard::infraredSensorBackValue;
}

int SensorsBoard::getUltrasonicFrontValue()
{
        return SensorsBoard::ultrasonicFrontValue;
}

int SensorsBoard::getUltrasonicRightValue()
{
        return SensorsBoard::ultrasonicRightValue;
}

int SensorsBoard::getUltrasonicLeftValue()
{
        return SensorsBoard::ultrasonicLeftValue;
}

int SensorsBoard::getUltrasonicBackValue()
{
        return SensorsBoard::ultrasonicBackValue;
}


void SensorsBoard::setInfraredSensorFrontBottomRightValue(int infraredSensorFrontBottomRightValue)
{
        SensorsBoard::infraredSensorFrontBottomRightValue = infraredSensorFrontBottomRightValue;
}

void SensorsBoard::setInfraredSensorFrontBottomLeftValue(int infraredSensorFrontBottomLeftValue)
{
        SensorsBoard::infraredSensorFrontBottomLeftValue = infraredSensorFrontBottomLeftValue;
}

void SensorsBoard::setInfraredSensorFrontBottomCenterValue(int infraredSensorFrontBottomCenterValue)
{
        SensorsBoard::infraredSensorFrontBottomCenterValue = infraredSensorFrontBottomCenterValue;
}

void SensorsBoard::setInfraredSensorFrontTopValue(int infraredSensorFrontTopValue)
{
        SensorsBoard::infraredSensorFrontTopValue = infraredSensorFrontTopValue;
}

void SensorsBoard::setInfraredSensorBackValue(int infraredSensorBackValue)
{
        SensorsBoard::infraredSensorBackValue = infraredSensorBackValue;
}

void SensorsBoard::setUltrasonicFrontValue(int ultrasonicFrontValue)
{
        SensorsBoard::ultrasonicFrontValue = ultrasonicFrontValue;
}

void SensorsBoard::setUltrasonicRightValue(int ultrasonicRightValue)
{
        SensorsBoard::ultrasonicRightValue = ultrasonicRightValue;
}

void SensorsBoard::setUltrasonicLeftValue(int ultrasonicLeftValue)
{
        SensorsBoard::ultrasonicLeftValue = ultrasonicLeftValue;
}

void SensorsBoard::setUltrasonicBackValue(int ultrasonicBackValue)
{
        SensorsBoard::ultrasonicBackValue = ultrasonicBackValue;
}


/* ======================================================================================================
 *      Methods
 * ======================================================================================================
 */

/**
 * \fn void receiveEvent(int howMany - fonction qui est exécutée lorsque des données sont envoyées par le Maître. Cette fonction est enregistrée comme un événement ("event" en anglais), voir la fonction setup()
 * \param int howMany
 */
void SensorsBoard::receiveEvent3bytes(int howMany)
{
        if (Wire.available() == 3)
        {
                //lecture de la variable
                byte var = Wire.read();
                //lecture des 2 octets suivants
                byte x = Wire.read();
                byte y = Wire.read();
                //reconstitution de la valeur
                byte bytesTab[2] = {x, y};
                int value = recoverIntFrom2Bytes(bytesTab);

                switch ( var )  // cf. les références des variables en haut du fichier
                {
                case 0:
                        if (_DEBUG_) Serial.println("variable recue : InfraredSensorBack");
                        SensorsBoard::setInfraredSensorBackValue(value);
                        break;
                case 1:
                        if (_DEBUG_) Serial.println("variable recue : InfraredSensorFrontTop");
                        SensorsBoard::setInfraredSensorFrontTopValue(value);
                        break;
                case 2:
                        if (_DEBUG_) Serial.println("variable recue : InfraredSensorFrontBottomRight");
                        SensorsBoard::setInfraredSensorFrontBottomRightValue(value);
                        break;
                case 3:
                        if (_DEBUG_) Serial.println("variable recue : InfraredSensorFrontBottomCenter");
                        SensorsBoard::setInfraredSensorFrontBottomCenterValue(value);
                        break;
                case 4:
                        if (_DEBUG_) Serial.println("variable recue : InfraredSensorFrontBottomLeft");
                        SensorsBoard::setInfraredSensorFrontBottomLeftValue(value);
                        break;
                case 5:
                        if (_DEBUG_) Serial.println("variable recue : UltrasonicRight");
                        SensorsBoard::setUltrasonicRightValue(value);
                        break;
                case 6:
                        if (_DEBUG_) Serial.println("variable recue : UltrasonicLeft");
                        SensorsBoard::setUltrasonicLeftValue(value);
                        break;
                case 7:
                        if (_DEBUG_) Serial.println("variable recue : UltrasonicFront (back1)");
                        SensorsBoard::setUltrasonicFrontValue(value);
                        break;
                case 8:
                        if (_DEBUG_) Serial.println("variable recue : UltrasonicBack (back2)");
                        SensorsBoard::setUltrasonicBackValue(value);
                        break;
                default:
                        if (_DEBUG_) Serial.println("variable recue inconnue");
                }

        }
        // else de debug
        else if (_DEBUG_)
        {
                Serial.println("Erreur : Pas 3 octets envoyes");
        }
}


/**
 * \fn void i2creceive3bytes
 * \param int adresse
 * \brief
 */
void SensorsBoard::i2creceive3bytes(int adresse)
{
        Wire.begin(adresse);
        Wire.onReceive(SensorsBoard::receiveEvent3bytes); // enregistrer l'événement (lorsqu'une demande arrive)
        Wire.endTransmission();
}


/**
 * \fn void SensorsBoard::update()
 * \brief reception + maj infos du module capteurs
 */
void SensorsBoard::updateAllSensorsValue()
{
        for (int i = 0; i < _NUMBER_OF_SENSORS_; i++)
        {
                SensorsBoard::i2creceive3bytes(_SENSORSBOARD_RECEIVEADRESS_);
        }
}


// === CHECK CYLINDER FUNCTIONS ===

bool SensorsBoard::checkForCylinderOnSensorFrontBottomLeft()
{
        if (SensorsBoard::getInfraredSensorFrontBottomLeftValue() < _CYLINDER_DISTANCE_) return true;
        else return false;
}

bool SensorsBoard::checkForCylinderOnSensorFrontBottomCenter()
{
        if (SensorsBoard::getInfraredSensorFrontBottomCenterValue() < _CYLINDER_DISTANCE_) return true;
        else return false;
}

bool SensorsBoard::checkForCylinderOnSensorFrontBottomRight()
{
        if (SensorsBoard::getInfraredSensorFrontBottomRightValue() < _CYLINDER_DISTANCE_) return true;
        else return false;
}

//return true if there is a cylinder
bool SensorsBoard::checkForCylinder()
{
        if (SensorsBoard::checkForCylinderOnSensorFrontBottomLeft() ||
            SensorsBoard::checkForCylinderOnSensorFrontBottomCenter()||
            SensorsBoard::checkForCylinderOnSensorFrontBottomRight())
                return true;
        return false;
}


// === CHECK BASE FUNCTIONS ===

bool SensorsBoard::checkForBaseOnSensorFrontBottomLeft()
{
        if (SensorsBoard::getInfraredSensorFrontBottomLeftValue() < _BASE_DISTANCE_) return true;
        else return false;
}

bool SensorsBoard::checkForBaseOnSensorFrontBottomCenter()
{
        if (SensorsBoard::getInfraredSensorFrontBottomCenterValue() < _BASE_DISTANCE_) return true;
        else return false;
}

bool SensorsBoard::checkForBaseOnSensorFrontBottomRight()
{
        if (SensorsBoard::getInfraredSensorFrontBottomRightValue() < _BASE_DISTANCE_) return true;
        else return false;
}

bool SensorsBoard::checkForBase()
{
        if (SensorsBoard::checkForBaseOnSensorFrontBottomLeft() ||
            SensorsBoard::checkForBaseOnSensorFrontBottomCenter()||
            SensorsBoard::checkForBaseOnSensorFrontBottomRight())
                return true;
        return false;
}


// === CHECK HINDRANCE FUNCTIONS ===

bool SensorsBoard::checkForHindranceOnFront()
{
        if (SensorsBoard::getInfraredSensorFrontTopValue() < _FOE_DISTANCE_ || SensorsBoard::getUltrasonicFrontValue() < _FOE_DISTANCE_) return true;
        else return false;
}

bool SensorsBoard::checkForHindranceOnRight()
{
        if (SensorsBoard::getUltrasonicRightValue() < _FOE_DISTANCE_) return true;
        else return false;
}

bool SensorsBoard::checkForHindranceOnLeft()
{
        if (SensorsBoard::getUltrasonicLeftValue() < _FOE_DISTANCE_) return true;
        else return false;
}

bool SensorsBoard::checkForHindranceOnBack()
{
        if (SensorsBoard::getInfraredSensorBackValue() < _FOE_DISTANCE_ || SensorsBoard::getUltrasonicBackValue() < _FOE_DISTANCE_) return true;
        else return false;
}

//return true if there is an hindrance
bool SensorsBoard::checkForHindrance()
{
        if (SensorsBoard::checkForHindranceOnFront() ||
            SensorsBoard::checkForHindranceOnRight() ||
            SensorsBoard::checkForHindranceOnLeft() ||
            SensorsBoard::checkForHindranceOnBack())
                return true;
        else return false;
}
