#include <LedControl.h>

const int sw_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;
byte snake = B00010000;
int snake_row = 4;
int old_snake_row = snake_row-1;
byte row_off = B00000000;
byte x[8] = {B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001};
LedControl lc=LedControl(12,10,11,1);
byte ball[60] = {B01000000};
int ball_row[60] = {7};
bool going_down[60] = {true};
bool at_row_end[60] = {false};
bool at_row_top[60] = {false};
int prev_ball_val[60] = {ball[0]};
bool going_left[60] = {true};
bool end_game = false;
int ball_delay = 350;
int cap = 0;
byte random_byte;

void setup() {
  init();
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  pinMode(sw_pin, INPUT);
  digitalWrite(sw_pin, HIGH);
  lc.setRow(0,snake_row,snake);
  lc.setRow(0,ball_row[0],ball[0]);
  

}
void move_x(){
   if (analogRead(X_pin)<50){
      //Serial.println("going Down");
     if((snake & 1) !=1){
        snake = snake>>1;
        lc.setRow(0,snake_row,snake);
      
     }
      
      
    }else if (analogRead(X_pin)>1000){
      //Serial.println("going up");
     
       if((snake>>7 &1) !=1){
          
          snake = snake<<1;
        
          lc.setRow(0,snake_row,snake);
          
        
      }     
  
  }
}

void move_y(){
  
 
  
  if(analogRead(Y_pin)<50){
   if(snake_row!=7){
      old_snake_row = snake_row;
      
      snake_row ++;
      lc.setRow(0,snake_row,snake);
      lc.setRow(0,old_snake_row,row_off);
      
    }
   
    
  }else if(analogRead(Y_pin)>1000){
    if(snake_row!=0){
      old_snake_row = snake_row;
      
      snake_row --;
      lc.setRow(0,snake_row,snake);
      lc.setRow(0,old_snake_row,row_off);
      
    }
    
  }
  
}
void moving_balls(){
   if((ball[0]>>7 &1 )==1){
      going_left[0] = false;
        
        
    }else if(ball[0]&1==1){
        going_left[0] = true;
        
    }
    if(((snake & ball[0]>>1)!=0) && snake_row==ball_row[0] && prev_ball_val[0]<ball[0]){
      end_game = true;
      Serial.println(ball[0],BIN);
      Serial.println(snake,BIN);
    
    
    }else    if(((snake & ball[0]<<1)!=0) && snake_row==ball_row[0] && prev_ball_val[0]>ball[0]){
      end_game = true;
      Serial.println(ball[0],BIN);
      Serial.println(snake,BIN);
    
    
    
    
    }else if(ball_row[0]>0 && going_down[0]){
     
      ball_row[0] --; 
      at_row_end[0] = false;
      if(snake_row==ball_row[0] ){
        lc.setRow(0,ball_row[0],ball[0] | snake);
        lc.setRow(0,ball_row[0]+1,row_off);
        
      }else if (snake_row == ball_row[0]+1){
        lc.setRow(0,ball_row[0],ball[0]);
        lc.setRow(0,ball_row[0]+1,snake);
      }else{
        lc.setRow(0,ball_row[0],ball[0]);
        lc.setRow(0,ball_row[0]+1,row_off);
      }
      

  
    }else if(ball_row[0]>=0 && ball_row[0]<7){
      if(ball_row[0]==0){
        at_row_top[0] = true;
      }else{
        at_row_top[0] = false;
      }
   
      going_down[0]=false;
      
      ball_row[0] ++;
       if(ball_row[0]==0){
        at_row_top[0] = true;
       }else if(snake_row==ball_row[0]){
          at_row_top[0] = false;
          lc.setRow(0,ball_row[0],ball[0]|snake);
          lc.setRow(0,ball_row[0]-1,row_off);
        }else if(snake_row==ball_row[0]-1){
          at_row_top[0] = false;
          lc.setRow(0,ball_row[0],ball[0]);
          lc.setRow(0,ball_row[0]-1,snake);
        }else{
          at_row_top[0] = false;
          lc.setRow(0,ball_row[0],ball[0]);
          lc.setRow(0,ball_row[0]-1,row_off);
        }
   
    
    }else{  
        
      going_down[0] = true;
      at_row_end[0] = true;
        
    }    
    prev_ball_val[0] = ball[0];

    if(going_left[0] && !at_row_end[0] && !at_row_top[0]){
      ball[0] = ball[0]<<1;
      
    }else if (!at_row_top[0] && !at_row_end[0] ){
      ball[0] = ball[0]>>1;
    }
    
}
void loop() {
    
  if(analogRead(X_pin)<=600 && analogRead(X_pin)>=500 ){
    //Serial.println("not moving");

  }else{
    move_x();
  }
  if(analogRead(Y_pin)<550 && analogRead(Y_pin)>450){
    //Serial.println("not moving y");
    
  }else {
    move_y();
    
  }
  
  if(!end_game){
    
    moving_balls(); 
    cap ++;
    if(cap >=20 && ball[0]<255){
      cap = cap-20;
      if(ball[0]&1 !=0){
        ball[0] = ball[0] +1;
        ball_delay = ball_delay-75;
        
      }else{
         ball[0] = ball[0] | (ball[0]>>1);
         
      }
      
     
    }
    
  }else{
    for(int i=0;i<8;i++){
      lc.setRow(0,i,x[i]);
    }
  }
  
  delay(ball_delay);
}
