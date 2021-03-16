
unsigned char ExtEPROM_Write(unsigned int addr,unsigned char data)
{
	I2C_Start();
	if(I2C_GetStatus() != 0x08)
	return 1;
	I2C_Write(EEPROM_Write_Address);
	if(I2C_GetStatus() != 0x18)
	return 2;
	I2C_Write((unsigned char)(addr));
	if(I2C_GetStatus() != 0x28)
	return 3;
	I2C_Write(data);
	if(I2C_GetStatus() != 0x28)
	return 4;
	I2C_Stop();
	return 5;
}

unsigned char ExtEPROM_Read(unsigned int addr,unsigned char *data)
{
	
	I2C_Start();
	if(I2C_GetStatus() != 0x08)
	return 1;
	I2C_Write(EEPROM_Write_Address);
	if(I2C_GetStatus() != 0x18)
	return 2;
	I2C_Write((unsigned char)(addr));
	if(I2C_GetStatus() != 0x28)
	return 3;
	I2C_Start();
	if(I2C_GetStatus() != 0x10)
	return 4;
	I2C_Write(EEPROM_Read_Address);
	if(I2C_GetStatus() != 0x40)
	return 5;
	*data=I2C_Read_Nack();
	if(I2C_GetStatus() != 0x58)
	return 6;
	I2C_Stop();
	return 7;
}