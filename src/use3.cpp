#include <we_autobot/UltraSoundEcho.h>
#include <time.h>

//int testGPIO(int inpin, int outpin){
int main(int argc, char **argv){
  ros::init( argc, argv, "usEcho" );
  ros::NodeHandle n;

  // GPIO 22: Rear  Middle
  // GPIO 6 : Front Right
  // GPIO 19: Front Left

  GPIOClass* gpioRM = new GPIOClass("27");
  GPIOClass* gpioFR = new GPIOClass("6");
  GPIOClass* gpioFL = new GPIOClass("19");
  gpioRM->export_gpio();
  gpioFR->export_gpio();
  gpioFL->export_gpio();
  //cout << " GPIO pins exported" << endl;

  gpioRM->setdir_gpio("in");
  gpioFR->setdir_gpio("in");
  gpioFL->setdir_gpio("in");
  //cout << " Set GPIO pin directions" << endl;

  struct timeval rmStart, rmEnd, frStart, frEnd, flStart, flEnd;
  string rmState, frState, flState;
  double rmD, frD, flD;
  //TODO: NEED TO REPLACE LOOP COND WITH TERMINATE SIGNAL
  while(1){

    gpioRM->getval_gpio(rmState);
    gpioFR->getval_gpio(frState);
    gpioFL->getval_gpio(flState);

    // cout << " >> Waiting Echo  : "<< usstate << endl;
    if (rmState == "0" && rmEnd.tv_usec > rmStart.tv_usec){
      rmD = (rmEnd.tv_usec - rmStart.tv_usec) * 0.00001 * 171.5;
      cout << "Distance is "<< rmD << endl;
      gettimeofday(&rmStart, NULL);
    }else if (rmState == "0"){
      gettimeofday(&rmStart, NULL);
    }else{
      gettimeofday(&rmEnd, NULL);
    }

    if (frState == "0" && frEnd.tv_usec > frStart.tv_usec){
      frD = (frEnd.tv_usec - frStart.tv_usec) * 0.00001 * 171.5;
      //cout << "Distance is "<< frD << endl;
      gettimeofday(&frStart, NULL);
    }else if (frState == "0"){
      gettimeofday(&frStart, NULL);
    }else{
      gettimeofday(&frEnd, NULL);
    }
    if (flState == "0" && flEnd.tv_usec > flStart.tv_usec){
      flD = (flEnd.tv_usec - flStart.tv_usec) * 0.00001 * 171.5;
      //cout << "Distance is "<< flD << endl;
      gettimeofday(&flStart, NULL);
    }else if (flState == "0"){
      gettimeofday(&flStart, NULL);
    }else{
      gettimeofday(&flEnd, NULL);
    }
  }

  cout << "Exiting....." << endl;
  gpioRM->unexport_gpio();
  gpioFR->unexport_gpio();
  gpioFL->unexport_gpio();
  return 0;
}
