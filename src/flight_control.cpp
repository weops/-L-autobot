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


  //while (!ros::ok());
  flightCmdWrapper.flight_print();
  ROS_INFO( "flight_control start" );

  int cmd;
  while (ros::ok())
  {
    //ROS_INFO( "testing" );
    cout << "0: launch\n1: land\n2: led\n";
    cin >> cmd;
    cout << "I received:" << cmd << endl;

    switch (cmd)
    {
      case 0:
        break;
      case 1:
        flightCmdWrapper.flight_land();
        break;
      case 2:
        flightCmdWrapper.led_animation();
        break;
      default:
        break;
    }
  }

  ros::spinOnce();
  loop_rate.sleep();

  return 0;
}

