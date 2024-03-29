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


  cout << " >> Pulse Trigger for 1ms / 100ms" << endl;
  while(1){
    // turn off trigger
    gpioTrig->setval_gpio("0");
    usleep(100000); //sleep for 0.1s

    // set trigger for 10us
    gpioTrig->setval_gpio("1");
    usleep(1000);
  }
  cout << "Exiting....." << endl;
  gpioTrig->unexport_gpio();
  return 0;
}
