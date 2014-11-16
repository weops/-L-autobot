#include <we_autobot/UltraSoundTrigger.h>
#include <time.h>

//int testGPIO(int inpin, int outpin){
int main(int argc, char **argv){
  ros::init( argc, argv, "usTrigger" );
  ros::NodeHandle n;

  string trig = "17"; //trigger
  GPIOClass* gpioTrig = new GPIOClass(trig); //create new GPIO object to be attached to  GPIO17
  gpioTrig->export_gpio(); //export GPIO17
  cout << " GPIO pins exported" << endl;

  gpioTrig->setdir_gpio("out"); //set to output trigger
  cout << " Set GPIO pin directions" << endl;

  while(1){
    // turn off trigger
    cout << " >> Settling Trigger....." << endl;
    gpioTrig->setval_gpio("0");
    usleep(10000); //sleep for 0.01s

    // set trigger for 10us
    cout << " >> Pulse Trigger for 10us" << endl;
    gpioTrig->setval_gpio("1");
    usleep(100);
    gpioTrig->setval_gpio("0");
  }
  cout << "Exiting....." << endl;
  gpioTrig->unexport_gpio();
  return 0;
}
