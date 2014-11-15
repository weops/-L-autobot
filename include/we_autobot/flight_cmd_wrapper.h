#ifndef _FLIGHT_CMD_WRAPPER_H_
#define _FLIGHT_CMD_WRAPPER_H_

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

  public:
    FlightCmdWrapper( ConnectMode mode ); // hide default constructor
    
    void flight_print();

  private:
};

#endif
