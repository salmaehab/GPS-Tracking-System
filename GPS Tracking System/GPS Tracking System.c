#include "stdint.h"
#include "C:\keil\tm4c123gh6pm.h"

// Port init

void SystemInit() {}
	uint32_t delay;
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











//systick timer
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









//Lcd



//lcd Data





//lcd command






//lcd init





// main

