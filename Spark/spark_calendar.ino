int getData(String input);
String classTimes[25];
String dayRules[25];
int timeIndex = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("serial has started");
  Spark.function("getData", getData);
}

void loop() {
}

int getData(String input)
{
  Serial.println(input);
  if(input.indexOf("MO") > 0 || input.indexOf("TU") > 0 || input.indexOf("WE") > 0 || input.indexOf("TH") > 0 || input.indexOf("FR") > 0) {
    dayRules[timeIndex] = input;
  }
  else {
    int begIndex = input.indexOf(",");
    String sub = "" + input.substring(begIndex+1);
    int endIndex = sub.indexOf(",");
    String middle = "" + input.substring(begIndex+1, begIndex+endIndex+1);
    begIndex = middle.indexOf(" ");
    sub = "" + middle.substring(begIndex+1);
    classTimes[timeIndex] = "" + sub.substring(sub.indexOf(" ")+1);
    Serial.println(classTimes[timeIndex]);
  }
  timeIndex++;
  return 1;
}
