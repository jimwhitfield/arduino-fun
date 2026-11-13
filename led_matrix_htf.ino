// !!!
// Scroll down past where the alphabet is defined in order to set what to say
// !!!
#define CHAR_WIDTH 5                     // each character is 5 columns wide
#define SP {0, 0, 0, 0, 0}               //Space
#define DOT {0, 0, 1, 0, 0}              //Space
#define EX {0, 125, 0, 0, 0}             //Exclamation !
#define EX2 {0, 125, 0, 125, 0}          //Exclamation !!
#define A_ {31, 36, 68, 36, 31}
#define B_ {127, 73, 73, 73, 54}
#define C_ {62, 65, 65, 65, 34}
#define D_ {127, 65, 65, 34, 28}
#define E_ {127, 73, 73, 65, 65}
#define F_ {127, 72, 72, 72, 64}
#define G_ {62, 65, 65, 69, 38}
#define H_ {127, 8, 8, 8, 127}
#define I_ {0, 65, 127, 65, 0}
#define J_ {2, 1, 1, 1, 126}
#define K_ {127, 8, 20, 34, 65}
#define L_ {127, 1, 1, 1, 1}
#define M_ {127, 32, 16, 32, 127}
#define N_ {127, 32, 16, 8, 127}
#define O_ {62, 65, 65, 65, 62}
#define P_ {127, 72, 72, 72, 48}
#define Q_ {62, 65, 69, 66, 61}
#define R_ {127, 72, 76, 74, 49}
#define S_ {50, 73, 73, 73, 38}
#define T_ {64, 64, 127, 64, 64}
#define U_ {126, 1, 1, 1, 126}
#define V_ {124, 2, 1, 2, 124}
#define W_ {126, 1, 6, 1, 126}
#define X_ {99, 20, 8, 20, 99}
#define Y_ {96, 16, 15, 16, 96}
#define Z_ {67, 69, 73, 81, 97}
#define BOX {127,65,65,65,127}

// Write the sentence with commas separating each letter
// note the first number must equal the number of letters
byte phrase[28][CHAR_WIDTH]={W_,E_,L_,C_,O_,M_,E_,SP,T_,O_,SP,H_,A_,C_,K_,SP,T_,H_,E_,SP,F_,U_,T_,U_,R_,E_,EX2,SP};
int len = sizeof(phrase)/CHAR_WIDTH;

//We always have to include the library
#include "LedControl.h"

//pin 12 is connected to the DataIn 
//pin 11 is connected to the CLK 
//pin 10 is connected to LOAD 

//LedControl(int dataPin, int clkPin, int csPin, int numDevices);
LedControl lc=LedControl(12,11,10,1);

void setup() {
  //The MAX72XX is in power-saving mode on startup, we have to do a wakeup call   
  lc.shutdown(0,false);
  //Set the brightness to a medium values (0~15 possible values)
  lc.setIntensity(0,2);
  //and clear the display
  lc.clearDisplay(0);
}

#define BLOCK_WIDTH 12
// In the first issue we will adapt the length of the sentence (characters)
int ltr_buffer[BLOCK_WIDTH]={8,7,6,5,4,3,2,1,0,-1,-2,-3};

void loop() { 

  for (int letter=0; letter<len; letter++){
    for (int moves = BLOCK_WIDTH; moves>=CHAR_WIDTH; moves--) {
      for (int i=0; i<CHAR_WIDTH; i++){ 
        lc.setRow(0,ltr_buffer[i+moves-CHAR_WIDTH],phrase[letter][i]); 
      }
      delay(75); // speed of animation
      lc.clearDisplay(0);
    }
  }//end for letter

}
