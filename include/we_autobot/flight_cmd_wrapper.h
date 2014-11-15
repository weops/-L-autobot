#ifndef _FLIGHT_CMD_WRAPPER_H_
#define _FLIGHT_CMD_WRAPPER_H_


class FlightCmdWrapper
{
  public:
    enum ConnectMode
    {
      WIFI,
      TTL
    }

  private:
    ConnectMode connectMode;

  public:
    FlightCmdWrapper( ConnectMode mode );

}
