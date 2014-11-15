#ifndef _FLIGHT_CMD_WRAPPER_H_
#define _FLIGHT_CMD_WRAPPER_H_
#include "ros/ros.h"
#include <ardrone_autonomy/LedAnim.h>

enum ConnectMode
{
  WIFI,
  TTL
};


class FlightCmdWrapper
{
  public:
  private:
    ConnectMode connectMode;
    ros::NodeHandle n;
    ros::ServiceClient client;

  public:
    FlightCmdWrapper( ConnectMode mode ); // hide default constructor
    void LedAnimation();
    
    void flight_print();

  private:
};

#endif
