#include <we_autobot/UltraSoundTrigger.h>
#include <time.h>

//int testGPIO(int inpin, int outpin){
int main(int argc, char **argv){
  ros::init( argc, argv, "usTrigger" );
  ros::NodeHandle n;

  // GPIO 27: Rear  Middle
  // GPIO 5 : Front Right
  // GPIO 13: Front Left
  GPIOClass* gpioRM = new GPIOClass("17"); 
  GPIOClass* gpioFR = new GPIOClass("5");
  GPIOClass* gpioFL = new GPIOClass("13");  
  gpioRM->export_gpio();
  gpioFR->export_gpio();
  gpioFL->export_gpio();
  //cout << " GPIO pins exported" << endl;

  gpioRM->setdir_gpio("out");
  gpioFR->setdir_gpio("out");
  gpioFL->setdir_gpio("out");
  //cout << " Set GPIO pin directions" << endl;

  gpioRM->setval_gpio("0");
  gpioFR->setval_gpio("0");
  gpioFL->setval_gpio("0");
  cout << " >> Pulse Trigger for 1ms / 100ms" << endl;

  usleep(100000); //sleep for 0.1s
  //TODO: NEED TO REPLACE LOOP COND WITH TERMINATE SIGNAL
  while(1){
    // turn off trigger
    gpioRM->setval_gpio("0");
    gpioFL->setval_gpio("0");
    usleep(100000); //sleep for 0.1s

    // set trigger for 10us
    gpioRM->setval_gpio("1");
    gpioFR->setval_gpio("1");
    usleep(1000);

    // turn off trigger
    gpioRM->setval_gpio("0");
    gpioFR->setval_gpio("0");
    usleep(100000); //sleep for 0.1s

    // set trigger for 10us
    gpioRM->setval_gpio("1");
    gpioFL->setval_gpio("1");
    usleep(1000);
  }

  cout << "Exiting....." << endl;
  gpioRM->unexport_gpio();
  gpioFR->unexport_gpio();
  gpioFL->unexport_gpio();
  return 0;
}
