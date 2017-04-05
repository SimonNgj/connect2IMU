//Aplication to MPU6050 & MSP430G2553
//--------------------------------------------o0o---------------------------------------------
#include <msp430.h> 
#include <stdint.h>
#include "stdio.h"
#include "stdarg.h"
#include "cmath"
#include "MPU6050Map.h"						// Declaration of MPU6050 (ADXL345 - Accelerometer && ITG3200 - Gyro Scope)

#define PI 			3.141592654
//--------------------------------------------o0o---------------------------------------------
uint8_t *PRx,*PTx;  					    // 2 Pointers (PRx for READING, PTx for WRITING)
uint8_t RXByteCtr=0;						// Length of data for READING
uint8_t TXByteCtr=0;						// Length of data for WRITING
uint8_t RX=0;								// Variable to separate WRITE of READ
uint8_t buffer[6];							// To store data (3 axises - x, y and z)
uint8_t a1 = 0x00;
char buff[7];							   // To store data (for UART sending)
int16_t ax,ay,az;
int16_t a[3];
int16_t i = 0;


double aux[4];
double y[2],angle[2], newAngle[3], angle_predict[2], rate[2], newRate[3], bias[2];
int16_t anx, any, anz;
//--------------------------------------------o0o---------------------------------------------
// Initialize UART
void initUart(void)
{
      UCA0CTL1 |= UCSSEL_2;                // Use SMCLK
      UCA0BR0 = 104;                       // 1MHz 9600
      UCA0BR1 = 0;                         // 1MHz 9600
      UCA0MCTL = UCBRS0;                   // Modulation UCBRSx = 1
      P1SEL |= BIT1 + BIT2 ;                // P1.1 = RXD, P1.2=TXD
      P1SEL2|= BIT1 + BIT2 ;               // P1.1 = RXD, P1.2=TXD
      UCA0CTL1 &= ~UCSWRST;                // Initialize USCI state machine
      IE2 |= UCA0TXIE;
}
//--------------------------------------------o0o---------------------------------------------
// Initialize I2C
void Init_i2c(uint8_t devAddr)
{
	UCB0CTL1 |= UCSWRST;                   // Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;  // I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;         // Use SMCLK, keep SW reset
	UCB0BR0 = 10;                          // fSCL = 1Mhz/10 = ~100kHz
	UCB0BR1 = 0;
	P1SEL |=  BIT6 + BIT7;                 // Assign  I2C pins to  USCI_B0 // Assign Uart pins to USCI_A0
	P1SEL2|=  BIT6 + BIT7;                 //  Assign  I2C  pins  to  USCI_B0  //  Assign  Uart  pins  to USCI_A0
	UCB0I2CSA = devAddr;                   // Slave Address is 069h
	UCB0CTL1 &= ~UCSWRST;                  // Initialize USCI state machine
	//IE2 |= UCB0RXIE + UCB0TXIE;            // Enable RX and TX interrupt
	IE2 |= UCB0RXIE;            			// Enable RX and TX interrupt
}
//---------------------------------------------o0o------------------------------------------------------------
//Write a char to PC
void UART_Write_Char(unsigned char data)
{
	while (!(IFG2&UCA0TXIFG));                 // Doi gui xong ky tu truoc
	UCA0TXBUF= data;                           // Moi cho phep gui ky tu tiep theo
}
//---------------------------------------------o0o------------------------------------------------------------
//Write a string to PC
void UART_Write_String(char* string)
{
	if(*string == 0)
	{
		while (!(IFG2&UCA0TXIFG));             // Doi gui xong ky tu truoc
		UCA0TXBUF = '0';                       // Moi cho phep gui ky tu tiep theo
	}
	while(*string)                             // Het chuoi ky tu thi thoat
	{
		while (!(IFG2&UCA0TXIFG));             // Doi gui xong ky tu truoc
		UCA0TXBUF = *string;                   // Moi cho phep gui ky tu tiep theo
		string ++;                             // Lay ky tu tiep theo
	}
	UART_Write_Char(0);
}
//--------------------------------------------o0o---------------------------------------------
// Assign address of sensor MPU6050
void transmitIni(uint8_t regAddr)
{
	while (UCB0CTL1 & UCTXSTP);          // Ensure stop condition got sent
	UCB0CTL1  |=  UCTR  +  UCTXSTT;      // I2C  start  condition  with  UCTR  flag  for transmit
	while((IFG2 & UCB0TXIFG) == 0);      // UCB0TXIFG is set immidiately
	UCB0TXBUF = regAddr;                 // write registerAddr in TX buffer
	while((IFG2  &  UCB0TXIFG)  ==  0);  // wait  until  TX  buffer  is  empty  and transmitted
}
//--------------------------------------------o0o---------------------------------------------
// Read data from sensor to MCU
void ReadBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data)
{
	_DINT();                            // Disable interrupt
	IE2 &= ~(UCB0TXIE);                 // Disable interrupt - transmit
	IE2 &= ~(UCB0RXIE);                 // Disable interrupt - receive
	RX=1;
	transmitIni(regAddr);
	IE2 |= UCB0RXIE;                    //+ UCB0TXIE; // Enable RX and TX interrupt
	PRx = (uint8_t *)data;
	RXByteCtr = length;
	while  (UCB0CTL1  &  UCTXSTP);      // Ensure  stop  condition  got sent
	UCB0CTL1 &= ~UCTR ;                 // Clear I2C TX flag for receive
	UCB0CTL1 |= UCTXSTT;                // I2C TX, start condition
	__bis_SR_register(CPUOFF + GIE);    // Enter LPM0 w/ interrupts
}
//--------------------------------------------o0o---------------------------------------------
// Write configuration to sensor MPU6050
void WriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data)
{
	_DINT();
	RX=0;

	IE2 &= ~(UCB0TXIE);
	IE2 &= ~(UCB0RXIE);
	transmitIni(regAddr);
	IE2 |= UCB0TXIE;                  	// Enable RX and TX interrupt
	TXByteCtr = length;
	PTx = (uint8_t *)data;
	while  (UCB0CTL1  &  UCTXSTP);    	//  Ensure  stop  condition  got sent
	__bis_SR_register(CPUOFF + GIE);  	// Enter LPM0 w/ interrupts
 }
//--------------------------------------------o0o---------------------------------------------
// Function  that  retrieves  the  6-axis  motion  from MPU6050
void  getMotion6(int16_t*  ax,  int16_t*  ay,  int16_t*  az)
{
	ReadBytes(MPU6050Addr, MPU6050_RA_ACCEL_XOUT_H, 6, buffer);
	*ax = (((int16_t)buffer[0]) << 8) | buffer[1];
	*ay = (((int16_t)buffer[2]) << 8) | buffer[3];
	*az = (((int16_t)buffer[4]) << 8) | buffer[5];
}
//--------------------------------------------o0o---------------------------------------------
//  Function setups  IMU.
void initializeIMU()
{
	WriteBytes(MPU6050Addr, MPU6050_RA_PWR_MGMT_1,1, &a1);       //Clock Source: PLL with X axis gyroscope reference
	WriteBytes(MPU6050Addr, MPU6050_RA_ACCEL_CONFIG, 1,&a1);     //Range = +- 2g, Filter: ON, Cut-off: 5Hz, LSB Sensitivity: 16384 LSB/mg
}
//--------------------------------------------o0o---------------------------------------------
// Sub-program (routine) when calling interrupt
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if((IFG2&UCA0TXIFG)&&(IE2&UCA0TXIE))         		// UART-interrupt
	{
		IE2 &= ~UCA0TXIE;                       		// Disable USCI_A0 TX interrupt
		IFG2&= ~UCB0TXIFG;                   			// Clear USCI_B0 TX int flag
	}
	if((IE2&UCB0TXIE)||(IE2&UCB0RXIE))                  // I2C-Interrupt
	{
		if(RX == 1)										// Read from sensors (Interrupt)
		{                                        		// Master Recieve?
			if (RXByteCtr)
			{
				*PRx++ = UCB0RXBUF;              		// Move RX data to address PRxData
				RXByteCtr--;                         	// Decrement RX byte counter
			}
			else
			{
				UCB0CTL1 |= UCTXSTP;             		// No Repeated Start: stop condition
				*PRx = UCB0RXBUF;                		// Move final RX data to PRxData
				IFG2 &= ~UCB0RXIFG;                     // Clear USCI_B0 TX int flag
				__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
			}
		}

		else											// Write to sensors - Configuration (Interrupt)
		{                                               // Master Transmit
			if (TXByteCtr)                              // Check TX byte counter
			{
				UCB0TXBUF = *PTx++;                     // Load TX buffer
				while((IFG2 & UCB0TXIFG) == 0);         // wait until TX buffer is emptyand transmitted
				TXByteCtr--;                            // Decrement TX byte counter
			}
			else
			{
				UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
				IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
				__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
			}
		}
	}
}
//--------------------------------------------o0o---------------------------------------------
//Main-function
//--------------------------------------------o0o---------------------------------------------
int main(void) {

    WDTCTL = WDTPW | WDTHOLD;	                   // Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;                         // Set DCO to 1Mhz
    DCOCTL = CALDCO_1MHZ;
    P1DIR = 0x01;
    P1OUT = 0;
/*
    P2DIR&=~BIT4;
    P2REN|= BIT4;
    P2OUT|= BIT4;*/
//--------------------------------------------o0o---------------------------------------------
//          Loop - while
//--------------------------------------------o0o---------------------------------------------
    while(1)
    {
    	//i++;
    	//if((P2IN&BIT4) == 0){						//BITA~BIT2, BITB~BIT3
    	P1OUT ^= BIT0;
    	Init_i2c(MPU6050Addr);
    	initializeIMU();
    	getMotion6( &ax, &ay, &az);

    	a[0] = ax;
    	a[1] = ay;
    	a[2] = az;

    	aux[3]=0.0;
    	for(i=0;i<3;i++){
    	   aux[i] = a[i];
    	   aux[i] = aux[i]/5000.0;
    	   //aux[3] += pow((double)aux[i],2.0);
    	   aux[3] += (double)(aux[i]*aux[i]);
    	}

    	aux[3] = sqrt(aux[3]);

    	for(i=0;i<2;i++){
    	    newAngle[i]=((acos(aux[i]/aux[3])*180)/PI)-90;
    	  //  newRate[i]= (double)g[i]/16.3835;
    	}


    	anx = round(-newAngle[0]);
    	any = round(newAngle[1]);
    	anz = round(newAngle[2]);


    	//UCB0CTL1 = 0x01;                            // Enable SW reset
    	//UCB0CTL0 = 0x01;
    	/*if(i==5000)
    	{
    		initUart();
    		UART_Write_String("Finish");
    	}*/

    	initUart();
    	                     //axFiltered
    	sprintf(buff,"%d",anx);
    	UART_Write_String(buff);
    	//UART_Write_Char(' ');
    	                     //ayFiltered
    	//sprintf(buff,"%d",any);
    	//UART_Write_String(buff);
    	/*UART_Write_Char(' ');
    	                      //azFiltered
    	sprintf(buff,"%d",anz);
    	UART_Write_String(buff);
    	UART_Write_Char(' ');*/
    	UART_Write_Char(10);

    	//UCA0CTL1 = 0x01;
    	//}
    }
}
//--------------------------------------------o0o---------------------------------------------
//End of program
