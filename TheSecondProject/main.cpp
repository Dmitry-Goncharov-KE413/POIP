#include "rccregisters.hpp" // for RCC
#include "gpioaregisters.hpp" // for GPIOA
#include "gpiocregisters.hpp" // for GPIO?
#include "rccregisters.hpp" // ��� ������ RCC
#include "gpiocregisters.hpp" // ������� ��� ����� �
//������� ��������
void Delay(int delay)
{
  for (int i=0; i<delay;++i)
  {
    //��� ���-�� ��������
    volatile int j = i; // ��� �����������, ��������� ��� ������ ��� ��� �� ����, ��� ���� ����� �������� ��������
    // ���� �������� ����������� �� ������ � ����������� volatile, �� ���������� ��� �����
    // � volatile ������� �� 
  }
  
}
//������� �������
int main()
{
  //������ ������������ �� ���� �
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  
  // c.5 c.8 c.9
  GPIOC::MODER::MODER7::Output::Set(); 
  GPIOC::MODER::MODER8::Output::Set(); 
  GPIOC::MODER::MODER9::Output::Set(); 
  // ������ ����������
  uint8_t i = 0; 
  while(true)// ���� ��� ������������ �������� �����������
  {
    i++;
    
    
    if (i%2==0)  // ������� �� ���������/������� ����������
    {
      GPIOC::ODR::ODR7::High::Set(); // ���������� ���������
      Delay(2000000);  // ����� ������� ��������
      GPIOC::ODR::ODR8::High::Set(); // ���������� ���������
      Delay(2000000);  // вызов функции задержки
      GPIOC::ODR::ODR9::High::Set();  // светодиод на порту С.9 загорается
      Delay(2000000);  // вызов функции задержки
    }
    else 
    {
      GPIOC::ODR::ODR7::Low::Set();  // светодиод на порту С.7 погасает
      Delay(2000000);  // вызов функции задержки
      GPIOC::ODR::ODR8::Low::Set();  // светодиод на порту С.8 погасает
      Delay(2000000);  // вызов функции задержки
      GPIOC::ODR::ODR9::Low::Set();  // светодиод на порту С.8 погасает
      Delay(2000000);  // вызов функции задержки
    } 
  }
}