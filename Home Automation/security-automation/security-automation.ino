//Debadri Dutta's Code

const int trigPin = 2;
const int echoPin = 4;
 
int minSecsBetweenEmails = 60; // 1 min interval b/w emails
 
long lastSend = -minSecsBetweenEmails * 1000l;
int distance=0;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(6,OUTPUT); //buzzer
   Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, cm;
   long now = millis();
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  Serial.println(distance);
  delay(1000);
  if(distance<10)
    {
      digitalWrite(6, HIGH); 
      if (now > (lastSend + minSecsBetweenEmails * 1000l))
    {
      Serial.println("Doorstep Detection");
      lastSend = now;
    }
    else
    {
      Serial.println("");
  }

    }
    else
    {digitalWrite(6,LOW);}
 delay(1000);

}


