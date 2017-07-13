#include "maestro_servo_interface.h"
#include <string>

/*
 Author: Jonathan GARCIA-MALLEN
 Description: subscribes to maestro_servo_command
 */
int main(int argc, char *argv[]) {
  if(argc == 2) {
    MaestroServo hitecServo = MaestroServo(0x02, 6200, 5400, 7000);
    double thrust = std::stod(argv[1]);
    hitecServo.setThrust(thrust);
  } else if(argc == 3){
    int channel = std::stoi(argv[1]);
    double thrust = std::stod(argv[2]);
    MaestroServo hitecServo = MaestroServo(channel, 6200, 5400, 7000);
    hitecServo.setThrust(thrust);    
  }
  return 0;
  
}
