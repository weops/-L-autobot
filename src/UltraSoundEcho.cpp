#include <we_autobot/UltraSoundEcho.h>
#include <time.h>

//int testGPIO(int inpin, int outpin){
int main(int argc, char **argv){
  ros::init( argc, argv, "usEcho" );
  ros::NodeHandle n;


  string echo = "27"; //echo
  GPIOClass* gpioEcho = new GPIOClass(echo); //create new GPIO object to be attached to  GPIO27
  gpioEcho->export_gpio(); //export GPIO27
  cout << " GPIO pins exported" << endl;

  gpioEcho->setdir_gpio("in"); // set to read echo
  cout << " Set GPIO pin directions" << endl;

  // time_t pulse_start;
  // time_t pulse_end;

  struct timeval pulse_start, pulse_end;
  string usstate;
  gpioEcho->getval_gpio(usstate);
  cout << " >> Waiting Echo  : "<< usstate << endl;
  while (usstate == "0"){
    //time(&pulse_start);
    gettimeofday(&pulse_start, NULL);
    gpioEcho->getval_gpio(usstate);
  }

  cout << " >> Receiving Echo : "<< usstate << endl;
  while (usstate == "1"){
    //time(&pulse_end);
    gettimeofday(&pulse_end, NULL);
    gpioEcho->getval_gpio(usstate);
  }

  cout << "Pulse Started @ " << pulse_start.tv_usec << endl;
  cout << "Pulse Ended   @ " << pulse_end.tv_usec << endl;
  cout << "Distance is "<< (pulse_end - pulse_start) * 0.000001 * 171.5 << "m"<< endl;

  cout << "Exiting....." << endl;

  gpioEcho->unexport_gpio();
  return 0;
}
