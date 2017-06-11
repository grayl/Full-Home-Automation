//Debadri Dutta's code
#define esp Serial
 
#define led 9

#define BUFFER_SIZE 1000
char buffer[BUFFER_SIZE];
 
void send_at(String x)
{
  esp.println(x);
}
 
void setup(){
 
 
pinMode(led, OUTPUT);
delay(2000);
esp.begin(115200);
esp.println("AT");
delay(1000);
esp.println("AT+CWMODE=3");
delay(1000);
esp.println("AT+CIPMUX=1");
delay(1000);
esp.println("AT+CIPSERVER=1,80");
delay(1000);
esp.println("AT+CIFSR");
delay(1000);
}
 
bool read_till_eol() {
  static int i=0;
  if(esp.available()) {
    char c=esp.read();
    buffer[i++]=c;
    if(i==BUFFER_SIZE)  i=0;
    if(i>1 && buffer[i-2]==13 && buffer[i-1]==10) {
      buffer[i]=0;
      i=0;
      return true;
    }
  }
  return false;
}
 
void loop()
{
  int ch_id, packet_len;
  char *pb;  
  if(read_till_eol()) {
    if(strncmp(buffer, "+IPD,", 5)==0) {
      // request format: +IPD,ch,len:data
      sscanf(buffer+5, "%d,%d", &ch_id, &packet_len);
      if (packet_len > 0) {
        pb = buffer+5;
        while(*pb!=':') pb++;
        pb++;
        if (strncmp(pb, "GET / ", 6) == 0) 
        {
         serve_homepage(ch_id,0);
         }
          else if (strncmp(pb, "GET /?on", 8) == 0)
          {
               on();
               serve_homepage(ch_id,1);
               }
          else if(strncmp(pb, "GET /?off", 9) == 0)
          {
               off();
               serve_homepage(ch_id,2);
 
           }
  }
}
}}
 
void serve_homepage(int ch_id, byte state)
{
         
          esp.print(F("AT+CIPSEND="));
          esp.print(ch_id);
          esp.print(",");
          
          esp.println("512");
          delay(500);
 
          esp.print("HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n<HTML><HEAD><TITLE>LIGHT CONTROLLER</TITLE></HEAD><BODY><font size=\"3\"><center>WELCOME TO THE WEB INTERFACE OF CONTROLLING ELECTRICAL APPLIANCES OVER WIFI<hr /><br /><br />");
 
          esp.print("<font size=\"20\"><p><a href=\"/?on\"\">ON</a></p><a href=\"/?off\"\"><center>OFF</center></a>&nbsp;&nbsp;&nbsp;&nbsp;</BODY></HTML>");
          delay(1000);
 
          esp.print(F("AT+CIPCLOSE="));
          esp.println(ch_id);
}
 
void on()
{
  digitalWrite(led,HIGH);
}
void off()
{
  digitalWrite(led,LOW);
}
