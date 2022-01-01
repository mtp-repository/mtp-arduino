
#define PWMA 9 
#define DIRA 8 
#define PWMB 6 
#define DIRB 7 
#define MOTOR_GO_FORWARD  {digitalWrite(DIRA,HIGH);analogWrite(PWMA,250);digitalWrite(DIRB,HIGH);analogWrite(PWMB,250);}
#define MOTOR_GO_BACK	  {digitalWrite(DIRA,LOW);analogWrite(PWMA,250);digitalWrite(DIRB,LOW);analogWrite(PWMB,250);}
#define MOTOR_GO_LEFT	  {digitalWrite(DIRA,LOW);analogWrite(PWMA,250);digitalWrite(DIRB,HIGH);analogWrite(PWMB,250);}
#define MOTOR_GO_RIGHT	  {digitalWrite(DIRA,HIGH);analogWrite(PWMA,250);digitalWrite(DIRB,LOW);analogWrite(PWMB,250);}
#define MOTOR_GO_STOP	  {digitalWrite(DIRA,LOW);analogWrite(PWMA,0);digitalWrite(DIRB,LOW);analogWrite(PWMB,0);}
#define MAX_PACKETSIZE 32  
char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;
enum DN
{ 
	GO_ADVANCE, 
	GO_LEFT, 
	GO_RIGHT,
	GO_BACK,
	STOP_STOP,
	DEF
}Drive_Num=DEF;

bool flag1=false;
bool stopFlag = true;
bool JogFlag = false;
uint16_t JogTimeCnt = 0;
uint32_t JogTime=0;

void CAR_Control()
{
	switch (Drive_Num) 
    {
      case GO_ADVANCE:MOTOR_GO_FORWARD;JogFlag = true;JogTimeCnt = 1;JogTime=millis();break;
      case GO_LEFT: MOTOR_GO_LEFT;JogFlag = true;JogTimeCnt = 1;JogTime=millis();break;
      case GO_RIGHT:MOTOR_GO_RIGHT;JogFlag = true;JogTimeCnt = 1;JogTime=millis();break;
      case GO_BACK:MOTOR_GO_BACK;JogFlag = true;JogTimeCnt = 1;JogTime=millis();break;
      case STOP_STOP: MOTOR_GO_STOP;JogTime = 0;JogFlag=false;stopFlag=true;break;
      default:break;
    }
    Drive_Num=DEF;

    if(millis()-JogTime>=210)
    {
      JogTime=millis();
      if(JogFlag == true) 
      {
        stopFlag = false;
        if(JogTimeCnt <= 0) 
        {
          JogFlag = false; stopFlag = true;
        }
        JogTimeCnt--;
      }
      if(stopFlag == true) 
      {
        JogTimeCnt=0;
        MOTOR_GO_STOP;
      }
    }
}

void UART_Control()
{
	char Uart_Date=0;
	if(Serial.available())
	{
		size_t len = Serial.available();
		uint8_t sbuf[len + 1];
		sbuf[len] = 0x00;
		Serial.readBytes(sbuf, len);
		//parseUartPackage((char*)sbuf);
		memcpy(buffUART + buffUARTIndex, sbuf, len);
		buffUARTIndex += len;
		preUARTTick = millis();
		if(buffUARTIndex >= MAX_PACKETSIZE - 1) 
		{
		  buffUARTIndex = MAX_PACKETSIZE - 2;
		  preUARTTick = preUARTTick - 200;
		}
	}
	if(buffUARTIndex > 0 && (millis() - preUARTTick >= 100))
	{ //data ready
		buffUART[buffUARTIndex] = 0x00;
		if((buffUART[0]=='C') && (buffUART[1]=='M') && (buffUART[2]=='D'))
	    {
	    	;
	    }
		else Uart_Date=buffUART[0];
    	buffUARTIndex = 0;
    }
    switch (Uart_Date) 
	{
		case '2': Drive_Num=GO_ADVANCE;break;
		case '4': Drive_Num=GO_LEFT; break;
		case '6': Drive_Num=GO_RIGHT; break;
		case '8': Drive_Num=GO_BACK; break;
		case '5': Drive_Num=STOP_STOP;break;
		default:break;
	}
}

void IO_init()
{
	pinMode(PWMA, OUTPUT);
	pinMode(DIRA, OUTPUT);
	pinMode(PWMB, OUTPUT);
	pinMode(DIRB, OUTPUT);
	MOTOR_GO_STOP;
}
/////////////////////////////////////////////////////////////////////////////
void setup()
{
	Serial.begin(9600);
	IO_init();
}

void loop()
{
	UART_Control();
	CAR_Control();
}
