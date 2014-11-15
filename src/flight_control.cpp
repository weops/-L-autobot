/*
 * flight algo that calculate flight path from reading sensor data and determining distance and direction of its target
 * move the drone by calling service from flight_cmd_wrapper
 *
 */

#include <we_autobot/flight_control.h>

int main( int argc, char **argv)
{
  ros::init( argc, argv, "flight_control" );
  
  ros::NodeHandle n;

  ros::Rate loop_rate( 10 );

  //FlightCmdWrapper flightCmdWrapper(TTL);
  FlightCmdWrapper flightCmdWrapper(WIFI);

  flightCmdWrapper.flight_print();

  ROS_INFO( "flight_control start" );
  while (ros::ok())
  {
    // your code
    //ROS_INFO( "testing" );
    //flightCmdWrapper.flight_print();
  }

  ros::spinOnce();
  loop_rate.sleep();

  return 0;
}

