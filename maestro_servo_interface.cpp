// Modified from from https://www.pololu.com/docs/0J40/5.h.1
//   by Jonathan Garcia-Mallen
// The C syntax is in herited from there

// Uses POSIX functions to send and receive data from a Maestro.
// NOTE: The Maestro's serial mode must be set to "USB Dual Port".
// NOTE: You must change the 'const char * device' line below.

#include "maestro_servo_interface.h"
#include <stdexcept>

MaestroServo::MaestroServo(unsigned char channel, int zero, int max, int min){
  // Initialize member constants
  m_channel = channel;
  m_zero    = zero;
  m_max     = max;
  m_min     = min;
  
  // Open the Maestro's virtual COM port in Linux
  m_device_file = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
}

MaestroServo::~MaestroServo(){
  close(m_device_file);
}

// Sets the target of a Maestro channel.
// See the "Serial Servo Commands" section of the user's guide.
// The units of 'target' are quarter-microseconds.
int MaestroServo::setTarget(unsigned short target)
{
  unsigned char command[] = {0x84, m_channel, target & 0x7F, target >> 7 & 0x7F};
  if (write(m_device_file, command, sizeof(command)) == -1) {
    perror("error writing");
    return -1;
  }
  return 0;
  
}

int MaestroServo::setThrust(double thrust){
  if(thrust > 1 || thrust < -1){
    throw std::out_of_range("argument thrust must be in the range [-1, 1]");
  }
      
  int target = m_zero;
  
  if(thrust > 0){
    target = m_zero + thrust * (m_max - m_zero);
  }
  else if(thrust < 0){
    target = m_zero + thrust * (m_zero - m_min);
  }

  return MaestroServo::setTarget(target);  
}
