//#include <LiquidCrystal\LiquidCrystal.h>
#include <string.h>

#define NUM_LCDS = 5

char inData[100];
char* topRowData[100];
char* bottomRowData[100];
char* rgb[100];
char* saveptr;
int index = 0;
char curr = '\0';
int lcdCounter = 0;
int counter = 0;
int splitIndex = 0;
LiquidCrystal lcds[NUM_LCDS] = {
  LiquidCrystal(12, 5, 7, 8, 9, 10), 
  LiquidCrystal(12, 4, 7, 8, 9, 10), 
  LiquidCrystal(12, 3, 7, 8, 9, 10), 
  LiquidCrystal(12, 2, 7, 8, 9, 10), 
  LiquidCrystal(12, 6, 7, 8, 9, 10)
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Parse Testing...");
  for(int i = 0; i < NUM_LCDS; i++)
    lcds[i].begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0)
  {
    curr = Serial.read();
    //Serial.print(curr);
    if(curr == '\n')
    {
      inData[index] = '\0';
      Serial.println(inData);
      
      char *str;
      
      str = strtok_r(inData, ",", &saveptr);  //first entry in sequence is title, goes in top row of display
      topRowData[counter] = str;
      splitIndex=1;
      
      while(str = strtok_r(NULL, ",", &saveptr))
      {
        if(splitIndex == 1)
          bottomRowData[counter] = str;
        else
          rgb[counter] = str;
          
        splitIndex++;
      }
      Serial.println("DATA:");
      Serial.println(topRowData[counter]);
      Serial.println(bottomRowData[counter]);
      Serial.println(rgb[counter]);
      Serial.println("DATA END\n");
      counter++;
      index = 0;
    }
    else
    {
      inData[index] = curr;
      index++;
    }
  }
  
  for(int i = 0; i < NUM_LCDS; i++)
  {
    lcds[i].clear();
    delay(10);
    lcds[i].print(topRowData[i]);
    lcds[i].setCursor(0, 1);
    lcds[i].print(bottomRowData[i]);
  }
}
