#ifndef _FLIGHT_CMD_WRAPPER_H_
#define _FLIGHT_CMD_WRAPPER_H_
#include "std_msgs/Empty.h"
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
    ConnectMode         connectMode;
    ros::NodeHandle     n;
    ros::ServiceClient  srvLedClient;
    ros::Publisher      msgLandPublisher;
    ros::Publisher      msgLaunchPublisher;

  public:
    FlightCmdWrapper( ConnectMode mode ); // hide default constructor
    void led_animation();
    
    void flight_launch();
    void flight_land();
    void flight_print();

  private:
};

#endif
