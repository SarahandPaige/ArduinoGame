#include <LedControl.h>
// got library from arduino site

const int SW_pin[2] = {2,3}; 
const int X_pin[2] = {0,3};
const int Y_pin[2] = {1,4};
const int bar_row[2] = {0,7};


int ball_row = 6;
const byte p1[8] = {B00000000,B11100010,B01000010,B01000010,B01001110,B01101010,B01001110,B00000000};
const byte p2[8] = {B00000000,B11100001,B00100001,B00100001,B11101111,B10001001,B10001001,B11101111};
const byte W[8] = {B00000000,B01110111,B01001001,B01001001,B01000001,B01000001,B01000001,B01000001};
const byte I[8] = {B11111111,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000,B11111111};
const byte N[8] = {B10000001,B11000001,B10100001,B10010001,B10001001,B10000101,B10000011,B10000001};
const byte S[8] = {B00111100,B00100100,B00100000,B00100000,B00111100,B00000100,B00100100,B00111100};
const byte ex[8] = {B00011000,B00011000,B00000000,B00011000,B00011000,B00011000,B00011000,B00011000};



int row_off = B00000000;
bool going_up = false;
bool going_down = true;
bool end_game = false;
bool going_left = true;
bool at_row_end = false;
bool at_row_top = false;

bool p2wins = false;
bool not_moving = true;

LedControl lc=LedControl(12,10,11,1);
byte bar[2] = {B00011000,B00011000};

byte ball = B00100000;
byte prev_ball_val = ball;


void setup() {
  init();
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  pinMode(SW_pin[0], INPUT);
  digitalWrite(SW_pin[0], HIGH);
  pinMode(SW_pin[1], INPUT);
  digitalWrite(SW_pin[1], HIGH);
  

  lc.setRow(0,bar_row[0],bar[0]);
  lc.setRow(0,bar_row[1],bar[1]);
  lc.setRow(0,ball_row,ball);
  
  

  
  


}



void loop() {
  
  for(int i=0;i<2;i++){
    if(analogRead(X_pin[i])<=600 && analogRead(X_pin[i])>=500 ){
    //Serial.println("not moving");
      
    
      
    }else if (analogRead(X_pin[i])<517){
      //Serial.println("going Down");
       if((bar[i] & 1) !=1){
        bar[i] = bar[i]>>1;
        lc.setRow(0,bar_row[i],bar[i]);
        
      }
      
      
    }else if (analogRead(X_pin[i])>517){
      //Serial.println("going up");
     
       if((bar[i]>>7 &1) !=1){
          
          bar[i] = bar[i]<<1;
        
        lc.setRow(0,bar_row[i],bar[i]);
        
      }
      
    }
  
  }

  
  
  if(!end_game){
    if((ball>>7 &1 )==1){
      going_left = false;
        
        
    }else if(ball&1==1){
        going_left = true;
        
    }
   if(ball_row==1 && ((ball<<1)&bar[0]) ==0 && prev_ball_val>ball){
      Serial.println("ball right");
      Serial.println(ball,BIN);
      
      end_game = true; 
      p2wins = true;
     
   }else if(ball_row==1 && ((ball>>1)&bar[0]) ==0 && prev_ball_val<ball){
      Serial.println("ball left");
      Serial.println(ball,BIN);
      
      end_game = true; 
      p2wins = true;
      
      
    
   
   }else if(ball_row==6 && ((ball<<1)&bar[1]) ==0 && prev_ball_val>ball){
      Serial.println("ball right");
      Serial.println(ball,BIN);
      
      end_game = true; 
      p2wins = false;
   }else if(ball_row==6 && ((ball>>1)&bar[1]) ==0 && prev_ball_val<ball){
      Serial.println("ball left");
      Serial.println(ball,BIN);
      
      end_game = true; 
      p2wins = false;
      
      
   }else if(ball_row>1 && going_down){
     
      ball_row --; 
      at_row_end = false;
      
      lc.setRow(0,ball_row,ball);
      lc.setRow(0,ball_row+1,row_off);

  
    }else if(ball_row>=1 && ball_row<6){
      if(ball_row==1){
        at_row_top = true;
      }else{
        at_row_top = false;
      }
   
      going_down=false;
      
      ball_row ++;
       if(ball_row==1){
        at_row_top = true;
        }else{
          at_row_top = false;
          lc.setRow(0,ball_row,ball);
          lc.setRow(0,ball_row-1,row_off);
        }
        
        
        
        //lc.setRow(0,ball_row,ball);
        //lc.setRow(0,ball_row-1,row_off);
      
 
    
    
    }else{  
        
      going_down = true;
      at_row_end = true;
        
    }    
    prev_ball_val = ball;

    if(going_left && !at_row_end && !at_row_top){
      ball = ball<<1;
      
    }else if (!at_row_top && !at_row_end ){
      ball = ball>>1;
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
    
  }
  /*
  if(!(analogRead(X_pin[0])<=600 && analogRead(X_pin[0])>=500)&& end_game){
    end_game = false;
    for(int i=0;i<8;i++){
      lc.setRow(0,i,row_off);
    }
    lc.setRow(0,bar_row[0],bar[0]);
    lc.setRow(0,bar_row[1],bar[1]);
  }
  */
  
  
  
  
  
  
  
  delay(250);
  

}
