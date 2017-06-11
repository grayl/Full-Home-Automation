//Debadri Dutta's Code
int flamePin = 5;
 
int minSecsBetweenEmails = 60; // 1 min interval b/w emails
 
long lastSend = -minSecsBetweenEmails * 1000l;
 
void setup()
{
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
}
 
void loop()
{
  long now = millis();
  if (digitalRead(flamePin) == HIGH)
  {
    if (now > (lastSend + minSecsBetweenEmails * 1000l))
    {
      Serial.println("Fire Detected");
      lastSend = now;
    }
    else
    {
      Serial.println("");
    }
  }
  delay(500);
}
