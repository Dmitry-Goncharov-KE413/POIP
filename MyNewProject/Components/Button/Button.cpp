#include "Button.h"


Button::Button(const IPinReadable& pin): _pin(pin)
{
  
}
// Кнопка нажата
   bool Button::IsPressed() const 
  {   
    if( !_pin.IsHigh() )  // Если кнопка не нажата 
    {
        while (!_pin.IsHigh()) // Если в како-то момент времени кнопка нажалась, то режим меняем
        {
           volatile int a = 1;
        } 
        return true;
    }
    return false;

  } 
