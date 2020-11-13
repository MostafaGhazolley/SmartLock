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
    
    KEYPAD_PORT|= 0X0F; //0b0000 1111

    for(c=0;c<3;c++){
      KEYPAD_DDR&=~(0X7F); //0b0111 1111
      KEYPAD_DDR|=(0X10<<c);  //0b0001 000
    for(r=0;r<4;r++)
    {
     if(!(KEYPAD_PIN & (0X01<<r))){ //0b0000 0001
       if(r==3){
         if(c==0){
           return (0x2A);	//return a '#' in ASCII-table.
         }
         if(c==1){
           return (0x30);	//return a '0' in ASCII-table.
         }
         if(c==2){
           return (0x23);	//return a '*' in ASCII-table.
         }
       }
       else
          {
            return (0x31+r*3+c); //+(hex 0x31) to switch to ASCII-table values.
          }
     }
     
    }
  }
  return 0XFF; //Indicate No key pressed.
}


