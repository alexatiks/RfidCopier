/** FUNCTIONS FOR SERIAL COMMUNICATION USING UART */

#ifndef UART_H
#define UART_H
#define TX_NEWLINE {transmitByte(0x0d); transmitByte(0x0a);}

/** Function to receive a single byte */
unsigned char receiveByte(void);

/** Function to transmit a single byte */
void transmitByte(unsigned char);

/** Function to transmit hex format data */
void transmitHex(unsigned char dataType, unsigned long data);

/** Function to transmit a string in Flash */
void transmitString_F(char *);

/** Function to transmit a string in RAM */
void transmitString(unsigned char *);

#endif
