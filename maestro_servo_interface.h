#ifndef MAESTRO_SERVO_INTERFACE_HEADER
#define MAESTRO_SERVO_INTERFACE_HEADER

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

class MaestroServo
{
 public:
  MaestroServo(unsigned char channel, int zero, int max, int min);
  ~MaestroServo();
  int setTarget(unsigned short target);
  int setPercentThrust(double percent_thrust);

 private:
  int m_device_file;
  unsigned char m_channel;
  int m_zero;
  int m_max;
  int m_min;
};

#endif // MAESTRO_SERVO_INTERFACE_HEADER
