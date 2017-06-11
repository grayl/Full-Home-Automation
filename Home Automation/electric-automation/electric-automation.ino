//Debadri Dutta's Code
const int ldr = A0; 
float val=0;
void setup() {
  // put your setup code here, to run once:
pinMode(3,OUTPUT);
pinMode(ldr, INPUT);
digitalWrite(A0, HIGH);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
val=1023-analogRead(ldr);
Serial.println(val);
delay(100);
if(val<200)
{
  digitalWrite(3,HIGH);
}
else
{
  digitalWrite(3,LOW);
}
}
