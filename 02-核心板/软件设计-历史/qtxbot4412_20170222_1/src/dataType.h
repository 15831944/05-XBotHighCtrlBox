#ifndef __DATATYPE_H__
#define __DATATYPE_H__

// place your code here

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#ifdef __arm
    #define ARM_PACKED	__packed
#else
    #define ARM_PACKED
#endif

#pragma pack(1)

typedef ARM_PACKED union 
{
	ARM_PACKED struct
	{
		uint8_t head;
	    uint8_t command;
	    uint8_t commandData0;    //
	    uint8_t commandData1;     //����B
	    uint8_t commandData2;
	    uint8_t commandData3;
	    uint8_t commandData4;
	    uint8_t commandData5;
	    uint8_t commandData6;
	    uint8_t commandData7;
	    uint8_t commandData8;
	    uint8_t commandData9;
	    uint8_t commandData11;
	    uint8_t commandData12;
	    uint8_t checkSum;   	       
	}controlData;
	char byte[15];
	
}SendFrame;

typedef ARM_PACKED union 
{
	ARM_PACKED struct
	{
		uint8_t head;
	    uint8_t command;
	    uint8_t keyA;     //����A
	    uint8_t keyB;     //����B
	    uint8_t keyE;
	    uint8_t keyF;
	    uint8_t keyHM;
	    uint8_t keyIJG;
	    uint8_t joyStickLeftX;
	    uint8_t joyStickLeftY;
	    uint8_t joyStickRightX;
	    uint8_t joyStickRightY;
	    uint8_t ctrlBoxPower1;
	    uint8_t ctrlBoxPower2;
	    uint8_t checkSum;   	       
	}keyData;
	ARM_PACKED struct
	{
		uint8_t head;
	    uint8_t command;
	    uint8_t feedIndex;     //
	    uint8_t leftMoveSpeed;     //
	    uint8_t rightMoveSpeed;
	    uint8_t feedData1;
	    uint8_t feedData2;
	    uint8_t feedData3;
	    uint8_t feedData4;
	    uint8_t feedData5;
	    uint8_t feedData6;
	    uint8_t reserve1;
	    uint8_t reserve2;
	    uint8_t reserve3;
	    uint8_t checkSum;   	       
	}robotData;
	char byte[15];
	
}ReceiveFrame;


#pragma pack()




#endif // __DATATYPE_H__
