int x, y, z, t, a, b;
char buffer [100];
void setup()
{

	Serial.begin(115200);

}

void loop()
{

	for (int i = 0; i < 2556; i++)
	{
		x = i;
		y = i;
		z = i;
		t = i;
		a = i;
		b = i;
		
		sprintf(buffer, "%d,%d,%d,%d,%d,%d", x, y, z, t, a, b);
		Serial.println(buffer);
		delay(100);

		//Serial.print("%d,%d,%d,%d,%d,%d/n", x,y,z,t,a,b);
		//printf("%d,%d,%d,%d,%d,%d", x, y, z, t, a, b);
	}
	

}
