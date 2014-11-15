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
}

void FlightCmdWrapper::flight_print()
{
  printf( "connection mode: %d\n", connectMode );
}
