//Интерфейс для различных режимов
#ifndef GARLAND_H
#define GARLAND_H

#include <array>
#include "IMode.h"

using tArrayModes = std::array<IMode*, 4>;
class Garland
{
public:
  
  Garland(tArrayModes& modes): _modes(modes)
  {

  }
  
  void UpdateCurrentMode() 
  {
     _modes[modeNumber]->Update();
  };
  
  virtual void SwithNextMode() 
  {
    if(modeNumber == _modes.size()-1)
    {
      modeNumber = 0;
    }
    else
    {
      modeNumber++;
    }
    _modes[modeNumber]->Clear(); // light off to all LEDs
  };
private:
  uint32_t modeNumber = 0;
  tArrayModes& _modes;

};

#endif