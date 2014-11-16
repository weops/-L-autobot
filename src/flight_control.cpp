/*
 * flight algo that calculate flight path from reading sensor data and determining distance and direction of its target
 * move the drone by calling service from flight_cmd_wrapper
 *
 */

#include <we_autobot/flight_control.h>

int main( int argc, char **argv)
{
  bool  programExit = false;

  enum DroneCMD
  {
     LED,
     FLAT_TRIM,
     LAUNCH,
     LAND,
     ADVANCE,
     STRIDE,
     UP,
     TURN,
     HOVER,
     EXIT
  };

  DroneCMD cmd;
  int       inputCMD;

  ros::init( argc, argv, "flight_control" );
  
  ros::NodeHandle n;

  ros::Rate loop_rate( 10 );

  //FlightCmdWrapper flightCmdWrapper(TTL);
  FlightCmdWrapper flightCmdWrapper(WIFI);


  //while (!ros::ok());
  flightCmdWrapper.flight_print();
  ROS_INFO( "flight_control start" );

  while (ros::ok() && !programExit)
  {
    cout  << LED        << ": led\n"
          << FLAT_TRIM  << ": flat_trim\n"
          << LAUNCH     << ": launch\n"
          << LAND       << ": land\n"
          << ADVANCE    << ": advance\n"
          << STRIDE     << ": stride\n"
          << UP         << ": up\n"
          << TURN       << ": turn\n"
          << HOVER      << ": hover\n"
          << EXIT       << ": exit\n";
    cin >> inputCMD;
    cout << "I received:" << inputCMD << endl;
    cmd = (DroneCMD)inputCMD;
    switch (cmd)
    {
      case LED:
        flightCmdWrapper.led_animation();
        break;
      case FLAT_TRIM:
        flightCmdWrapper.flat_trim();
        break;
      case LAUNCH:
        flightCmdWrapper.flight_launch();
        break;
      case LAND:
        flightCmdWrapper.flight_land();
        break;
      case ADVANCE:
        flightCmdWrapper.flight_advance( 0.2 );
        break;
      case STRIDE:
        flightCmdWrapper.flight_stride( 0.2 );
        break;
      case UP:
        flightCmdWrapper.flight_up( 0.2 );
        break;
      case TURN:
        flightCmdWrapper.flight_turn( -0.2 );
        break;
      case HOVER:
        flightCmdWrapper.flight_hover();
        break;
      case EXIT:
        ROS_INFO( "Exiting programming" );
        programExit = true;
        break;
      default:
        ROS_INFO( "Wrong CMD" );
        break;
    }
  }

  ros::spinOnce();
  loop_rate.sleep();

  return 0;
}

