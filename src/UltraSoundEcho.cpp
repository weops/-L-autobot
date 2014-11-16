#include <we_autobot/UltrasonicSensor.h>
#include <time.h>

//int testGPIO(int inpin, int outpin){
int main(int argc, char **argv){
  ros::init( argc, argv, "usEcho" );
  ros::NodeHandle n;

  string out = "4"; //led
  GPIOClass* gpioOut = new GPIOClass(out); //create new GPIO object to be attached to  GPIO4
  gpioOut->export_gpio(); //export GPIO4

  string echo = "27"; //echo
  string ussate = "1";
  GPIOClass* gpioEcho = new GPIOClass(echo); //create new GPIO object to be attached to  GPIO27
  gpioEcho->export_gpio(); //export GPIO27
  
  cout << " GPIO pins exported" << endl;

  gpioOut->setdir_gpio("out"); //GPIO22 set to output
  gpioEcho->setdir_gpio("in"); // set to read echo
  cout << " Set GPIO pin directions" << endl;

  bool kill = 1;


  time_t pulse_start;
  time_t pulse_end;
  cout << " >> Waiting Echo  : "<< usstate << endl;
  while (usstate == "0"){
    time(&pulse_start);
    gpioEcho->getval_gpio(usstate);
  }
  gpioOut->setval_gpio("1"); // turn LED ON
  cout << " >> Receiving Echo : "<< usstate << endl;
  while (usstate == "1"){
    time(&pulse_end);
    gpioEcho->getval_gpio(usstate);
  }
  gpioOut->setval_gpio("0"); // turn LED OFF
  cout << "Distance is "<< (pulse_end - pulse_start) * 17150 << endl;

  cout << "Exiting....." << endl;
  gpioOut->unexport_gpio();
  gpioEcho->unexport_gpio();
  return kill;
}
