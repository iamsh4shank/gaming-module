#include<LiquidCrystal.h>                                                        
LiquidCrystal lcd (8,7,6,5,4,3);                                                 
int ledPin = 13;                                                                 
int buttonPin = 2;                                                               
                                                                                 
int ledToggle;
int previousState = HIGH;
unsigned int previousPress; 
volatile int buttonFlag;
int buttonDebounce = 20;
int i=0;
int pos=0;
int Speed=100;
String typea    = "                      ##        ######     ##       ####     ####       ########       ##                  ";  
String typeaa   = "                 ##       ####          ##     ####       ##         ##           ##                       ";                       
                
int  typeA[]    = {22,23,32,33,34,35,36,37,43,44,52,53,54,55,61,62,63,64,72,73,74,75,76,77,78,79,87,88};//28
int typeAA[]    = {17,18,26,27,28,29,40,41,47,48,49,50,58,59,69,70,82,83};//18

void setup()
{
  lcd.begin(16,2);
  lcd.begin(16,2);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), button_ISR, CHANGE);
  while(ledToggle==0)
  {
    lcd.clear();
    delay(500);
    lcd.print("   START GAME   ");
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print('O');
}

void loop() 
{
while(1)
 {
   for(i=0;i<89;i++)
   {
    if(pos==0)
    {
      lcd.setCursor(1,0);
      lcd.print(typea.substring(i+1,16+i));
    }
    else
    {
      lcd.setCursor(0,0);
      lcd.print(typea.substring(i,16+i));
    }
    if(pos==1)
    {
      lcd.setCursor(1,1);
      lcd.print(typeaa.substring(i+1,16+i));
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print(typeaa.substring(i,16+i));
    }
    for(int j=0;j<28;j++)
    {
      if(typeA[j]==i)
      {
        if(pos==0)
        {
          gameover();
        }
      }
    }
    for(int j=0;j<18;j++)
    {
      if(typeAA[j]==i)
      {
        if(pos==1)
        {
          gameover();
        }
      }
    }
    delay(Speed);
  }
   winner();
 }
}

void gameover (void)
{
  detachInterrupt(digitalPinToInterrupt(2));
  while(1)
  {
    lcd.clear();
    delay(500);
    lcd.print("   GAME OVER   ");
    delay(500);
  }
}

void winner (void)
{
  detachInterrupt(digitalPinToInterrupt(2));
  while(1)
  {
    lcd.clear();
    delay(500);
    lcd.print(" WINNER!");
    lcd.setCursor(0,1);
    delay(500);
  }
}

void button_ISR()
{
   buttonFlag = 1;
   if((millis() - previousPress) > buttonDebounce && buttonFlag)
  {
    previousPress = millis();
    if(digitalRead(buttonPin) == LOW && previousState == HIGH)
    {
      ledToggle =! ledToggle;
      digitalWrite(ledPin, ledToggle);
      previousState = LOW;
      if(ledToggle)
      {
       lcd.setCursor(0,0);
       lcd.print('O');
       lcd.setCursor(0,1);
       lcd.print(' ');
       pos=0;
      }
      else
      {
       lcd.setCursor(0,1);
       lcd.print('O');
       lcd.setCursor(0,0);
       lcd.print(' ');
       pos=1;
      }
    }    
    else if(digitalRead(buttonPin) == HIGH && previousState == LOW)
    {
      previousState = HIGH;
    }
    buttonFlag = 0;
  }
}
