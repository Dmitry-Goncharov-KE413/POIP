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
#include "SlideMode.h" // Mode of "Christmas tree"
#include "Garland.h" // Mode of "Garland"
#include "IButtonObserver.h"
#include "IObservable.h"

#include <iostream>
#include <array> // Connection of libraries for work with arraies
#include "stkregisters.hpp" // for STK (System Timer)
#include "scbregisters.hpp" // for SCB

constexpr std::uint32_t SystemClock = 8'000'000U;
constexpr std::uint32_t OneMillisecondsRatio = 1000U;


// -------------------------Function of delay-----------------------------------
int Delay(std::uint32_t millisecons)
{
  const std::uint32_t delayCounts = millisecons*SystemClock/OneMillisecondsRatio - 1U;
  
  STK::VAL::Write(0U);
  STK::LOAD::Write(delayCounts);
  STK::CTRL::ENABLE::Enable::Set();
  while(!STK::CTRL::COUNTFLAG::Overflow::IsSet())
  {
    
  }
  //STK::CTRL::ENABLE::Disable::Set();
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
  TreeMode treeMode(leds);
  SlideMode slideMode(leds);
//------------------------------------------------------------------------------  
  
//----------------------------------Array of modes--------------------------
    using tArrayModes = std::array<IMode*,4>;
    tArrayModes modes =
    {
      &allMode,
      &chessMode,
      &treeMode,
      &slideMode,

    };
//------------------------------------------------------------------------------
    
//-------------Creation of object (garland) with binding of modes----------------  
  Garland garland(modes);
  Gyru gyru;

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
  
  userButton1.AddObserver(garland);
  userButton1.AddObserver(gyru);
  
 //---------------------------Port and number of ports--------------------------------


  //std::uint32_t modeNumber = 0;
  for(;;)  
  {
    Delay(1000); 
    if(userButton1.IsPressed())
    { 
      garland.SwithNextMode();
    }
    Delay(1000);   
    garland.UpdateCurrentMode();
  }
  // create a mode for adding of subscriber (for the next lesson)
}
