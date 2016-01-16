#include "SparkTime.h"

UDP UDPClient;
SparkTime rtc;

unsigned long currentTime;
unsigned long lastTime = 0UL;
String timeStr;

int getData(String input);
String classTimes[20];
String dayRules[20];
String allInputs[20];
int timeIndex = 0;
String result;

void setup() {
    rtc.begin(&UDPClient, "north-america.pool.ntp.org");
    rtc.setTimeZone(-6); // gmt offset
    Serial1.begin(9600);
    Spark.function("getData", getData);
    pinMode(D4, OUTPUT); //DeMUX1 ENABLE ACTIVE LOW
    pinMode(D7, OUTPUT); //DeMUX1 A
    pinMode(D6, OUTPUT); //DeMUX1 B
    pinMode(D5, OUTPUT); //DeMUX1 C

    pinMode(D0, OUTPUT); //DeMUX1 ENABLE ACTIVE LOW
    pinMode(D3, OUTPUT); //DeMUX2 A
    pinMode(D2, OUTPUT); //DeMUX2 B
    pinMode(D1, OUTPUT); //DeMUX2 C

    pinMode(A0, OUTPUT);
    analogWrite(A0, 0);
}

void loop() {
    currentTime = rtc.now();
    if (currentTime != lastTime) {
        byte sec = rtc.second(currentTime);

      	// Build Date String
      	timeStr = "";
      	timeStr += rtc.dayOfWeekString(currentTime);
      	timeStr += ", ";
      	timeStr += rtc.monthNameString(currentTime);
      	timeStr += " ";
      	timeStr += rtc.dayString(currentTime);
      	timeStr += ", ";
      	timeStr += rtc.yearString(currentTime);

      	// Just the time in 24 hour format
      	timeStr += " ";
      	timeStr += rtc.hourString(currentTime);
      	timeStr += ":";
      	timeStr += rtc.minuteString(currentTime);
      	timeStr += ":";
      	timeStr += rtc.secondString(currentTime);
      	//Serial.println(timeStr);

        lastTime = currentTime;
    }

    for(int i = 0; i < 11; i++) {
        setLEDLine(i);
        for(int brightness = 0.20*256; brightness < 0.35*256; brightness++)
        {
            analogWrite(A0, brightness);
            delay(50);
        }
        for(int brightness = 0.35*256; brightness >= 0.20*256; brightness--)
        {
            analogWrite(A0, brightness);
            delay(50);
        }

        delay(500);
    }

/*
    int eventIndex = 0;
    while (rtc.hourString(currentTime).toInt() > classTimes[eventIndex]) {  //ignore all classes that are scheduled before current time
        eventIndex++;
    }

    for(int i = 0; i < 10; i++)
    {
        setLEDLine(i);
        for(int x = 0; x < 256; x++)
        {
            analogWrite(A0, x);
            delay(25);
        }
        for(int x = 255; x >= 0; x--)
        {
            analogWrite(A0, x);
            delay(25);
        }
    }*/


    //String day = rtc.dayString(currentTime);
    //day.toUpperCase();
    /*result = "";
    for(int i = 0; i < timeIndex; i++) {
        result += allInputs[i] + ",";

        /*int firstComma = dayRules[i].indexOf(",");
        if(day.indexOf(dayRules[i].substring(0, firstComma)) >= 0) {
            result += classTimes[i] + ",";
        }
        else {
            String temp = "" + dayRules[i].substring(firstComma+1);
            int secondComma = temp.indexOf(",") + firstComma;
            if(day.indexOf(dayRules[i].substring(firstComma, secondComma)) >= 0) {
                result += classTimes[i] + ",";
            }
            else if(day.indexOf(dayRules[i].substring(secondComma)) >= 0) {
                result += classTimes[i] + ",";
            }
        }*/
    /*}
    Serial.print("Events for today: ");
    Serial.println(result);*/
}

int getData(String input)
{
    //Serial.println(input);
    if(input.indexOf("MO") >= 0 || input.indexOf("TU") >= 0 || input.indexOf("WE") >= 0 || input.indexOf("TH,") >= 0 || input == "TH" || input.indexOf("FR") >= 0) {
        dayRules[timeIndex] = input;
    }
    else {
        allInputs[timeIndex] = input;
        Serial1.println(input);
        delay(1000);
        int begIndex = input.indexOf(",");
        String sub = "" + input.substring(begIndex+1);
        int endIndex = sub.indexOf(",");
        String middle = "" + input.substring(begIndex+1, begIndex+endIndex+1);
        begIndex = middle.indexOf(" ");
        sub = "" + middle.substring(begIndex+1);
        classTimes[timeIndex] = "" + sub.substring(sub.indexOf(" ")+1);
    }
    timeIndex++;
    return 1;
}

void setLEDLine(int inByte)
{
    switch (inByte) {
			case 0:
				digitalWrite(D0, HIGH); //Disable DeMUX2
				digitalWrite(D4, LOW);  //Enabale DeMUX1
				digitalWrite(D7, LOW);
				digitalWrite(D6, LOW);
				digitalWrite(D5, LOW);
				break;
			case 1:
				digitalWrite(D0, HIGH); //Disable DeMUX2
				digitalWrite(D4, LOW);  //Enabale DeMUX1
				digitalWrite(D7, LOW);
				digitalWrite(D6, LOW);
				digitalWrite(D5, HIGH);
				break;
			case 2:
				digitalWrite(D0, HIGH); //Disable DeMUX2
				digitalWrite(D4, LOW);  //Enabale DeMUX1
				digitalWrite(D7, LOW);
				digitalWrite(D6, HIGH);
				digitalWrite(D5, LOW);
				break;
			case 3:
				digitalWrite(D0, HIGH); //Disable DeMUX2
				digitalWrite(D4, LOW);  //Enabale DeMUX1
				digitalWrite(D7, HIGH);
				digitalWrite(D6, HIGH);
				digitalWrite(D5, HIGH);
				break;
			case 4:
				digitalWrite(D0, HIGH); //Disable DeMUX2
				digitalWrite(D4, LOW);  //Enabale DeMUX1
				digitalWrite(D7, HIGH);
				digitalWrite(D6, LOW);
				digitalWrite(D5, LOW);
				break;
			case 5:
				digitalWrite(D4, HIGH); //Disable DeMUX1
				digitalWrite(D0, LOW);  //Enable DeMUX2
				digitalWrite(D3, LOW);
				digitalWrite(D2, LOW);
				digitalWrite(D1, LOW);
				break;
			case 6:
				digitalWrite(D4, HIGH); //Disable DeMUX1
				digitalWrite(D0, LOW);  //Enable DeMUX2
				digitalWrite(D3, LOW);
				digitalWrite(D2, LOW);
				digitalWrite(D1, HIGH);
				break;
			case 7:
				digitalWrite(D4, HIGH); //Disable DeMUX1
				digitalWrite(D0, LOW);  //Enable DeMUX2
				digitalWrite(D3, LOW);
				digitalWrite(D2, HIGH);
				digitalWrite(D1, LOW);
				break;
			case 8:
				digitalWrite(D4, HIGH); //Disable DeMUX1
				digitalWrite(D0, LOW);  //Enable DeMUX2
				digitalWrite(D3, HIGH);
				digitalWrite(D2, HIGH);
				digitalWrite(D1, HIGH);
				break;
			case 9:
				digitalWrite(D4, HIGH); //Disable DeMUX1
				digitalWrite(D0, LOW);  //Enable DeMUX2
				digitalWrite(D3, HIGH);
				digitalWrite(D2, LOW);
				digitalWrite(D1, LOW);
				break;
			default:
				// turn all the LEDs off:
				digitalWrite(D4, HIGH);  //Disable DeMUX1
				digitalWrite(D0, HIGH);  //Disable DeMUX2
				digitalWrite(D7, LOW);
				digitalWrite(D6, LOW);
				digitalWrite(D5, LOW);
      }
}
