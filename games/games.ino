#include <LedControl.h>
#include "game1.h"
#include "game2.h"
LedControl lc=LedControl(12,10,11,1);
bool button_state = false;
bool play_1 = false;
bool play_2 = false;
int my_button = 5;
bool game_start1 = false;
bool game_start2 = false;

 


void setup() {
  init();
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  pinMode(my_button,INPUT);
  digitalWrite(my_button,HIGH);
  lc.setRow(0,0,00000000);

}

void loop() {
  if(digitalRead(my_button) == LOW && !play_1){
    play_1 = true;
    play_2 = false;
    game_start1 = true;
    
  }else if(digitalRead(my_button) == LOW && !play_2){
    play_1 = false;
    play_2 = true;
    game_start2 = true;
    
  }
  if(play_1){
    if(game_start1){
      
      beginning();
      game_start1 = false;
      delay(500);
    }
    
    delay(300);
    game1_led();
  }
  if(play_2){
    if(game_start2){
      
      beginning2();
      game_start2 = false;
      delay(500); 
    }
   
     
   game2_led();
  }

}
