#include <we_autobot/UltrasonicSensor.h>

//int testGPIO(int inpin, int outpin){
int main(int argc, char **argv){
  ros::init( argc, argv, "testUltraSense" );
  ros::NodeHandle n;

  string in = "22"; //button
  string out = "7"; //led
  string inputstate;
  GPIOClass* gpioOut = new GPIOClass(in); //create new GPIO object to be attached to  GPIO22
  GPIOClass* gpioIn = new GPIOClass(out); //create new GPIO object to be attached to  GPIO7
  gpioOut->export_gpio(); //export GPIO22
  gpioIn->export_gpio(); //export GPIO7

  string trig = "17"; //trigger
  string echo = "27"; //echo
  string usstate; //us state
  GPIOClass* gpioTrig = new GPIOClass(trig); //create new GPIO object to be attached to  GPIO17
  GPIOClass* gpioEcho = new GPIOClass(echo); //create new GPIO object to be attached to  GPIO27
  gpioTrig->export_gpio(); //export GPIO17
  gpioEcho->export_gpio(); //export GPIO27
  
  cout << " GPIO pins exported" << endl;

  gpioOut->setdir_gpio("out"); //GPIO22 set to output
  gpioIn->setdir_gpio("in"); // GPIO27 set to input

  gpioTrig->setdir_gpio("out"); //set to output trigger
  gpioEcho->setdir_gpio("in"); // set to read echo
  cout << " Set GPIO pin directions" << endl;

  bool kill = 1;
  while(kill){
    usleep(500000);  // wait for 0.5 seconds
    gpioIn->getval_gpio(inputstate); //read state of GPIO17 input pin
    gpioEcho->getval_gpio(usstate); //read state of ultrasensor
    cout << "Current input pin state is " << inputstate  <<endl;
    if(inputstate == "0"){ // if input pin is at state "0" i.e. button pressed
      cout << "input pin state is \"Pressed \".n Will check input pin state again in 20ms "<<endl;
      usleep(20000);
      cout << "Checking again ....." << endl;
      gpioIn->getval_gpio(inputstate); // checking again to ensure that state "0" is due to button press and not noise
      if(inputstate == "0"){
        cout << "input  pin state is definitely \"Pressed\". Turning LED ON" <<endl;
        gpioOut->setval_gpio("1"); // turn LED ON

        cout << " Waiting until pin is unpressed....." << endl;
        while (inputstate == "0"){ 
          gpioIn->getval_gpio(inputstate);
        };
        cout << "pin is unpressed" << endl;
      }
      else{
          cout << "input pin state is definitely \"UnPressed\". That was just noise." <<endl;
      }
    }
    gpioOut->setval_gpio("0");
  }
  cout << "Exiting....." << endl;
  gpioOut->unexport_gpio();
  gpioIn->unexport_gpio();
  return kill;
}
