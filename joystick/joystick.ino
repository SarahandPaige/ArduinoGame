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


LedControl lc=LedControl(12,10,11,1);
byte bar = B00111000;
byte ball = B00100000;
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

void loop() {
  

  if(analogRead(X_pin)<=600 && analogRead(X_pin)>=500 ){
    //Serial.println("not moving");
    
  }else if (analogRead(X_pin)<517){
    //Serial.println("going Down");
      if((bar>>7 &1) !=1){
        
        bar = bar<<1;
      
      lc.setRow(0,0,bar);
    }
    
  }else if (analogRead(X_pin)>517){
    //Serial.println("going up");
    if((bar & 1) !=1){
      bar = bar>>1;
      lc.setRow(0,0,bar);
    }
  }
  
  if(!end_game){
    if(ball_row>1 && going_down){
     
      ball_row --;
        
        
      //ball = ball <<1;
      
      lc.setRow(0,ball_row,ball);
      lc.setRow(0,ball_row+1,row_off);

  
    }else if(ball_row>=1 && ball_row<7){
      if(ball_row==1 && (ball&bar) ==0){
        end_game = true; 
        
      }else{
        going_down=false;
        going_up=true;
        ball_row ++;
        
        
        //ball = ball >>1;
        lc.setRow(0,ball_row,ball);
        lc.setRow(0,ball_row-1,row_off);
      }
    
    
    }else{
      
      
        
      going_down = true;
      going_up = false;
        
    }    
    if((ball>>7 &1 )==1){
        going_left = false;
        Serial.println("reached left");
        
    }else if(ball&1==1){
        going_left = true;
        Serial.println("reached right");
    }
    if(going_left){
      ball = ball<<1;
      
    }else{
      ball = ball>>1;
    }
    
  }else{
    lc.setRow(0,0,row_off);
  }
  
  
  
  
  
  delay(1000);
  

}
