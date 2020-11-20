void SPI_MasterInit(void)
{	
	//set MOSI, SCK, SS as output pins...
	SPI_DDR |= (1<<MOSI) | (1<<SCK) | (1<<SS);
	//Set MISO as input pin...
	SPI_DDR &= ~(1<<MISO);
	//Enable SPI, Master mode, Shift Clock clk/16
	SPCR= (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	
}

void SPI_SlaveInit(void)
{
	//set MOSI, SCK, SS as output pins...
	SPI_DDR |= (1<<MISO);
	//Set MISO as input pin...
	SPI_DDR &=~(1<<MOSI) & ~(1<<SCK) & ~(1<<SS);
	//Enable SPI, Master mode, Shift Clock clk/16
	SPCR = (1<<SPE);
	
}

unsigned char SPI_Transmitter(unsigned char SPI_DATA)
{
	//char FLUSH_BUFFER;
	SPDR = SPI_DATA;			//start transmission
	while( !(SPSR & (1<<SPIF)) );	//wait for the transmission to complete 
	//FLUSH_BUFFER=SPDR;
	return SPDR;				//return receive data
}