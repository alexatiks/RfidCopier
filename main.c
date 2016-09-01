#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include "ili9320.h"
#include "uart.h"

#define T_POLL 0

#define FOSC 16000000// Clock Speed
#define BAUD 38400 //
#define MYUBRR FOSC/16/BAUD-1

float maxVoltageLevel = 0.25;
float minVoltageLevel = 0.1;
float currentVoltageLevel;


int adcData;

uint x = 10;
uint y = 30;
uchar string[16];
uint i = 0;
uint last = 1;
bool bol = false;
uint ci = 0;
uint count = 0;
uint tim = 0;


/* Generating a PWM frequency 125 kHz */
void init_pwm(void) {
    TCCR2 = 0;
    TCCR2 = (0 << COM01) | (1 << COM00) | (1 << WGM01) | (0 << WGM00);
    TCNT2 = 0;
    OCR2 = 63;
    TIMSK = 0;
    TCCR2 |= (0 << CS02) | (0 << CS01) | (1 << CS00);
}

void setup() {
    TCCR0 = 0;
    TCCR0 = (0 << WGM01) | (0 << WGM00);
    TCNT0 = T_POLL;
    TIFR = (1 << TOV0);
    TIMSK |= (1 << TOIE0);
    TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);
}

ISR (TIMER0_OVF_vect) {
    TCNT0 = T_POLL;
    //LCD_PutPixel(x,y-10,0x0000);
}

void USART_Init(unsigned int ubrr) {
/* Set baud rate */
    UBRRH = (unsigned char) (ubrr >> 8);
    UBRRL = (unsigned char) ubrr;
/* Enable receiver and transmitter */
    UCSRB = (1 << RXEN) | (1 << TXEN);
/* Set frame format: 8data, 1stop bit */
    UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

/* Print pulses into display */
void printPulsesDisplay() {
    while (1) {
        //LCD_clear(0xFFFF);
        ADCSRA |= 0x40;
        adcData = ADCW;
        currentVoltageLevel = 3.16 - (float) adcData * 0.003088;
        //sprintf(string, "%1.2f", v);
        //LCD_DrawString(string,60,60,0x00FF);
        //LCD_PutPixel(x, y - v * 100, 0x00FF);
        //x += 4;

        if (currentVoltageLevel > maxVoltageLevel)
            LCD_PutPixel(x, y - 20, 0x00FF);
        if (currentVoltageLevel < minVoltageLevel)
            LCD_PutPixel(x, y, 0x00FF);
        x++;

        if (x > 320) {
            x = 0;
            y = y + 40;
            //break;
        }
        if (y > 220) {
            //		LCD_clear(0xFFFF);
            x = 0;
            y = 20;
            ///	}
            //break;
        }
    }
}

/* Wait while voltage level changes, value - current voltage level */
void change(bool value) {
    while (1) {
        ADCSRA |= 0x40;
        adcData = ADCW;
        currentVoltageLevel = 3.16 - (float) adcData * 0.003088;
        if (value == 0 & currentVoltageLevel > maxVoltageLevel)
            bol = true;
        if (value == 1 & currentVoltageLevel < minVoltageLevel)
            bol = true;
        if (bol & value == 0 & currentVoltageLevel > maxVoltageLevel | bol & value == 1 & currentVoltageLevel < minVoltageLevel) {
            bol = false;
            break;
        }
    }
}

int main(void) {
    init_IO();
    init_pwm();

    ACSR = 0x80;
    SFIOR = 0x00;
    ADMUX = 0b01000000;
    ADCSRA = 0x85;

    setup();
    USART_Init(MYUBRR);
    sei();

    TX_NEWLINE;
    transmitString_F(PSTR("Start"));
    TX_NEWLINE;

    find_long_path:
    last = 1;
    TCNT0 = T_POLL;
    i = 0;
    ci = 0;
    change(0);
    tim = TCNT0;
    TCNT0 = T_POLL;
    change(1);
    count = TCNT0;
    if (count >= 20 & count <= 40) //280..560 20..40
    {}
    else
        goto find_long_path;

    goto first;

    find:
    change(1);
    change(0);
    tim = TCNT0;
    TCNT0 = 0;
    first:

    string[ci] <<= 1;

    if (tim >= 28 & tim <= 38)//32 28..38
    {
        if (last == 0) {
            string[ci] &= ~(1 << 0);
            last = 0;
        } else if (last == 1) {
            string[ci] |= (1 << 0);
            last = 1;
        }
        i++;
    } else if (tim >= 40 & tim <= 57) //53
    {
        if (last == 0) {
            string[ci] |= (1 << 0);
            i++;
            last = 1;
        } else if (last == 1) {
            string[ci] &= ~(1 << 0);
            i++;
            string[ci] <<= 1;
            string[ci] &= ~(1 << 0);
            i++;
            last = 0;
        }
    } else if (tim >= 60 & tim <= 68) //64 60..68
    {
        string[ci] &= ~(1 << 0);
        i++;
        string[ci] <<= 1;
        string[ci] |= (1 << 0);
        i++;
        last = 1;
    } else {
        goto find_long_path;

    }

    if (i % 7 == 0) {
        ci++;
    }

    if (i >= 127)
        goto end;
    goto find;

    end:
    TX_NEWLINE;
    for (int op = 0; op <= ci; op++) {
        transmitHex(CHAR, string[op]);
    }


    TX_NEWLINE;
    transmitString_F(PSTR("Finish"));
    return 0;
}