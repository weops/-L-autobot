#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main( int argc, char **argv)
{
    ros::init( argc, argv, "flight_control" );
    
    ros::NodeHandle n;

    ros::Rate loop_rate( 10 );

    while (ros::ok())
    {
        // your code
        //ROS_INFO( "testing" );
    }

    ros::spinOnce();
    loop_rate.sleep();

    return 0;
}

