#include <LedControl.h>
// got library from arduino site

const int SW_pin1[2] = {2,3}; 
const int X_pin1[2] = {0,3};
const int Y_pin1[2] = {1,4};
const int bar_row[2] = {0,7};


int ball1_row1 = 6;
const byte p1[8] = {B00000000,B11100010,B01000010,B01000010,B01001110,B01101010,B01001110,B00000000};
const byte p2[8] = {B00000000,B11100001,B00100001,B00100001,B11101111,B10001001,B10001001,B11101111};
const byte W[8] = {B00000000,B01110111,B01001001,B01001001,B01000001,B01000001,B01000001,B01000001};
const byte I[8] = {B11111111,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000,B11111111};
const byte N[8] = {B10000001,B11000001,B10100001,B10010001,B10001001,B10000101,B10000011,B10000001};
const byte S[8] = {B00111100,B00100100,B00100000,B00100000,B00111100,B00000100,B00100100,B00111100};
const byte ex[8] = {B00011000,B00011000,B00000000,B00011000,B00011000,B00011000,B00011000,B00011000};

int displayed_message = 0;
extern LedControl lc;

int row_off = B00000000;
bool going_up1 = false;
bool going_down1 = true;
bool end_game1 = false;
bool going_left1 = true;
bool at_row_end1 = false;
bool at_row_top1 = false;

bool p2wins = false;
bool not_moving1 = true;


//LedControl lc=LedControl(12,10,11,1);
byte bar[2] = {B00011000,B00011000};

byte ball1 = B00100000;  
byte prev_ball1_val = ball1;


void beginning() {
  displayed_message = 0;
  row_off = B00000000;
  going_up1 = false;
  going_down1 = true;
  end_game1 = false;
  going_left1 = true;
  at_row_end1 = false;
  at_row_top1 = false;

  p2wins = false;
  not_moving1 = true;

  bar[0] = B00011000;
  bar[1] = B00011000;

  ball1 = B00100000;
  prev_ball1_val = ball1;
  init();
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  
  pinMode(SW_pin1[0], INPUT);
  digitalWrite(SW_pin1[0], HIGH);
  pinMode(SW_pin1[1], INPUT);
  digitalWrite(SW_pin1[1], HIGH);
  lc.clearDisplay(0);

  lc.setRow(0,bar_row[0],bar[0]);
  lc.setRow(0,bar_row[1],bar[1]);

  lc.setRow(0,ball1_row1,ball1);

  
  

  
  


}



void game1_led() {

  
  
  for(int i=0;i<2;i++){
    if(analogRead(X_pin1[i])<=600 && analogRead(X_pin1[i])>=500 ){
    
      
    
      
    }else if (analogRead(X_pin1[i])<517){
      
       if((bar[i] & 1) !=1){
        bar[i] = bar[i]>>1;
        lc.setRow(0,bar_row[i],bar[i]);
        
      }
      
      
    }else if (analogRead(X_pin1[i])>517){
      
     
       if((bar[i]>>7 &1) !=1){
          
          bar[i] = bar[i]<<1;
        
        lc.setRow(0,bar_row[i],bar[i]);
        
      }
      
    }
  
  }

  
  
  if(!end_game1){
    if((ball1>>7 &1 )==1){
      going_left1 = false;
        
        
    }else if(ball1&1==1){
        going_left1 = true;
        
    }
   if(ball1_row1==1 && ((ball1<<1)&bar[0]) ==0 && prev_ball1_val>ball1){
     
      Serial.println(ball1,BIN);
      
      end_game1 = true; 
      p2wins = true;
     
   }else if(ball1_row1==1 && ((ball1>>1)&bar[0]) ==0 && prev_ball1_val<ball1){
      
      Serial.println(ball1,BIN);
      
      end_game1 = true; 
      p2wins = true;
      
      
    
   
   }else if(ball1_row1==6 && ((ball1<<1)&bar[1]) ==0 && prev_ball1_val>ball1){
      
      Serial.println(ball1,BIN);
      
      end_game1 = true; 
      p2wins = false;
   }else if(ball1_row1==6 && ((ball1>>1)&bar[1]) ==0 && prev_ball1_val<ball1){
      
      Serial.println(ball1,BIN);
      
      end_game1 = true; 
      p2wins = false;
      
      
   }else if(ball1_row1>1 && going_down1){
     
      ball1_row1 --; 
      at_row_end1 = false;
      
      lc.setRow(0,ball1_row1,ball1);
      lc.setRow(0,ball1_row1+1,row_off);

  
    }else if(ball1_row1>=1 && ball1_row1<6){
      if(ball1_row1==1){
        at_row_top1 = true;
      }else{
        at_row_top1 = false;
      }
   
      going_down1=false;
      
      ball1_row1 ++;
       if(ball1_row1==1){
        at_row_top1 = true;
        }else{
          at_row_top1 = false;
          lc.setRow(0,ball1_row1,ball1);
          lc.setRow(0,ball1_row1-1,row_off);
        }
        
        
        
        //lc.setRow(0,ball1_row1,ball1);
        //lc.setRow(0,ball1_row1-1,row_off);
      
 
    
    
    }else{  
        
      going_down1 = true;
      at_row_end1 = true;
        
    }    
    prev_ball1_val = ball1;

    if(going_left1 && !at_row_end1 && !at_row_top1){
      ball1 = ball1<<1;
      
    }else if (!at_row_top1 && !at_row_end1 ){
      ball1 = ball1>>1;
    }
    
  }else{
    if(p2wins){
      for (int i=0;i<8;i++){
        lc.setRow(0,i,p2[i]);
      
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,W[i]);
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,I[i]);
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,N[i]);
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,S[i]);
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,ex[i]);
      }
      
    }else{
      for (int i=0;i<8;i++){
        lc.setRow(0,i,p1[i]);
      
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,W[i]);
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,I[i]);
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,N[i]);
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,S[i]);
      }
      delay(500);
      for (int i=0;i<8;i++){
        lc.setRow(0,i,ex[i]);
      }
      
    }
    displayed_message ++;
    
  }
}
