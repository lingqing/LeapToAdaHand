/*  Open Bionics - FingerLib Example - SingleFinger
* Author - Olly McBride
* Date - October 2015
*
* This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
* 
* Website - http://www.openbionics.com/
* GitHub - https://github.com/Open-Bionics
*/

#include <FingerLib.h>

//#define MYSERIAL Serial
#define BUF_SIZE 100
/*
 * WHAT IT DOES
 * Uses the FingerLib.h library to open and close a single finger every 2 seconds
 * 
 */
// typedef
typedef struct FingerAngle{
    char type;
    char valid;
    uint16_t angle;
}FingerAngle;
typedef struct Com_Frame{
    char Tag;
    char type;
    uint16_t lenth;
    char data[20];
    char End[2];
}Com_Frame;

/* ----------- local varity ------------------ */
// initialise Finger class to array, and assigns pins
Finger finger[5];

const Com_Frame comResp = {'a', 'r', 4,"",'5'};
Com_Frame comReadData;
char * ptrComBuf = (char*)&comReadData.Tag;
FingerAngle (* ptrFingerAngle)[5] = (FingerAngle(*)[5])&comReadData.data[0];
unsigned int angle;

char readBuf[BUF_SIZE];
int bufPos = 0;
bool comBufValid = false;

/************************************
 * 
 ***********************************/
void serialCom()
{
  // read data frome serial
  while(MYSERIAL.available()>0)
  {
    readBuf[bufPos++] = MYSERIAL.read();
    delay(2);     
    if(bufPos > BUF_SIZE)
    {
        bufPos = 0;       
    }
  }
  // anlyze the buffer
  if(bufPos  > 0)
  {
    int i = 0;
    while('a' != readBuf[i] && i++ < bufPos);
    if(i >= bufPos)
    {
      // no valid buff data  
    }
    else
    {
      if(i > 0) i = i--;  
      for(int j = 0;i < bufPos;)
      {
        ptrComBuf[j++] = readBuf[i++];  
        comBufValid = true;
      }
    }   
    bufPos = 0;
  }
}

/*************************************
 * 
 *************************************/
void driverFinger()
{
  if(comBufValid)
  {
//    char buf[20];
//    MYSERIAL.println();   
    for(unsigned int i= 0; i < 5 ; i++)
    {
      if((*ptrFingerAngle)[i].valid == 'y' && i == (*ptrFingerAngle)[i].type)
      {
        angle = (*ptrFingerAngle)[i].angle;
        if( angle > 0 && angle < 240)
        {
          if(i !=0 )
          {
            if(angle < 40) angle = 40;
            if(angle > 160) angle = 160;
            angle -= 40;
            finger[i].writePos(50 + angle * 7.7); 
          }
          else
          {
           if(angle < 0) angle = 0;
            if(angle > 70) angle = 70;            
            finger[i].writePos(50 + angle * 13.2); 
          }          
        }
      }  
    }
    delay(100);
    comBufValid = false; 
  }  
}
/*************************************
 * 
 ************************************/
void respToLeap()
{
  static int i = 0;
  static int j = 0;
  if(i++ > 10)
  {    
    MYSERIAL.write((char *)&comResp.Tag, comResp.lenth);
    i = 0;
    // monitor
    if(j ++ > 20)
    {
      for(int k = 0; k < 5; k++)
      {
        finger[k].open();
      }
      j = 0;
    }
  }    
  delay(20);
}


// set up
void setup()
{ 
  // MYSERIAL.print is used to allow compatability between both the Mega (Serial.print) 
  //and the Zero Native Port (SerialUSB.print), and is defined in FingerLib.h
  MYSERIAL.begin(38400);
 // MYSERIAL.println("Started");
  //MYSERIAL.setTimeout(100);
  // configure finger pins
  finger[0].attach(13,4,A5);          // Right motor connector
  finger[1].attach(3,6,A1);
  finger[2].attach(7,8,A2);
  finger[3].attach(10,9,A3);
  finger[4].attach(11,12,A4);  
  MYSERIAL.println("Pins configured");  
}

void loop()
{
  serialCom();
  driverFinger();
  //--------------------------- 
  // respon   
  respToLeap();
}




