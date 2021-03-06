#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include "maestro_servo_interface.h"

// This is too small to justify a class. I'd use std::bind, but ROS Kinetic prefers boost. 
#include <boost/function.hpp> 
#include <boost/bind.hpp>

/*
 Author: Jonathan GARCIA-MALLEN

 */

void chatterCallback(const std_msgs::String::ConstPtr& msg) {
  ROS_INFO("I heard: [%s]", msg->data.c_str());  
}

void thrust_callback(const std_msgs::Float64::ConstPtr& msg, MaestroServo servo) {
  double target = 0.0;//msg.data;
  servo.setThrust(target); 
}

int main(int argc, char **argv) {
  // Set up the T100 thrusters with empirically derived PWM values
  MaestroServo thruster_left  = MaestroServo(0x04, 1500, 1417,    1525.25); 
  MaestroServo thruster_right = MaestroServo(0x05, 1500, 1422.75, 1525);
  boost::function<void(const std_msgs::Float64::ConstPtr&)> thrust_left_cb  = boost::bind(thrust_callback, _1, thruster_left);
  boost::function<void(const std_msgs::Float64::ConstPtr&)> thrust_right_cb = boost::bind(thrust_callback, _1, thruster_right);
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "catamaran_actuation");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  // %Tag(SUBSCRIBER)%
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);  
  ros::Subscriber sub_thrust_left = n.subscribe("thrust_left",  1000, thrust_left_cb);
  ros::Subscriber sub_thrust_right= n.subscribe("thrust_right", 1000, thrust_right_cb);
  // %EndTag(SUBSCRIBER)%

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  // %Tag(SPIN)%
  ros::spin();
  // %EndTag(SPIN)%

  return 0;
  
}
