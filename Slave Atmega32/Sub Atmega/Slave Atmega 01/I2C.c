void I2C_Init(void)
{
	TWCR = (1<<TWEN);
	TWSR = 0x00; //TWPS = 0...
	TWBR = 0x02; //250kHZ (F_CPU = 8M)
	/*
	(8000000) / ( 16 + ( 2 x (4^TWPS) x TWBR )
	which TWPS default 0 , 0 (TWPS0 and TWPS1)
	which mean power to 1 (default)
	TWBR = 2...
	to get SCL_Freq = 250 000
	*/ 
	//_delay_ms(150);
}

void I2C_Start(void)
{
	TWCR=(1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while ((TWCR & (1<<TWINT)) == 0);		//waiting if bus is busy...
}

void I2C_Stop(void)
{	//stop function
	TWCR=(1<<TWEN)|(1<<TWSTO)|(1<<TWINT);	//Enable I2C, generates stop
	while(TWCR&(1<<TWSTO));					//wait until stop condition

}

void I2C_Write(unsigned char data)
{
	TWDR=data;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while((TWCR&(1<<TWINT))==0);
}

unsigned char I2C_Read(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return (TWDR);
}

unsigned char I2C_GetStatus()
{
	return (TWSR&0xF8);
}

unsigned char I2C_Read_Nack()			// I2C read nack function 
{
	TWCR=(1<<TWEN)|(1<<TWINT);	// Enable TWI and clear interrupt flag 
	while(!(TWCR&(1<<TWINT)));	// Wait until TWI finish its current job 
	return TWDR;				// Return received data 
}

unsigned char I2C_Read_Ack()		// I2C read ack function 
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA); // Enable TWI, generation of ack 
	while(!(TWCR&(1<<TWINT)));	// Wait until TWI finish its current job 
	return TWDR;			// Return received data 
}
