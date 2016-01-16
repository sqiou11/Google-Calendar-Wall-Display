void setup() {
	// initialize serial communication:
	Serial.begin(9600);
	pinMode(13, OUTPUT); //DeMUX1 ENABLE ACTIVE LOW
	pinMode(14, OUTPUT); //DeMUX1 A
	pinMode(15, OUTPUT); //DeMUX1 B
	pinMode(16, OUTPUT); //DeMUX1 C

	pinMode(11, OUTPUT); //DeMUX1 ENABLE ACTIVE LOW
	pinMode(17, OUTPUT); //DeMUX2 A
	pinMode(18, OUTPUT); //DeMUX2 B
	pinMode(19, OUTPUT); //DeMUX2 C

	pinMode(6, OUTPUT); //PWM TEST SIGNAL
	pinMode(5, OUTPUT); //PWM TEST SIGNAL
}

void loop() {
	for (int i = 0; i < 256; i++)
	{
		analogWrite(6, i);
		analogWrite(5, i);

		// read the sensor:
		if (Serial.available() > 0) {
			int inByte = Serial.read();

			switch (inByte) {
			case '0':
				digitalWrite(11, HIGH); //Disable DeMUX2
				digitalWrite(13, LOW);  //Enabale DeMUX1
				digitalWrite(14, LOW);
				digitalWrite(15, LOW);
				digitalWrite(16, LOW);
				break;
			case '1':
				digitalWrite(11, HIGH); //Disable DeMUX2
				digitalWrite(13, LOW);  //Enabale DeMUX1
				digitalWrite(14, LOW);
				digitalWrite(15, LOW);
				digitalWrite(16, HIGH);
				break;1
			case '2':
				digitalWrite(11, HIGH); //Disable DeMUX2
				digitalWrite(13, LOW);  //Enabale DeMUX1
				digitalWrite(14, LOW);
				digitalWrite(15, HIGH);
				digitalWrite(16, LOW);
				break;
			case '3':
				digitalWrite(11, HIGH); //Disable DeMUX2
				digitalWrite(13, LOW);  //Enabale DeMUX1
				digitalWrite(14, HIGH);
				digitalWrite(15, HIGH);
				digitalWrite(16, HIGH);
				break;
			case '4':
				digitalWrite(11, HIGH); //Disable DeMUX2
				digitalWrite(13, LOW);  //Enabale DeMUX1
				digitalWrite(14, HIGH);
				digitalWrite(15, LOW);
				digitalWrite(16, LOW);
				break;
			case '5':
				digitalWrite(13, HIGH); //Disable DeMUX1
				digitalWrite(11, LOW);  //Enable DeMUX2
				digitalWrite(17, LOW);
				digitalWrite(18, LOW);
				digitalWrite(19, LOW);
				break;
			case '6':
				digitalWrite(13, HIGH); //Disable DeMUX1
				digitalWrite(11, LOW);  //Enable DeMUX2
				digitalWrite(17, LOW);
				digitalWrite(18, LOW);
				digitalWrite(19, HIGH);
				break;
			case '7':
				digitalWrite(13, HIGH); //Disable DeMUX1
				digitalWrite(11, LOW);  //Enable DeMUX2
				digitalWrite(17, LOW);
				digitalWrite(18, HIGH);
				digitalWrite(19, LOW);
				break;
			case '8':
				digitalWrite(13, HIGH); //Disable DeMUX1
				digitalWrite(11, LOW);  //Enable DeMUX2
				digitalWrite(17, HIGH);
				digitalWrite(18, HIGH);
				digitalWrite(19, HIGH);
				break;
			case '9':
				digitalWrite(13, HIGH); //Disable DeMUX1
				digitalWrite(11, LOW);  //Enable DeMUX2
				digitalWrite(17, HIGH);
				digitalWrite(18, LOW);
				digitalWrite(19, LOW);
				break;
			default:
				// turn all the LEDs off:
				digitalWrite(13, HIGH);  //Disable DeMUX1
				digitalWrite(11, HIGH);  //Disable DeMUX2
				digitalWrite(14, LOW);
				digitalWrite(15, LOW);
				digitalWrite(16, LOW);
			}
		}
		delay(10);
	}
}
