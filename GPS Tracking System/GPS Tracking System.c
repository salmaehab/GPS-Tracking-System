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


//UART INIT
void UART0_Init(void)
{
        SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
        UART0_CTL_R &= ~UART_CTL_UARTEN;
        UART0_IBRD_R = 104;
        UART0_FBRD_R = 11;
        UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
        UART0_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
        GPIO_PORTA_AFSEL_R |= GPIO_PA10_M;
        GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00) |
        (GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX);
        GPIO_PORTA_DEN_R |= GPIO_PA10_M;
}
//check for UART flags
uint8_t UART0_Available(void){
return ((UART0_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

//Read data 
uint8_t UART0_Read(void){
while(UART0_Available() != 1);
return (uint8_t)(UART0_DR_R&0xFF);
}

//write data
void UART0_Write(uint8_t data){
while((UART0_FR_R&UART_FR_TXFF) != 0);
UART0_DR_R = data;
}

//UART 2
void UART2_Init(void){
SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R2;
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
UART2_CTL_R = 0;
UART2_IBRD_R = 104;
UART2_FBRD_R = 11;
UART2_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);UART2_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
GPIO_PORTD_AFSEL_R |= 0xC0;
GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFFFFFF00) |
(GPIO_PCTL_PD7_U2TX | GPIO_PCTL_PD6_U2RX);
GPIO_PORTD_DEN_R |= 0xFF;
}
//available uart2
uint8_t UART2_Available(void){
return ((UART2_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}
//port d read
uint8_t UART2_Read(void){
while(UART2_Available() != 1);
return (uint8_t)(UART2_DR_R&0xFF);
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
float toRadians(const float degree)
{
	float deg = ( M_PI) / 180;
	return (deg * degree);
}


//distance 

float distance(float lat1, float long1, float lat2, float long2)
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


uint8_t in;
int flag = 1;
char gps[61];
char sign[6] = {'$','G','P','G','L','L'};
char coordinates[44];
int i;
int j;
int k;
int l;
char ilong[4]; //int part of long
char flong[9]; //float part of long
char ilat[3];
char flat[9];
float latt = 1;
float longg = 1;
float longi = 1;
float lati = 1;
char str_dist[];
int n;
int m = 0;
float f;
float dist = 0;
float arr[700][2];


// convert float to string
void ftoa(float a) 
{
        sprintf(str_dist,"%f",a);
}

// main
int main()
{
	UART0_Init();
        UART2_Init();
        Delay(5);
        init();
        Delay(5);
        init_lcd();
        Delay(3);
        LCD_Command(0x01);
        Delay(2);
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
			    
			    
			    
			    longg= atof(ilong);
                                    longi= atof(flong)/60; //float part of long atof
                                    longg = longg + longi;
                                    latt = atof(ilat);
                                    lati = atof(flat)/60;
                                    latt = latt + lati;
                                    ///////////////
                                    arr[m][0] = latt;
                                    arr[m][1] = longg;
                                    if(m != 0)
                                    {
                                        f = distance(arr[m][0],arr[m][1], arr[m-1][0], arr[m-1][1]);
                                        dist += f;
                                        if(dist >= 100)GPIO_PORTF_DATA_R = 0x02;
                                    }
                                    ftoa(dist);
                                    Delay(50);
                                    LCD_Command(0x01);
                                    for(n = 0; n < 5; n++)
                                    {
                                        LCD_Data(str_dist[n]);
                                    }
                                    m++;
		    } // end if
	    }

	} //end while
}


//End of main function
