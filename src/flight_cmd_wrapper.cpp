#include <we_autobot/flight_cmd_wrapper.h>
#include <stdio.h>
//#include "ros/ros.h"
//#include "std_msgs/String.h"
//
//#include <sstream>

//int main( int argc, char **argv)
//{
//    ros::init( argc, argv, "flight_cmd_wrapper" );
//    
//    ros::NodeHandle n;
//
//    ros::Rate loop_rate( 10 );
//
//    ROS_INFO( "flight_cmd_wrapper start" );
//    while (ros::ok())
//    {
//        // your code
//        //ROS_INFO( "testing" );
//    }
//
//    ros::spinOnce();
//    loop_rate.sleep();
//
//    return 0;
//}

FlightCmdWrapper::FlightCmdWrapper( ConnectMode mode ) : connectMode(mode)
{
  //printf( "connection mode: %d", connectMode );
  //ROS_INFO( "connection mode: %d", connectMode );
  switch (mode)
  {
    case WIFI:
    case TTL:
      break;
    default:
      connectMode = WIFI;
      break;
  }

  client = n.serviceClient<ardrone_autonomy::LedAnim>("ardrone/setledanimation");
}

void FlightCmdWrapper::flight_print()
{
  //printf( "connection mode: %d\n", connectMode );
  ROS_INFO( "connection mode: %d\n", connectMode );
}

void FlightCmdWrapper::LedAnimation()
{
  ardrone_autonomy::LedAnim srv;

  //# 0 : BLINK_GREEN_RED
  //# 1 : BLINK_GREEN
  //# 2 : BLINK_RED
  //# 3 : BLINK_ORANGE
  //# 4 : SNAKE_GREEN_RED
  //# 5 : FIRE
  //# 6 : STANDARD
  //# 7 : RED
  //# 8 : GREEN
  //# 9 : RED_SNAKE
  //# 10: BLANK
  //# 11: LEFT_GREEN_RIGHT_RED
  //# 12: LEFT_RED_RIGHT_GREEN
  //# 13: BLINK_STANDARD
  //uint8 type
  //
  //# In Hz
  //float32 freq
  //
  //# In Seconds
  //uint8 duration 

  srv.request.type      = 1;
  srv.request.freq      = 4;
  srv.request.duration  = 5;

  if (client.call(srv))
  {
    ROS_INFO("LED Animation OK");
  }
  else
  {
    ROS_INFO("LED Animation FAILED");
  }

}
