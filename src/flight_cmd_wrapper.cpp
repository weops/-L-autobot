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
}
