/*Example Input Serial data:

1007,1007,1007,1007,1007,1007\n
1008,1008,1008,1008,1008,1008\n
1009,1009,1009,1009,1009,1009\n
1010,1010,1010,1010,1010,1010\n
1011,1011,1011,1011,1011,1011\n
1012,1012,1012,1012,1012,1012\n
1013,1013,1013,1013,1013,1013\n
1014,1014,1014,1014,1014,1014\n
1015,1015,1015,1015,1015,1015\n

*/

//#include <LiquidCrystal\LiquidCrystal.h>
#include <string.h>
char inData[100];
char* flightdata[100];
char* saveptr;
byte index = 0;
/*LiquidCrystal lcd1(12, 5, 7, 8, 9, 10);
LiquidCrystal lcd2(12, 4, 7, 8, 9, 10);
LiquidCrystal lcd3(12, 3, 7, 8, 9, 10);
LiquidCrystal lcd4(12, 2, 7, 8, 9, 10);
LiquidCrystal lcd5(12, 6, 7, 8, 9, 10);*/

void setup()
{
	Serial.begin(115200);
        Serial.println("beginning testing...");
	/*lcd1.begin(16, 2);
	lcd2.begin(16, 2);
	lcd3.begin(16, 2);
	lcd4.begin(16, 2);
	lcd5.begin(16, 2);*/
}

void loop()
{
	//lcd1.clear();
	//lcd1.print("Screen is Ready!");
	while (Serial.available() > 0)
	{
		char aChar = Serial.read();
		if (aChar == '\n')
		{
			inData[index] = '\0'; // Keep the string NULL terminated
			Serial.println(inData);
			//lcd1.clear();
			//delay(10);
			//lcd1.print("END OF LINE!");
			// End of record detected. Time to parse			
			
			char *str;        //declare str
			int counter = 0; //initialise the counter

			str = strtok_r(inData, ",", &saveptr);	//point the first token before calling strtok_r with NULL
			flightdata[counter] = str;	//point appropriate flightdata index to str
			counter++;

			while ((str = strtok_r(NULL, ",", &saveptr))) // delimiter is the comma. NULL is the terminator
			{
				flightdata[counter] = str; //use the counter as an index to add each value to the array
				
				counter++; //increment the counter
				//lcd1.clear();
				/*delay(10);
				lcd1.print(counter);*/
			}
			Serial.println("DATA:");
			Serial.println(flightdata[0]);
			Serial.println(flightdata[1]);
			Serial.println(flightdata[2]);
			Serial.println(flightdata[3]);
			Serial.println(flightdata[4]);
			Serial.println(flightdata[5]);
			Serial.println("DATA END");
			Serial.println( );
			/*
			lcd1.clear();
			delay(10);
			lcd1.print("Screen1: "); 
			lcd1.print(flightdata[0]);
			/*lcd1.print(flightdata[1]);
			lcd1.print(flightdata[2]);
			lcd1.print(flightdata[3]);
			lcd1.print(flightdata[4]);
			lcd1.print(flightdata[5]);*/
			//print out the data stored in the value storage array index '0'
			//set cursor to next line using appropiate commands again
			/*lcd1.setCursor(0, 1);
			lcd1.print("Screen1: "); 
			lcd1.print(flightdata[1]); 

			lcd2.clear();
			delay(10);
			lcd2.print("Screen2: ");
			lcd2.print(flightdata[0]);
			lcd2.setCursor(0, 1);
			lcd2.print("screen2: ");
			lcd2.print(flightdata[1]);

			lcd3.clear();
			delay(10);
			lcd3.print("Screen3: ");
			lcd3.print(flightdata[0]);
			lcd3.setCursor(0, 1);
			lcd3.print("screen3: ");
			lcd3.print(flightdata[1]);

			lcd4.clear();
			delay(10);
			lcd4.print("Screen4: ");
			lcd4.print(flightdata[0]);
			lcd4.setCursor(0, 1);
			lcd4.print("screen4: ");
			lcd4.print(flightdata[1]);

			lcd5.clear();
			delay(10);
			lcd5.print("Screen5: ");
			lcd5.print(flightdata[0]);
			lcd5.setCursor(0, 1);
			lcd5.print("screen5: ");
			lcd5.print(flightdata[1]);

			delay(500);*/

			index = 0;
		}
		else
		{
			inData[index] = aChar;
			index++;
		}
	}
}
