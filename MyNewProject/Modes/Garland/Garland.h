//Интерфейс для различных режимов
#ifndef GARLAND_H
#define GARLAND_H
#include <iostream>

#include <array>
#include "IMode.h"
#include "IButtonObserver.h"


using tArrayModes = std::array<IMode*, 4>;

class Garland: private IButtonObserver
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
  
  void OnButtonPress() override
  {
    SwithNextMode();
  }
  
private:
  uint32_t modeNumber = 0;
  tArrayModes& _modes;

};

class Gyru : public IButtonObserver
{
  void OnButtonPress() override
  {
    std::cout<<"Button is pressed"<<std::endl;
  }
}
#endif