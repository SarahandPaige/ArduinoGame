
#include <LedControl.h>

const int sw_pin2 = 2;
const int X_pin2 = 0;
const int Y_pin2 = 1;
byte snake = B00010000;
int snake_row = 4;
int old_snake_row = snake_row-1;
byte row_off2 = B00000000;
byte x[8] = {B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001};

byte ball2 = B01000000;
int ball_row2 = 7;
bool going_down2 = true;
bool at_row_end2 = false;
bool at_row_top2 = false;
int prev_ball_val2 = ball2;
bool going_left2 = true;
bool end_game2 = false;
int ball_delay = 350;
int cap = 0;


extern LedControl lc;

void beginning2() {
  ball2 = B01000000;
  ball_row2 = 7;
  going_down2 = true;
  at_row_end2 = false;
  at_row_top2 = false;
  prev_ball_val2 = ball2;
  going_left2 = true;
  end_game2 = false;
  ball_delay = 350;
  cap = 0;
  byte snake = B00010000;
  snake_row = 4;
  old_snake_row = snake_row-1;
  row_off2 = B00000000;

  init();
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  pinMode(sw_pin2, INPUT);
  digitalWrite(sw_pin2, HIGH);
  lc.setRow(0,snake_row,snake);
  lc.setRow(0,ball_row2,ball2);
}
void move_x(){
   if (analogRead(X_pin2)<50){
     if((snake & 1) !=1){
        snake = snake>>1;
        lc.setRow(0,snake_row,snake);
      
     } 
    }else if (analogRead(X_pin2)>1000){
     
       if((snake>>7 &1) !=1){
          
          snake = snake<<1;
        
          lc.setRow(0,snake_row,snake);  
      }     
  }
}
void move_y(){  
  if(analogRead(Y_pin2)<50){
   if(snake_row!=7){
      old_snake_row = snake_row;
      snake_row ++;
      lc.setRow(0,snake_row,snake);
      lc.setRow(0,old_snake_row,row_off2);
    }
  }else if(analogRead(Y_pin2)>1000){
    if(snake_row!=0){
      old_snake_row = snake_row;
      snake_row --;
      lc.setRow(0,snake_row,snake);
      lc.setRow(0,old_snake_row,row_off2);
    }
    
  }
  
}
void moving_balls(){
   if((ball2>>7 &1 )==1){
      going_left2 = false;
        
    }else if(ball2&1==1){
        going_left2 = true;
        
    }
    if(((snake & ball2>>1)!=0) && snake_row==ball_row2 && prev_ball_val2<ball2){
      end_game2 = true;
      
      
    }else if(((snake & ball2<<1)!=0) && snake_row==ball_row2 && prev_ball_val2>ball2){
      end_game2 = true;
      
    
    }else if(ball_row2>0 && going_down2){
     
      ball_row2 --; 
      at_row_end2 = false;
      if(snake_row==ball_row2 ){
        lc.setRow(0,ball_row2,ball2 | snake);
        lc.setRow(0,ball_row2+1,row_off2);
        
      }else if (snake_row == ball_row2+1){
        lc.setRow(0,ball_row2,ball2);
        lc.setRow(0,ball_row2+1,snake);
      }else{
        lc.setRow(0,ball_row2,ball2);
        lc.setRow(0,ball_row2+1,row_off2);
      }
  
    }else if(ball_row2>=0 && ball_row2<7){
      if(ball_row2==0){
        at_row_top2 = true;
      }else{
        at_row_top2 = false;
      }
   
      going_down2=false;
      
      ball_row2 ++;
       if(ball_row2==0){
        at_row_top2 = true;
       }else if(snake_row==ball_row2){
          at_row_top2 = false;
          lc.setRow(0,ball_row2,ball2|snake);
          lc.setRow(0,ball_row2-1,row_off2);
        }else if(snake_row==ball_row2-1){
          at_row_top2 = false;
          lc.setRow(0,ball_row2,ball2);
          lc.setRow(0,ball_row2-1,snake);
        }else{
          at_row_top2 = false;
          lc.setRow(0,ball_row2,ball2);
          lc.setRow(0,ball_row2-1,row_off2);
        }

    }else{  
        
      going_down2 = true;
      at_row_end2 = true;
        
    }    
    prev_ball_val2 = ball2;

    if(going_left2 && !at_row_end2 && !at_row_top2){
      ball2 = ball2<<1;
      
    }else if (!at_row_top2 && !at_row_end2 ){
      ball2 = ball2>>1;
    }
    
}
void game2_led() {
    
  if(analogRead(X_pin2)<=600 && analogRead(X_pin2)>=500 ){

  }else{
    move_x();
  }
  if(analogRead(Y_pin2)<550 && analogRead(Y_pin2)>450){

    
  }else {
    move_y();
    
  }
  
  if(!end_game2){
    
    moving_balls(); 
    cap ++;
    if(cap >=20 && ball2<255){
      cap = cap-20;
      if(ball2&1 !=0){
        ball2 = ball2 +1;
        ball_delay = ball_delay-75;
        
      }else{
         ball2 = ball2 | (ball2>>1);
      }
    }
    
  }else{
    for(int i=0;i<8;i++){
      lc.setRow(0,i,x[i]);
    }
  }
  
  delay(ball_delay);
}