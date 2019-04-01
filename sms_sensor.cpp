#include <SoftwareSerial.h>
#include <string.h>

#define GAS_ALARM "Gas alarm:"
#define TEMP_ALARM "TEmp alarm:"

SoftwareSerial mySerial(9, 10);
int sendmsg = 0;
int gasFlag = 0;
int tempFlag = 0;

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(8, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  
  mySerial.println("AT+CFUN=0");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  
  mySerial.println("AT+CFUN=1,1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
}


void loop()
{
  char ptr[100], *FinalMsg;
  FinalMsg = ptr;
  
  memset(FinalMsg, 0x00, 100);
  if ((digitalRead(8) == LOW))
  {
    if (gasFlag == 0)
    {
      sendmsg = 1;
      Serial.write("Output is low");
      strncpy(FinalMsg, GAS_ALARM, strlen(GAS_ALARM));
      FinalMsg += strlen(GAS_ALARM);
      gasFlag = 1;
    }
  }
  else
  {
    gasFlag = 0;
  }

  
  if (digitalRead(7) == LOW)
  {
    if (tempFlag == 0)
    {
      sendmsg = 1;
      Serial.write("Output is low");
      strncpy(FinalMsg, TEMP_ALARM, strlen(TEMP_ALARM));
      FinalMsg += strlen(TEMP_ALARM);
      tempFlag = 1;

    }
  }
  else
  {
     tempFlag = 0;

  }

  if (sendmsg == 1)
  {
    SendMessage(ptr);
    Serial.write(ptr);
    Serial.write("\n");
  }
  delay(1000);
  sendmsg = 0;
}

void SendMessage(char *msg)
{
  mySerial.println("AT");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917907505811\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(msg);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

 
