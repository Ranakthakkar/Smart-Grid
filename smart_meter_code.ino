#include <LiquidCrystal.h>
LiquidCrystal Lcd(8,9,10,11,12,13);


const byte interruptPin = 2;
#define bulb 6
int bulbread;

int p=0; 
int b=0;
unsigned int bal=100;

void displaypval(int d)
{
  unsigned int temparray[3],temp;
  for(temp=3;temp>0;temp--)
  {
    temparray[temp-1]= d%10;
    d=d/10;  
  }
  
  for(temp=0;temp<3;temp++)
  {
   Lcd.print(temparray[temp]);
   delay(50);  
  }
}

void InitialSerialSetup() {
  Serial.print("ATE0");
  Serial.write(13);
  Serial.write(10);
  delay(700);
  Serial.print("AT+CWMODE=3");
  Serial.write(13);
  Serial.write(10);
  delay(700);
  Serial.print("AT+CWJAP=\"");
  Serial.print("ADMIN123");
  Serial.print("\",\"");
  Serial.print("ADMIN123");
  Serial.print("\"");
  Serial.write(13);
  Serial.write(10);
  delay(1000);
}




void data_uploading(unsigned int sensor1 ,unsigned int sensor2)
{
  Serial.print("AT+CIPSTART=4,\"TCP\",\"www.techpacs.com\",80");              //disbale echo
  Serial.write(13);
  Serial.write(10); 
  delay(1000);  
  Serial.print("AT+CIPSEND=4,119");
  Serial.write(13);
  Serial.write(10); 
  delay(1000);
  Serial.print("GET http://iot.techpacs.com/para_records.php?kid=K_45478&par=_ms1");
  Serial.print(sensor1);
  Serial.print("_2");
  Serial.print(sensor2);
  Serial.print(" HTTP/1.1\r\nHost: www.hostgator.com\r\n\r\n\r\n");
  delay(2000); 
  }


void setup()
{
  Serial.begin(115200);   
  pinMode(bulb,OUTPUT);
  digitalWrite(bulb,HIGH);
  attachInterrupt(0,Inc1,FALLING);
  Lcd.begin(16,2);      //welcome msg
  Lcd.setCursor(0,0);       
  Lcd.print("IOT Based Energy");
  Lcd.setCursor(0,1);
  Lcd.print("Prepaid Meter ");
  InitialSerialSetup();
  delay(3000);
  Lcd.clear(); 
  
  }

void loop() 
{ 
  if(bal<=0)
    {
     digitalWrite(bulb,HIGH);
    }
    else
    {
      digitalWrite(bulb,LOW);
    }
     Lcd.setCursor(0,0);       
     Lcd.print("Consumed Ut:");
     Lcd.setCursor(13,0);       
     Lcd.print(b);
     Lcd.setCursor(0,1);       
     Lcd.print("Balance: ");
     Lcd.setCursor(9,1);
     displaypval(bal);
       
   if(p==3)
   {             
     p=0;    
     b=b+1;
     bal=bal-5;    
     if(bal<=0)
     {
      digitalWrite(bulb,HIGH);
      }           
     delay(100);     
    }  
     
     Lcd.setCursor(0,0);       
     Lcd.print("Consumed Ut:");
     Lcd.setCursor(13,0);       
     Lcd.print(b);
     Lcd.setCursor(0,1);       
     Lcd.print("Balance: ");
     Lcd.setCursor(9,1);
     displaypval(bal);
    
    delay(3000);
     
}

void Inc1()
{
  p++;
  }
