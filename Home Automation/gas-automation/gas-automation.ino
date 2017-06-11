//Debadri Dutta's Code

int minSecsBetweenEmails = 60; // 1 min interval b/w emails
 
long lastSend = -minSecsBetweenEmails * 1000l;

int buzzer = 10;
int smokeA0 = A0;

// Your threshold value. You might need to change it.
int sensorThres = 200;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  long now = millis();
  int analogSensor = analogRead(smokeA0);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(buzzer,HIGH);
    if (now > (lastSend + minSecsBetweenEmails * 1000l))
    {
   Serial.println("Gas leakage detected");
      lastSend = now;
    }
    else
    {
      Serial.println("");
    }
  }
  else
  {
    noTone(buzzer);
     Serial.println("Clean");
  }
  delay(1000);
}
