//Question2 - Implement Upcounter to count 00 - 99

#include<lpc21xx.h>

void delay(unsigned int c)
{
	unsigned int a;
	for(a=1;a<=30000;a++);
}

int main()
{
	//Select the Port
PINSEL0=0x00000000;
PINSEL1=0x00000000;
	
	//Set the direction
IO0DIR=0xFFFFFFFF;

while(1)
{ 
	unsigned long int i,j;

	//Send data, we are using Common Cathode - send 1 to glow the bit
  int a[]={0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
  int b[]={0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
  
	for(i=0;i<10;i++)
		{
       IO0SET=IO0SET|a[i];	// send data to 1st seven segment display
          for(j=0;j<10;j++)
            {
               IO0SET= IO0SET|(b[j]<<8);//send data to 2nd seven segment display
               delay(10000);
               IO0CLR= IO0CLR|(b[j]<<8);//Clear the 2nd seven segement display
            }
        IO0CLR=IO0CLR|a[i]; // clear the 1st seven segment display after sending the data
      }
		}
}