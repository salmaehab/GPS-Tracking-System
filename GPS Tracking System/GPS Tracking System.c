#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "D:/Keil/Arm/INC/TI/tm4c123gh6pm.h"
#define GPIO_PA10_M 0x03
#define M_PI 3.14159265358979323846

// Port init

void SystemInit() {}
uint32_t delay;
int count = 0;
void init(void){
	//PORT F 
	SYSCTL_RCGCGPIO_R |= 0x20;
	delay =1 ;
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_PCTL_R = 0;
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R = 0x1F;
	GPIO_PORTF_PUR_R = 0x11;


	//port D

	SYSCTL_RCGCGPIO_R |= 0x08;
	delay = 1;

	GPIO_PORTD_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_CR_R = 0xFF;
	GPIO_PORTD_AFSEL_R = 0xF0;
	GPIO_PORTD_PCTL_R = 0x11110000;
	GPIO_PORTD_AMSEL_R = 0;
	GPIO_PORTD_DIR_R = 0xA0;
	GPIO_PORTD_DEN_R = 0xFF;
	
	
	//port B
	SYSCTL_RCGCGPIO_R |= 0x02;
	delay =1 ;
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R = 0xFF;
	GPIO_PORTB_AFSEL_R = 0;
	GPIO_PORTB_PCTL_R = 0;
	GPIO_PORTB_AMSEL_R = 0;
	GPIO_PORTB_DIR_R = 0xFF;
	GPIO_PORTB_DEN_R = 0xFF;
	//GPIO_PORTB_DATA_R = 0x01;


	
	//port A clock (usb)
	SYSCTL_RCGCGPIO_R |= 0x01;
	delay = 1;
	
	
	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_CR_R = 0xFF;
	GPIO_PORTA_AFSEL_R = 0x03;
	GPIO_PORTA_PCTL_R = 0x00000011;
	GPIO_PORTA_AMSEL_R = 0;
	GPIO_PORTA_DIR_R = 0xE2;
	GPIO_PORTA_DEN_R = 0xFF;
}



//SYSTICK TIMER
//systick timer

void SysTick_Wait(uint32_t delay)
{ 
    NVIC_ST_CTRL_R = 0;            /* (1) disable SysTick during setup */
    NVIC_ST_RELOAD_R = delay-1;    /* (2) number of counts to wait */
    NVIC_ST_CURRENT_R = 0;         /* (3) any value written to CURRENT clears */
    NVIC_ST_CTRL_R |= 0x5;         /* (4) enable SysTick with core clock */
 
    while((NVIC_ST_CTRL_R&0x00010000)==0) {
        ;                          /* wait for COUNT flag */
    }
}

void Delay(uint32_t delay){
unsigned long i; 
for(i=0; i<delay; i++){
SysTick_Wait(800000); // wait 10ms
}
}




//LCD

//LCD DATA
void LCD_Data(char data)
{
    GPIO_PORTA_DATA_R = 0x20; // 5alena rs b 1 w rw b 0 wel enable b 0
    GPIO_PORTA_DATA_R |= 0x80; // 5let el enable elly hya bit 7 teb2a high (1)
    GPIO_PORTB_DATA_R = data; // hya5od el data
    Delay(3); 
    GPIO_PORTA_DATA_R &= 0x1F;
}


//LCD Command
void LCD_Command(char com)
{
    GPIO_PORTA_DATA_R = 0x1F;// 34an a5li pin 5 w 6 w 7 elly hya rs w rw w e b zero
    GPIO_PORTA_DATA_R |=0x80; // 5let el enable elly hya bit 7 teb2a high (1)
    GPIO_PORTB_DATA_R = com; // hya5od el command
    Delay(3);
    GPIO_PORTA_DATA_R &= 0x1F; // rga3t el enable zero tani w3mlt equal 3latool 34an kda kda ba2i el bits kolha zeros
}



//LCD Initialization
void init_lcd(void)
{
		LCD_Command(0x38); // 8 bits
		Delay(2);
		LCD_Command(0x0E); // display on, cursor blinking
		Delay(2);
		LCD_Command(0x01); // clear
		Delay(2);
		LCD_Command(0x06); // increment cursor
		Delay(2);

}


long double Radius;
long double Difflong;
long double result;
long double lat1;
long double lat2;
long double long1;
long double long2;
long double Difflat ;

// Utility function for converting degrees to radians
long double toRadians(const long double degree)
{
	long double deg = ( M_PI) / 180;
	return (deg * degree);
}


//distance 

long double distance(long double lat1, long double long1,
long double lat2, long double long2)
{
	lat1 = toRadians(lat1);
	long1 = toRadians(long1);
	lat2 = toRadians(lat2);
	long2 = toRadians(long2);
	Difflong = long2 - long1;
	Difflat = lat2 - lat1;
	result = pow(sin(Difflat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(Difflong / 2), 2);
	result = 2 * asin(sqrt(result));
	Radius = 6371;
	result = result * Radius;
	return result*1000;
}

// convert float to string
void ftoa(float a) 
{
        sprintf(str_dist,"%f",a);
}

// main
int main()
{
	while(1)
	{
	    flag = 1;
	    in = UART2_Read();
	    if(in == '$')
	    {
		  for(i =1; i < 6; i++)
		    {       in = UART2_Read();
			    if(in != sign[i])
			    {
				    flag = 0;
				    break;
			    }
		    }
		    if(flag == 1) //founded!!!
		    {
			    for(j = 0 ; j < 44 ; j++)
			    {
				    in = UART2_Read();
				    coordinates[j]=in; // l7d my5zen elsatr kolo
			    }// kda m3ana ba2i elsatr mn awel el comma
			    count = 0;
			    for(k = 1; k < 3; k++)
			    {
				    ilat[count]=coordinates[k];
				    count++;
			    }
			    count = 0;
			    for(k = 3; k < 11; k++)
			    {
				    flat[count] = coordinates[k];
				    count ++;
			    }
			    count = 0;
			    for(l= 14; l < 17 ; l++)
			    {
				    ilong[count] = coordinates[l];
				    count++;
			    }
			    count = 0;
			    for(l= 17; l <25; l++)
			    {
				    flong[count] = coordinates[l];
				    count++;
			    }
			    ilat[2] = '\0';
			    flat[8] ='\0';
			    ilong[3] = '\0';
			    flong[8] = '\0';
		    } // end if
	    }

	} //end while
}


//End of main function
