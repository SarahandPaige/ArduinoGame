#include <LedControl.h>
// got library from arduino site

const int SW_pin[2] = {2,3}; 
const int X_pin[2] = {0,3};
const int Y_pin[2] = {1,4};
const int bar_row[2] = {0,7};


int ball_row = 6;


int row_off = B00000000;
bool going_up = false;
bool going_down = true;
bool end_game = false;
bool going_left = true;
bool at_row_end = false;
bool at_row_top = false;

bool p2wins = false;

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
    lc.setRow(0,0,row_off);
  }
  
  
  
  
  
  
  delay(350);
  

}
