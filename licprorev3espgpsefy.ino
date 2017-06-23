#include <LiquidCrystal.h>
#include "SoftwareSerial.h"
#include <TinyGPS.h>
int idd=0;
TinyGPS gps;
SoftwareSerial ss(13,4);
SoftwareSerial ESP8266(6, 9);
 float flat, flon;
 unsigned long age;
 bool newData = false;
 unsigned long chars;
 unsigned short sentences, failed;
String server = "192.168.43.12";
String mess="";
int p1=7;
int p2=8;
int p3=10;
int val1=0,val2=0,val3=0;
int a=0,vol=0;
int t1=0,t2=0,t3=0,br=0,y=0;
int sno=1;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() 
{
    lcd.begin(16, 2);
    lcd.print("Pressure Sensing");
    lcd.setCursor(0, 1);
    lcd.print("Along the Tracks");
Serial.begin(9600);
pinMode(p1,INPUT);
pinMode(p2,INPUT);
pinMode(p3,INPUT);
}

void reset()
{
  ESP8266.println("AT+RST");
  delay(1000);
  if(ESP8266.find("OK")) Serial.println("Module Reset");
}

void senddo(String mess2)
{ 
  Serial.println("k");
  ESP8266.begin(115200);
  String cmd;
  cmd = "AT+CIPSTART=1,\"TCP\",\"";
  delay(500);
  cmd += server;
  delay(500);
  cmd += "\",80";
  delay(500);
  ESP8266.println(cmd);
  delay(500); 
  if(ESP8266.find("OK"))
  {
    Serial.println("Connected to the web!");
  }
  ESP8266.end();
   ss.begin(9600);
   newData=false;

 while(!newData)
  {
    for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      if (gps.encode(c)) 
        newData = true;
    }
    Serial.println(newData);
  }
  }
  ss.end();
  if (newData)
  {
gps.f_get_position(&flat, &flon, &age);   
Serial.print(flat);
Serial.print("   ");
Serial.println(flon);
Serial.println(mess2);
ESP8266.begin(115200);
int sensor=1;
  cmd ="GET /pandeyji/postcoll.php?id=" + (String)idd + "&sen1=" + (String)sensor + "&sen2=" + (String)flat +  "&sen3=" + (String)flon + "HTTP/1.1\r\n"; 
  idd=idd+1;
  sno=sno+1;
  delay(500);
  cmd += "Host: 192.168.43.12\r\n\r\n";
  delay(500); 
  ESP8266.print("AT+CIPSEND=1,");
  delay(500);
  ESP8266.println(cmd.length()); 
  delay(500);
 
  if(ESP8266.find(">"))
  {
    Serial.println(">");
  }
 
  ESP8266.println(cmd);
  delay(500);
 
  if(ESP8266.find("OK"))
  {
    Serial.println("send!");
  }
ESP8266.end();
}
}

void loop() 
{
  ESP8266.begin(115200); 
  Serial.print("Start");
  reset();
  ESP8266.println("AT+CWMODE=1");
  delay(1000);
  ESP8266.println("AT+CIPMUX=1");
  delay(1000);
  ESP8266.end();
  
val1=digitalRead(p1);
val2=digitalRead(p2);
val3=digitalRead(p3);
Serial.print(val1);
Serial.print("   ");
Serial.print(val2);
Serial.print("   ");
Serial.println(val3);
  while (ss.available())
    {
      char c = ss.read();
      if (gps.encode(c)) 
        newData = true;
    }
if(val1==HIGH||val3==HIGH)
 {
  if(val1==HIGH)
     a=1;
lcd.clear();
lcd.print("1 Sensor Activated");
while(1)
{
val1=digitalRead(p1);
val2=digitalRead(p2);
val3=digitalRead(p3);
Serial.print(val1);
Serial.print("  high  ");
Serial.print(val2);
Serial.print("  high  ");
Serial.println(val3);
  t1=t1+1;
  lcd.setCursor(0,1);
  lcd.print(t1);
  if(val2==HIGH)
  {
   t2=t2+1;
   lcd.clear();
   lcd.print("Sensor 2 Activated");   
    while(1)
    {
lcd.setCursor(0, 1);
lcd.print(t2);
t2=t2+1;
val1=digitalRead(p1);
val2=digitalRead(p2);
val3=digitalRead(p3);
Serial.print(val1);
Serial.print("                 ");
Serial.print(val2);
Serial.print("                  ");
Serial.println(val3);
      if(a==1)
            vol=digitalRead(p3);
          else
            vol=digitalRead(p1);
      if(vol==HIGH)
      {        
      while(1)
      {
       t3=t3+1;
      lcd.clear();
    if(t1<100&&t2<100)
    {   
    lcd.clear();
    lcd.print("Landslide -3 ");
    mess="landslide-3";
    senddo(mess);
    lcd.setCursor(0, 1);
    lcd.print(t3);
      }
      else
      {      
    lcd.clear();
    lcd.print("animal passed ");
    mess="animal passed";
    senddo(mess);
    y=1;
    lcd.setCursor(0, 1);
    lcd.print(t3);
      }
    if(t3>500&&y==1)
    {
      y=0;
      br=1;
      break;
    }
     }  
    }
    
    if(t1<100)
    {      
    lcd.clear();
    lcd.print("landslide ");
    mess="landslide ";
    senddo(mess);
    }
    else
    {      
    lcd.clear();
    lcd.print("animal present ");
    mess="animal present";
    senddo(mess);
    }
    if(br==1)
    break;
  }
}
if(br==1)
{
  lcd.clear();
  lcd.print("Pressure Sensing");
  lcd.setCursor(0, 1);
  lcd.print("Along the Tracks");
break;
  }
}
}
t1=0;t2=0;t3=0;br=0;a=0;
}

