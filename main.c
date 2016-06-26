#include <util/delay.h>
#include <avr/interrupt.h>
#include "ili9320.h"

#define T_POLL 0//132//140//165

float max = 0.25;
float min = 0.1;

int data;
float v;
int x=10;
int y=30;
char string[129];
int i=0;
int last=1;
int bol=0;
int b;
uint k=0;
uint flag=0;

//��������-���������� �������� 125khz
void init_pwm (void){
    TCCR2 = 0;
    TCCR2 = (0<<COM01)|(1<<COM00)|(1<<WGM01)|(0<<WGM00);
    TCNT2 = 0;
    OCR2 = 63;
    TIMSK = 0;
    TCCR2 |= (0<<CS02)|(0<<CS01)|(1<<CS00);
}

//��������� ������� ��� �������� ��������� � �������
void setup(){
    TCCR0 = 0;
    TCCR0 = (0<<WGM01)|(0<<WGM00);
    TCNT0 = T_POLL;
    TIFR = (1<<TOV0);
    TIMSK |= (1<<TOIE0);
    TCCR0 |= (1<<CS02)|(0<<CS01)|(0<<CS00);
}

ISR (TIMER0_OVF_vect){
    TCNT0 = T_POLL;
    //LCD_PutPixel(x,y-10,0x0000);
}

//����� ��������� �� �������
int print_rfid(){
    while (1)
    {
        //LCD_clear(0xFFFF);
        ADCSRA |= 0x40;
        data = ADCW;
        v = 3.16;//3.16-(float) data*0.003088;
        //sprintf(string, "%1.2f", v);
        //LCD_DrawString(string,60,60,0x00FF);
        LCD_PutPixel(x,y-v*100,0x00FF);
        x+=4;
/*
		if (v>max)
			LCD_PutPixel(x,y-20,0x00FF);
		if (v<min)
			LCD_PutPixel(x,y,0x00FF);*/
        x++;

        if (x>320)
        {//x=0;
            //y=y+40;
            break;
        }
        if(y>220){
            //		LCD_clear(0xFFFF);
            //		x=0;
            //		y=20;
            ///	}
            break;}
    }

}


int change(int value){ //���������� 1, ���� ���� ��������� ����������; value - ������� ���������
    ADCSRA |= 0x40;
    data = ADCW;
    v = 3.16-(float) data*0.003088;
    if (value==0 & v>max)
        bol=1;
    if (value==1 & v<min)
        bol=1;
    if (bol==1 & value==0 & v>max |bol==1 & value==1 & v<min){
        bol=0;
        return 1;}
    return 0;
}

int main(void){
    init_IO();
    LED_OFF;
    LCD_reset();
    LCD_init();
    init_pwm();

    ACSR=0x80;
    SFIOR=0x00;
    ADMUX = 0b01000000;
    ADCSRA = 0x85;

    uint count=0;
    uint tim = 0;
    setup();
    sei();

    find_long_path:
    last=1;
    TCNT0 = T_POLL;
    i=0;
    while(change(0)==0){}//������� ��������� �� 1
    tim = TCNT0;
    TCNT0 = T_POLL;
    while(change(1)==0){}//������� �������� �� 0
    count = TCNT0;
    if (count>=20 &count <=40) //280..560
    {}
    else
        goto find_long_path;

    //���������������!
    goto first;

    find:
    while(change(1)==0){};
    while(change(0)==0){};
    tim = TCNT0;
    TCNT0=0;
    first:
    if(tim>=28 & tim<=38)//32
    {
        if(last==0)
        {
            string[i]='0';
            last=0;
        }
        else
        if(last==1)
        {
            string[i]='1';
            last=1;
        }
        i++;
    }
    else
    if(tim>=40 & tim<=57) //53
    {
        if(last==0)
        {
            string[i]='1';
            i++;
            last=1;
        }
        else
        if(last==1)
        {
            string[i]='0';
            i++;
            string[i]='0';
            i++;
            last=0;
        }
    }
    else
    if(tim>=60&tim<=68) //64
    {
        string[i]='0';
        i++;
        string[i]='1';
        i++;
        last=1;
    }
    else
    {
        goto find_long_path;

    }

    if(i>=129)
        goto end;
    goto find;

    end:
    LCD_DrawString(string,x,y,0x00FF);
    goto kol;
    k=0;
    for(int i=0;i<=129;i++)
    {
        if(string[i]=='1')
        {
            k++;
        }
        else
        {
            k=0;
        }
        if(k==9)
        {
            for(int l=0;l<9;l++)
            {
                LCD_DrawChar(x,y,'1',0x00FF);
                x+=7;
            }
            for(int l=i+1;l<i+56;l++){
                LCD_DrawChar(x,y,string[l],0x00FF);
                x+=7;
                if (x>320)
                {x=5;
                    y=y+20;
                }
            }

            goto kol;
        }
    }
    goto find_long_path;

    kol:
    LED_ON;
    _delay_ms(200);
    LED_OFF;
    _delay_ms(1000);
    LCD_clear(0xffff);
    _delay_ms(1000);
    x=10;
    y=30;

    goto find_long_path;
}