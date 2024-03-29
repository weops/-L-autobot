#include "ros/ros.h"
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

  srvLedClient        = n.serviceClient<ardrone_autonomy::LedAnim>("ardrone/setledanimation");
  srvFlatTrimClient   = n.serviceClient<std_srvs::Empty>("ardrone/flattrim");
  msgLandPublisher    = n.advertise<std_msgs::Empty>("ardrone/land", 100);
  msgLaunchPublisher  = n.advertise<std_msgs::Empty>("ardrone/takeoff", 100);
  msgMovePublisher    = n.advertise<geometry_msgs::Twist>("cmd_vel", 100);
}

void FlightCmdWrapper::print_connection_mode()
{
  ROS_INFO( "connection mode: %d\n", connectMode );
}

void FlightCmdWrapper::led_animation()
{
  ardrone_autonomy::LedAnim srv;

  ROS_INFO("LED Animation...");
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

  if (srvLedClient.call(srv))
  {
    ROS_INFO("OK");
  }
  else
  {
    ROS_INFO("FAILED");
  }

}

void FlightCmdWrapper::flat_trim()
{
  std_srvs::Empty srv;

  ROS_INFO("Flat Trim...");
  if (srvFlatTrimClient.call( srv ))
  {
    ROS_INFO("OK");
  }
  else
  {
    ROS_INFO("FAILED");
  }
}

void FlightCmdWrapper::flight_launch()
{
  std_msgs::Empty emptyMsg;

  ROS_INFO("Drone Launching...");

  msgLaunchPublisher.publish( emptyMsg );
}

void FlightCmdWrapper::flight_land()
{
  std_msgs::Empty emptyMsg;

  ROS_INFO("Drone Landing...");

  msgLandPublisher.publish( emptyMsg );
}

void FlightCmdWrapper::flight_advance( double magnitude )
{
  geometry_msgs::Twist moveMsg;
  
  moveMsg.linear.x = (magnitude <= 1 && magnitude >= -1) ? magnitude : 0;
  moveMsg.linear.y = 0;
  moveMsg.linear.z = 0;

  moveMsg.angular.z = 0;

  ROS_INFO( "Flight Advance %f", moveMsg.linear.x );
  msgMovePublisher.publish( moveMsg );
}

void FlightCmdWrapper::flight_stride( double magnitude )
{
  geometry_msgs::Twist moveMsg;
  
  moveMsg.linear.x = 0;
  moveMsg.linear.y = (magnitude <= 1 && magnitude >= -1) ? magnitude : 0;
  moveMsg.linear.z = 0;

  moveMsg.angular.z = 0;

  ROS_INFO( "Flight Stride %f", moveMsg.linear.y );
  msgMovePublisher.publish( moveMsg );
}

void FlightCmdWrapper::flight_up( double magnitude )
{
  geometry_msgs::Twist moveMsg;
  
  moveMsg.linear.x = 0;
  moveMsg.linear.y = 0;
  moveMsg.linear.z = (magnitude <= 1 && magnitude >= -1) ? magnitude : 0;

  moveMsg.angular.z = 0;

  ROS_INFO( "Flight Up %f", moveMsg.linear.z );
  msgMovePublisher.publish( moveMsg );
}

void FlightCmdWrapper::flight_turn( double magnitude )
{
  geometry_msgs::Twist moveMsg;
  
  moveMsg.linear.x = 0;
  moveMsg.linear.y = 0;
  moveMsg.linear.z = 0;

  moveMsg.angular.z = (magnitude <= 1 && magnitude >= -1) ? magnitude : 0;

  ROS_INFO( "Flight turn %f", moveMsg.angular.z );
  msgMovePublisher.publish( moveMsg );
}

void FlightCmdWrapper::flight_hover()
{
  geometry_msgs::Twist moveMsg;
  
  moveMsg.linear.x = 0;
  moveMsg.linear.y = 0;
  moveMsg.linear.z = 0;

  moveMsg.angular.x = 0;
  moveMsg.angular.y = 0;
  moveMsg.angular.z = 0;

  ROS_INFO( "Flight hover %f", moveMsg.angular.z );
  msgMovePublisher.publish( moveMsg );
}

bool FlightCmdWrapper::check_drone_ready()
{
  bool isReady = false;
  ardrone_autonomy::LedAnim srv;

  srv.request.type      = 1;
  srv.request.freq      = 4;
  srv.request.duration  = 5;

  isReady = (srvLedClient.call(srv)) ? true : false;

  if (isReady)
    ROS_INFO( "Drone is ready!" );

  return isReady;
}
