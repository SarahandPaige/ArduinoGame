#include <LedControl.h>
// got library from arduino site

const int SW_pin = 2; 
const int X_pin = 0;
const int Y_pin = 1;
int ball_row = 7;


int row_off = B00000000;
bool going_up = false;
bool going_down = true;
bool end_game = false;
bool going_left = true;
bool at_row_end = false;
bool at_row_top = false;


LedControl lc=LedControl(12,10,11,1);
byte bar = B00011000;
byte ball = B00100000;
byte prev_ball_val = ball;
void setup() {
  init();
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  lc.setRow(0,0,bar);
  lc.setRow(0,ball_row,ball);
  

  
  


}
int reverse_bar(int bar){
  int reverse = 0;
  int last_dig = B10000000;
  for(int i=1;i<9;i++){
    if((bar>>i&1)==1){
      reverse = reverse | (last_dig>>i);
      
    }
    
  }
  Serial.println(bar,BIN);
  Serial.println(reverse,BIN);
  return reverse;
}



void loop() {
  

  if(analogRead(X_pin)<=600 && analogRead(X_pin)>=500 ){
    //Serial.println("not moving");
    
  }else if (analogRead(X_pin)<517){
    //Serial.println("going Down");
     if((bar & 1) !=1){
      bar = bar>>1;
      lc.setRow(0,0,bar);
      
    }
    
  }else if (analogRead(X_pin)>517){
    //Serial.println("going up");
   
     if((bar>>7 &1) !=1){
        
        bar = bar<<1;
      
      lc.setRow(0,0,bar);
      
    }
  }
  
  if(!end_game){
    if((ball>>7 &1 )==1){
      going_left = false;
        
        
    }else if(ball&1==1){
        going_left = true;
        
    }
   if(ball_row==1 && ((ball<<1)&bar) ==0 && prev_ball_val>ball){
      Serial.println("ball right");
      Serial.println(ball,BIN);
      
      end_game = true; 
   }else if(ball_row==1 && ((ball>>1)&bar) ==0 && prev_ball_val<ball){
      Serial.println("ball left");
      Serial.println(ball,BIN);
      
      end_game = true; 
    
   }else if(ball_row>1 && going_down){
     
      ball_row --; 
      at_row_end = false;
      
      lc.setRow(0,ball_row,ball);
      lc.setRow(0,ball_row+1,row_off);

  
    }else if(ball_row>=1 && ball_row<7){
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
  
  
  
  
  
  delay(200);
  

}
