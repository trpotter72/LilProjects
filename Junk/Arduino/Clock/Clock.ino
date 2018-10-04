#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif

// Example to control LPD8806-based RGB LED Modules in a strip

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 32;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;

//initializes the data and clock pins to the numbers provided and takes in the number of LEDs
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);


//Time Values
int hours = 0;
int seconds = 0;
int minutes = 0;

//LED Color Values
uint32_t secondColor = strip.Color(0,1,1);
uint32_t minuteColor = strip.Color(0,0,1);
uint32_t hourColor = strip.Color(1,1,1);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
  
  
}


void loop() {
  seconds ++;
  updateTimeValues();
  updateLEDs();
}

void updateTimeValues()
{
  if (seconds == 60)
  {
    seconds = 0;
    minutes++;
  }
  if(minutes == 60)
  {
    hours += 1;
  }
  
}


void updateLEDs()
{
  //Blink the 'seconds' LED
  strip.setPixelColor(nLEDs-1, strip.Color(1,1,1));
  

  for (int i = 0; i <=minutes/2; i++)
  {
   strip.setPixelColor(i, minuteColor);
   strip.show();
  } 
  if(minutes % 2 == 1)
  {
    strip.setPixelColor((minutes/2 + 1), strip.Color(2, 2, 2));
  }
  
  strip.show();
  delay(250);
  strip.setPixelColor(nLEDs-1, 0);
  if(minutes % 2 == 1)
  {
    strip.setPixelColor((minutes/2 + 1), strip.Color(0, 0, 0));
  }
  strip.show();
  delay(750);
}
/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}
