#include "rccregisters.hpp" // for RCC
#include "gpiocregisters.hpp" // Register of Port C
#include "gpioaregisters.hpp" // Register of Port A
#include "gpiobregisters.hpp" // Register of Port B
#include "gpiodregisters.hpp" // Register of Port D


#include "pinconfig.h"
#include "LED.h"   // Connection of header file
#include  "Button.h" // Connection of button
#include "AllMode.h" // Mode of "All the LEDs are on"
#include "ChessMode.h" // Mode of "Chess"
#include "TreeMode.h" // Mode of "Christmas tree"
#include "Garland.h" // Mode of "Garland"


#include <iostream>
#include <array> // Connection of libraries for work with arraies
// -------------------------Function of delay-----------------------------------
int Delay(int value)
{
  for(int i = 0;i<value;++i)
  {
    volatile int j = i; 
  }
}
//-------------Creation of LEDs with binding of pins--------------

Led led1(pinA5); 
Led led2(pinC5);
Led led3(pinC8);
Led led4(pinC9);
Button userButton1(pinC13);
//------------------------------------------------------------------------------

//----------------------------------Array of LEDs-----------------------
   
    tArrayLeds leds =
    { 
      &led1,
      &led2,
      &led3,
      &led4,
    };
//------------------------------------------------------------------------------
    
//-------------Creation of objects with array of LEDs------------  
  AllMode allMode(leds); 
  ChessMode chessMode(leds);
//------------------------------------------------------------------------------  
  
//----------------------------------Array of modes--------------------------
    using tArrayModes = std::array<IMode*,2>;
    tArrayModes modes =
    { 
      &allMode,
      &chessMode,

    };
//------------------------------------------------------------------------------
    
//-------------Creation of object (garland) with binding of modes----------------  
  Garland garland(modes); 

//------------------------------------------------------------------------------     
    
int main()
{ 
  // Submitting the clock for Ports of MCU
  RCC::AHB1ENR::GPIOCEN::Enable::Set(); // Port C
  RCC::AHB1ENR::GPIOAEN::Enable::Set(); // Port A
  RCC::AHB1ENR::GPIOBEN::Enable::Set(); // Port B

  // Connection of Port C and port A to Output
  GPIOA::MODER::MODER5::Output::Set();
  GPIOC::MODER::MODER5::Output::Set();
  GPIOC::MODER::MODER8::Output::Set();
  GPIOC::MODER::MODER9::Output::Set();
  
  
  
 //---------------------------Port and number of ports--------------------------------


  //std::uint32_t modeNumber = 0;
  for(;;)  
  {
    Delay(100000); 
    if(userButton1.IsPressed())
    { 
      garland.SwithNextMode();
    }
    Delay(1000000);    
    garland.UpdateCurrentMode();
  }
  
}
