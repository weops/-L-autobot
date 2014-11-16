/*
 * flight algo that calculate flight path from reading sensor data and determining distance and direction of its target
 * move the drone by calling service from flight_cmd_wrapper
 *
 */

#include <we_autobot/flight_control.h>
bool flight_interactive( FlightCmdWrapper *flightCmdWrapper );
bool flight_auto( FlightCmdWrapper *flightCmdWrapper );

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


int main( int argc, char **argv)
{
  bool  programExit = false;
  bool  controlMode = false; // false: interactive CMD line, true: auto

  ros::init( argc, argv, "flight_control" );
  
  ros::NodeHandle n("~");

  ros::Rate loop_rate( 10 );

  n.getParam( "controlMode", controlMode );
  ROS_INFO( "control mode is %d", controlMode );

  //FlightCmdWrapper flightCmdWrapper(TTL);
  FlightCmdWrapper *flightCmdWrapper = new FlightCmdWrapper(WIFI);

  // TODO: parse in from rosrun arg for program mode: CMD line or Auto
  //
  while (!ros::ok());
  //system( "rosrun ardrone_autonomy ardrone_driver" );
  ROS_INFO( "waiting for drone..." );
  while (!flightCmdWrapper->check_drone_ready());
  flightCmdWrapper->print_connection_mode();
  ROS_INFO( "flight_control start" );

  // wait till drone is ready

  while (ros::ok() && !programExit)
  {
    if (controlMode)
    {
      programExit = flight_auto( flightCmdWrapper );
    }
    else
    {

      programExit = flight_interactive( flightCmdWrapper );
    }
  }

  ros::spinOnce();
  loop_rate.sleep();

  return 0;
}

// return true if flight is done
bool flight_interactive( FlightCmdWrapper *flightCmdWrapper )
{
  DroneCMD  cmd;
  int       inputCMD;
  bool      programExit = false;

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
      flightCmdWrapper->led_animation();
      break;
    case FLAT_TRIM:
      flightCmdWrapper->flat_trim();
      break;
    case LAUNCH:
      flightCmdWrapper->flight_launch();
      break;
    case LAND:
      flightCmdWrapper->flight_land();
      break;
    case ADVANCE:
      flightCmdWrapper->flight_advance( 0.2 );
      break;
    case STRIDE:
      flightCmdWrapper->flight_stride( 0.2 );
      break;
    case UP:
      flightCmdWrapper->flight_up( 0.2 );
      break;
    case TURN:
      flightCmdWrapper->flight_turn( -0.2 );
      break;
    case HOVER:
      flightCmdWrapper->flight_hover();
      break;
    case EXIT:
      ROS_INFO( "Exiting programming" );
      programExit = true;
      break;
    default:
      ROS_INFO( "Wrong CMD" );
      break;
  }

  return programExit;
}

// return true if flight is done
bool flight_auto( FlightCmdWrapper *flightCmdWrapper )
{
  bool   programExit = false;
  return programExit;
}

