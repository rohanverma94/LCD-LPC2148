#include "lpc214x.h"



void IRQ_Routine (void)   __attribute__ ((interrupt("IRQ")));
void FIQ_Routine (void)   __attribute__ ((interrupt("FIQ")));
void SWI_Routine (void)   __attribute__ ((interrupt("SWI")));
void UNDEF_Routine (void) __attribute__ ((interrupt("UNDEF")));

/*
 Connections from LPC2148 to LCD Module:
 P0.0 to P0.7 used as Data bits.
 P1.16 connected to pin4 i.e. RS	- Command / Data
 P1.17 connected to pin6 i.e. E - Enable
 Pin5 of LCD Module i.e. 'R/W' connected to ground
*/	

void initLCD(void);
void enable(void);
void LCD_WriteChar(char c);
void LCD_WriteString(char * string);
void LCD_Cmd(unsigned int cmd);
void delay(void);

void delay(void)
{
	int i=0,x=0;
	for(i=0; i<20000; i++){ x++; }
}

int main(void)
{
	initLCD(); //LCD Now intialized and ready to Print!
	LCD_WriteString(".: Rohan :.");
	LCD_Cmd(0x80 + 0x40); //Come to 2nd Row
	LCD_WriteString("www.cryptecx.xyz");
	while(1); // Loop forever	 
	return 0; //This won't execute :P
}

void initLCD(void)
{
	IO0DIR = 0xFF; //P0.0 to P0.7 configured as Output - Using 8 Bit mode
	IO1DIR |= (1<<16) | (1<<17); //P1.16 and P1.17 configured as Output - Control Pins
	IO0PIN = 0x0; //Reset Port0 to 0.	
	IO1PIN = 0x0; //Reset Port1 to 0 - Which also makes RS and Enable LOW.

	//LCD Initialization Sequence Now starts
	delay(); //Initial Delay
	LCD_Cmd(0x3C); //Function Set Command : 8 Bit Mode , 2 Rows , 5x10 Font Style
	LCD_Cmd(0x0F); //Display Switch Command : Display on , Cursor on , Blink on
	LCD_Cmd(0x06); //Input Set : Increment Mode 
	LCD_Cmd(0x01); //Screen Clear Command , Cursor at Home
	LCD_Cmd(0x80); //Not required the 1st time but needed to reposition the cursor at home after Clearing Screen 
	//Done!
}

void enable(void)
{
	delay();
	IO1PIN |=  (1<<17);//Enable=High
	delay();
	IO1PIN &= ~(1<<17);//Enable=Low
	delay();
}

void LCD_WriteChar(char c)
{
	IO1PIN |= (1<<16); //Switch to Data Mode
	IO0PIN = (int) c; //Supply Character Code
	enable(); //Pulse Enable to process it
}

void LCD_WriteString(char * string)
{
	int c=0;
	while (string[c]!='\0')
	{
		LCD_WriteChar(string[c]);
		c++;
	}
}
		
void LCD_Cmd(unsigned int cmd)
{
	IO1PIN = 0x0; //Enter Instruction Mode
	IO0PIN = cmd; //Supply Instruction/Command Code
	enable(); //Pulse Enable to process it
}




/*  Stubs for various interrupts (may be replaced later)  */
/*  ----------------------------------------------------  */

void IRQ_Routine (void) {
	while (1) ;
}

void FIQ_Routine (void)  {
	while (1) ;
}


void SWI_Routine (void)  {
	while (1) ;
}


void UNDEF_Routine (void) {
	while (1) ;
}


