/**
 *    \file Ecran_test.ino
 *    \brief Code d'affichage de l'écran
 *    \author Arthur Duytschaever & Nicolas Sobczak
 *    \date octobre 2016
*/


/* ======================================================================================================
 *      Include
 * ======================================================================================================
 */
#include "logoCrysteo.h"
#include "Ecran.h"
#include "U8glib.h"


/* ======================================================================================================
 *      Define
 * ======================================================================================================
 */
#define MENU_ITEMS 4
#define _MENU1_ "Strategie"
#define _MENU2_ "Test"
#define _MENU3_ "Debug"
#define _MENU4_ "Back"

#define KEY_NONE 0
#define KEY_PREV 1
#define KEY_NEXT 2
#define KEY_SELECT 3
#define KEY_BACK 4


/* ======================================================================================================
 *      Initialisation
 * ======================================================================================================
 */
//Declaration de l'objet UG8 + pin du SPI
U8GLIB_ST7920_128X64_1X u8g(13, 51, 14);  // SPI Com: SCK = en = 13, MOSI = rw = 51, CS = di = 14

//Declaration de l'encodeur = le bouton
const int entry = 2; 
const int encoderMoins = 52;
const int encoderPlus = 50;

//Declaration de trucs inconnus
uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;
uint8_t menu_redraw_required = 0;
uint8_t last_key_code = KEY_NONE;
int menu_current = 0;
uint8_t i, h;
u8g_uint_t w, d;
int selecteurMenu = 10;

//Definition du nom des menus
const char *menu_strings[MENU_ITEMS] = {_MENU1_, _MENU2_, _MENU3_, _MENU4_};

//Declaration des objets ecran
Ecran ecranStrategie;
Ecran ecranTest;
Ecran ecranDebug;


/* ======================================================================================================
 *      Fonctions
 * ======================================================================================================
 */
 
/**____________________________________________________
 *   \fn void drawEcranDacceuil(void)
 *   \param void
 *   Fonction qui affiche le logo crysteo au démarrage de l'écran
 */
void drawEcranDacceuil(void) {
  u8g.drawBitmapP(0, 0, 16, 64, logoCrysteo);
}


/**____________________________________________________
 *   \fn void updateMenu(void)
 *   \param void
 *   Fonction qui selectionne le menu sur lequel le curseur est place
 *   The position of the cursor bar is stored in the global variable menu_current.
 *   External buttons, a touchpanel or other sensors might modify the cursor bar position:
 */
void updateMenu(void) {
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;
  
  switch ( uiKeyCode ) {
    case KEY_NEXT:
      menu_current++;
      if ( menu_current >= MENU_ITEMS )
        menu_current = 0;
      menu_redraw_required = 1;
      break;
    case KEY_PREV:
      if ( menu_current == 0 )
        menu_current = MENU_ITEMS;
      menu_current--;
      menu_redraw_required = 1;
      break;
    case KEY_SELECT:
      for(int indice=0; indice <= MENU_ITEMS; indice++){
        if(menu_current==indice){
          selecteurMenu = indice;
        }
      }
      break;  
  }
}


/**____________________________________________________
 *   \fn void uiStep(void)
 *   \param void
 *   Fonction qui initialise la configuration des pins
 */
void uiStep(void) {
  uiKeyCodeSecond = uiKeyCodeFirst;
  if ( digitalRead(encoderMoins) == LOW )
    uiKeyCodeFirst = KEY_PREV;
  else if ( digitalRead(encoderPlus) == LOW )
    uiKeyCodeFirst = KEY_NEXT;
  else if ( digitalRead(entry) == LOW )
    uiKeyCodeFirst = KEY_SELECT;
  //else if ( digitalRead(uiKeyBack) == LOW )
    //uiKeyCodeFirst = KEY_BACK;
  else 
    uiKeyCodeFirst = KEY_NONE;
  
  if ( uiKeyCodeSecond == uiKeyCodeFirst )
    uiKeyCode = uiKeyCodeFirst;
  else
    uiKeyCode = KEY_NONE;
}


/**____________________________________________________
 *   \fn void drawMainMenu(void)
 *   \param void
 *   Afficher le menu après le logo + bande de selection
 */
void drawMainMenu(void) {
  uint8_t i, h;
  u8g_uint_t w, d;
   
  u8g.setFont(u8g_font_ncenB10);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  
  h = u8g.getFontAscent()-u8g.getFontDescent();
  w = u8g.getWidth();
  for( i = 0; i < MENU_ITEMS; i++ ) {
    d = (w - u8g.getStrWidth(menu_strings[i]) ) / 2;
    u8g.setDefaultForegroundColor();
    if ( i == menu_current ) {
      u8g.drawBox(0, i*h+1, w, h);
      u8g.setDefaultBackgroundColor();
    }
    u8g.drawStr(d, i*h, menu_strings[i]);
  }
}


/**____________________________________________________
 *   \fn void drawMenuStrategie(void)
 *   \param void
 *   Fonction qui affiche le menu de strategie
 */
void drawMenuStrategie(void)
{
  u8g.setPrintPos(0,0); 
  //initialisation de l'objet
  ecranStrategie.setNom("Ecran de strat", 0);
  ecranStrategie.setNom("Valeur test", 1);
  ecranStrategie.setValue(3.14, 1);
  
  //affichage a l'ecran
  u8g.print(ecranStrategie.getNom(0));
  u8g.setPrintPos(0, 12); 
  u8g.print(ecranStrategie.getNom(1) + ": ");
  u8g.print(ecranStrategie.getValue(1));
}


/**____________________________________________________
 *   \fn void drawMenuTest(void)
 *   \param void
 *   Fonction qui affiche l'ecran de test
 */
void drawMenuTest(void)
{
  u8g.setPrintPos(0,0); 
  //initialisation de l'objet
  ecranTest.setNom("string", 0);
  ecranTest.setNom("string", 1);
  ecranTest.setNom("string", 2);
  ecranTest.setNom("string", 3);
  ecranTest.setNom("string", 4);
  for (int i = 0; i < 5; ++i)
  {
    ecranTest.setValue(3.2*i, i);
  }
  //affichage a l'ecran
  for (int i = 0; i < 5; ++i)
  {
      u8g.setPrintPos(0, 0 + 11 * i);
      u8g.print(ecranTest.getNom(i) + ": ");
      u8g.print(ecranTest.getValue(i));
  }
}


/**____________________________________________________
 *   \fn void drawMenuDebug(void)
 *   \param void
 *   Fonction qui affiche l'ecran de debug
 */
void drawMenuDebug(void)
{
  u8g.setPrintPos(0,0); 
  //initialisation de l'objet
  ecranDebug.setNom("Debug", 0);
  ecranDebug.setNom("coucou", 1);
  ecranDebug.setNom("mon", 2);
  ecranDebug.setNom("petit", 3);
  ecranDebug.setNom("pigeon", 4);
  for (int i = 0; i < 5; ++i){
    ecranDebug.setValue(3.2*i, i);
  }
  //affichage a l'ecran
  for (int i = 0; i < 5; ++i)
  {
      u8g.setPrintPos(0, 0 + 11 * i);
      u8g.print(ecranDebug.getNom(i));
      if (i != 0)
      {
        u8g.print(": ");
        u8g.print(ecranDebug.getValue(i));
      }
  }
}


/**____________________________________________________
 *   \fn void selectMainMenu(int selecteurMenu)
 *   \param int selectMainMenu
 *   Fonction qui affiche le menu correspondant à la selection du curseur
 */
void selectMainMenu(int selecteurMenu){// fonction beug.....
  Serial.println(selecteurMenu);
  u8g.firstPage();
  switch(selecteurMenu)
  {
    case 0 :   
    { 
        u8g.firstPage();        // potentiellement source de beug
        do{
          drawMenuStrategie();
        }while(u8g.nextPage());
        break;
    }
    case 1 : 
    {
        u8g.firstPage();
        do{
          drawMenuTest();
        }while(u8g.nextPage());
        break;
    }
    case 2 :
    {
        u8g.firstPage();
        do{
          drawMenuDebug();
        }while(u8g.nextPage());
        break;
    }
    case 3 :
    {
        u8g.firstPage();
        do{
          drawEcranDacceuil();
        }while(u8g.nextPage());
        break;
    }
  }
}


//____________________________________________________
//____________________________________________________
void setup(void) {
  //Attachinterrupt()
  Serial.begin(9600);
  pinMode(entry, INPUT_PULLUP);
  pinMode(encoderMoins, INPUT_PULLUP);
  pinMode(encoderPlus, INPUT_PULLUP);
  //digitalWrite(entry,HIGH);
  u8g.setColorIndex(1); // Affichage en mode N&B
   
  //u8g.firstPage(); // Sélectionne la 1er page mémoire de l'écran
  u8g.firstPage();
  do {
      drawEcranDacceuil();
  } while(u8g.nextPage());  // while loop keep running until nextPage() returns '1'
  delay(1000);
  
  uiStep();
  // flip screen, if required
  // u8g.setRot180();
  // setup key detection and debounce algorithm
  menu_redraw_required = 1;
}


void loop(void) {
  
  uiStep();                                     // check for key press 
  if (  menu_redraw_required != 0 ) {
    u8g.firstPage();
    do{
       drawMainMenu();
    } while( u8g.nextPage() );
    menu_redraw_required = 0;
  }
  selectMainMenu(selecteurMenu);

  selecteurMenu= -1;
  updateMenu();     
}



