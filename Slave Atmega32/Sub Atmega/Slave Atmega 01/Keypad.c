/*****************************************************
* Author: Mostafa Ghazolley.
* Contact: MostafaGhazolley@outlook.com

	Function return the key-pressed (4x3)
	on the Keypad. Keys are numbered as follows
	in ASCII-Code
	from 0x30~0x3A ('0' to '9')+ 0x2A ('#') 
	and 0x23 ('*') .

    [00] [01] [02]
    [03] [04] [05]
    [06] [07] [08]
    [09] [10] [11]
  
    Arguments:
        None
 
    Return:
      Any number between 0-11  depending on
      key-pressed.
      
	*so to print out/send a hexa-decimel number to the LCD function we have to add (0x31+....) 
	to the returned number (in return of the keypad function!) so we can match the output (1) in ASCII-table ....
	using the Keypad 4x3 ((4R & 3C)) the last row ((# , 0 , * )) has to get special "if" conditions
	in order to printout the matching of the ASCII-table... 

      (hex 0xFF) if NO key-pressed.
  
      Precondition:
      None. Can be called without any setup.
	  
	  
      
*******************************************/


extern volatile unsigned char Key;

unsigned char GetKeyPressed(void)
 {
    unsigned char r,c; //rows and columns
    
    KEYPAD_PORT|= ALL_ROWS_HIGH; //0b0000 1111

    for(c=0;c<NUMBER_COLs;c++){
      KEYPAD_DDR&=~(ROW_COLUMN_HGIH); //0b0111 1111
      KEYPAD_DDR|=(FOURTHBIT<<c);  //0b0001 0000
    for(r=0;r<NUMBER_ROWs;r++)
    {
     if(!(KEYPAD_PIN & (FIRSTBIT<<r)))
	 { //0b0000 0001
       if(r==FOURTH_ROW)
	   {
         if(c==FIRST_COL)
		 {
           return (HASH_ASCII);	//return a '#' in ASCII-table.
         }
         if(c==SECOND_COL)
		 {
           return (ZERO_ASCII);	//return a '0' in ASCII-table.
         }
         if(c==THIRD_COL)
		 {
           return (ASTERISK_ASCII);	//return a '*' in ASCII-table.
         }
       }//END OF IF AT FOURTH ROW
       else
          {
            return (SWITCH_TO_ASCII+(r*NUMBER_COLs)+c); //+(hex 0x31) to switch to ASCII-table values.
          }
     }//END OF IF AT CHECKING PINS OUTPUT
     
    }//END FOR SECOND LOOP of rows
  }//END OF FIRST FOR LOOP OF COLUMNS
  return DEFAULT_KEYPRESS; //Indicate No key pressed.
}


