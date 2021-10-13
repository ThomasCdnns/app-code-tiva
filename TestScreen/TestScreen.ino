
#include "Iseplogo128.h"
void setup() {
  // put your setup code here, to run once:

InitI2C();
InitScreen();

Display(motif);                           // affichage de l'image décrite dans le tabelau de donnée motif.h
//DisplayString(0,5,"APP ISEP");            // Ecriture sur la 5ème ligne 
//DisplayString(0,7,"Ecole du numerique");  // Ecriture sur la dernière ligne. 



// void test_fft(); // La fonction test_fft disponible dans le fichier fft.ino montre comment utiliser la fft

}

void loop() {

  // put your main code here, to run repeatedly: 

}
