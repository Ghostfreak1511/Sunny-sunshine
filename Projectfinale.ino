#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 0;
int servohLimitHigh = 180;
int servohLimitLow = 0;

Servo servoverti; 
int servov = 60; 
int servovLimitHigh = 160;
int servovLimitLow =60;
//Assigning LDRs
int ldrtopl = 2; //top left LDR green
int ldrtopr = 1; //top right LDR yellow
int ldrbotl = 3; // bottom left LDR blue
int ldrbotr = 0; // bottom right LDR orange

float vin=0.0;
float vout=0.0;
float r1=30000.0;
float r2=7500.0;
int value=0;
float voltage=0.0;


 void setup () 
 {
  servohori.attach(10);
  servohori.write(0);
  servoverti.attach(9);
  servoverti.write(0);
  Serial.begin(9600);
  delay(500);
 }

void loop()
{
  voltage=voltageread();
  float current=currentread();
  servoh = servohori.read();
  servov = servoverti.read();
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);

  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs
if (servov<90)
{
  if (avgtop < avgbot)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(15);
  }
  else if (avgbot < avgtop)
  {
    servoverti.write(servov -1);
    if (servov < servovLimitLow)
  {
    servoverti.write(servov +1);
  }
    delay(15);
  }
  
  
  if (avgleft > avgright)
  {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(15);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    delay(15);
  }
}
if (servov>=90)
{
  if (avgtop < avgbot)
  {
    servoverti.write(servov -1);
    if (servov < servovLimitLow) 
     { 
      servov = servovLimitLow;
     }
    delay(15);
  }
  else if (avgbot < avgtop)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh)
  {
    servov = servovLimitHigh;
  }
    delay(15);
  }
   if (avgleft > avgright)
  {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
    delay(15);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
    delay(15);
  }
}
  delay(50);
  Serial.print("topleft:");Serial.print(analogRead(A0));Serial.print("\t");
  Serial.print("topright:");Serial.print(analogRead(A1));Serial.print("\t");
  Serial.print("bottomleft:");Serial.print(analogRead(A2));Serial.print("\t");
  Serial.print("bottomright:");Serial.print(analogRead(A3));Serial.print("\t");
  Serial.print("current:");Serial.print(current);Serial.print("\t");
  Serial.print("voltage:");Serial.println(voltage);
}
  float currentread()
  {
   float i = (voltage/22040)*1000;
   return i;
  }
   
  
  float voltageread()
  {
    value=analogRead(A5);
    vout=(value*5.0)/1024.0;
    vin=vout/(r2/(r1+r2));
    float v=vin/3;
   return v; 
  }
  int power()
  {
   float v=voltageread();
   float i=currentread();
    int p=v*i;
    return p;
  }
  

