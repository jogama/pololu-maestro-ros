#ifndef MAESTRO_SERVO_INTERFACE_HEADER
#define MAESTRO_SERVO_INTERFACE_HEADER

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/* This class currently has a very narrow interface,
   as the inner workings of the class were written in a
   rush and likely needs refactoring. 
 */

class MaestroServo
{
 public:
  MaestroServo(unsigned char channel, int zero, int max, int min);
  ~MaestroServo();
  int setThrust(double thrust);

 private:
  int setTarget(unsigned short target);  
  int m_device_file;
  unsigned char m_channel;
  int m_zero;
  int m_max;
  int m_min;
};

#endif // MAESTRO_SERVO_INTERFACE_HEADER
