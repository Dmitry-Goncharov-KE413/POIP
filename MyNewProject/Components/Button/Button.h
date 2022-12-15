#ifndef  BUTTON_H
#define  BUTTON_H

#include "IButton.h"
#include "iPinReadable.h"


class Button : public IButton
{
public: 
  Button(const IPinReadable& pin) ; 
  
   bool IsPressed() const override; 
 
  
private:
    const IPinReadable& _pin; 
};

#endif