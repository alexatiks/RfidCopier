#include "uart.h"
#include <avr/io.h>
#include <avr/pgmspace.h>

unsigned char receiveByte(void) {
    unsigned char data, status;
    while (!(UCSRA & (1 << RXC)));   // Wait for incomming data

    status = UCSRA;
    data = UDR;

    return (data);
}

void transmitByte(unsigned char data) {
    while (!(UCSRA & (1 << UDRE)));  // Wait for empty transmit buffer
    UDR = data;                          //Start transmition
}

//***************************************************
//Function to transmit hex format data
//first argument indicates type: CHAR, INT or LONG
//Second argument is the data to be displayed
//***************************************************
/*void transmitHex( unsigned char dataType, unsigned long data )
{
unsigned char count, i, temp;
unsigned char dataString[] = "0x        ";


if (dataType == CHAR) count = 2;
if (dataType == INT) count = 4;
if (dataType == LONG) count = 8;


for(i=count; i>0; i--)
{
  temp = data % 16;
  if((temp>=0) && (temp<10)) dataString [i+1] = temp + 0x30;
  else dataString [i+1] = (temp - 10) + 0x41;


  data = data/16;
}


transmitString (dataString);
}
*/

void transmitString_F(char *string) {
    while (pgm_read_byte(&(*string)))
        transmitByte(pgm_read_byte(&(*string++)));
}

void transmitString(unsigned char *string) {
    while (*string)
        transmitByte(*string++);
}
