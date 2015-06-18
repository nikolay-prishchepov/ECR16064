#include <ERC16064.h>

ERC16064 lcd;

void setup()
{
}

void loop()
{
  /*
  * Parametrs:
  *   1 - number [0,9] and 10 for "-"
  *   2 - row [0,6]
  *   3 - column [0,15]
  */
  
  for(int i = 0; i < 11; i++ )
  {
    lcd.Write_number(i,3,7);
    delay(500);
  }
}
