/*Question1 - ON LED 1 and OFF with delay of 1 sec
						- ON LED 2 and OFF with delay of 500 ms
			
		P1.18 - Switch1
		P1.19 - Switch2
		
*/
			
#include<lpc214x.h>

void delay(unsigned int z);       
void pll();

int main(void)
{
    IO0DIR=0xFFFFFFFF;
    IO1DIR =0x0;                         
    pll();                  //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
	
    while(1) {
      if((IO1PIN & (1<<18)) ==0)		// reading status at P1.18 configured as Switch1 to glow LED1
        {           
        IO0SET=0x000000FF;
        delay(1000);            //1sec delay; because 1 sec = 1000ms
        IO0CLR=0x000000FF;
        delay(1000);
        }
        if((IO1PIN & (1<<19)) ==0)	//reading status at P1.19 configured as Switch2 to glow LED2
        {
        IO0SET=0x0000FF00;
        delay(500); //500ms delay
        IO0CLR=0x0000FF00;
        delay(500);
        }           
    }
}

void pll()                  //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
{
    PLL0CON=0x01;
    PLL0CFG=0x24;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    while(!(PLL0STAT&(1<<10)));
    PLL0CON=0x03;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    VPBDIV=0x01;
}

void delay(unsigned int z)
{
    T0CTCR=0x0;                 //Select Timer Mode
    T0TCR=0x00;                 //Timer off
    T0PR=59999;                 //Prescaler value for 1ms calculated 
    T0TCR=0x02;                 //Timer reset
    T0TCR=0x01;                 //Timer ON
    while(T0TC<z);          
    T0TCR=0x00;                 //Timer OFF
    T0TC=0;                     //Clear the TC value
}
