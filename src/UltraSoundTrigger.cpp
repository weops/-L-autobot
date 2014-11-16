#include <we_autobot/UltrasonicSensor.h>
#include <time.h>

//int testGPIO(int inpin, int outpin){
int main(int argc, char **argv){
  ros::init( argc, argv, "usTrigger" );
  ros::NodeHandle n;

  string in = "22"; //button
  string inputstate = "1";
  GPIOClass* gpioIn = new GPIOClass(in); //create new GPIO object to be attached to  GPIO22
  gpioIn->export_gpio(); //export GPIO22

  string trig = "17"; //trigger
  GPIOClass* gpioTrig = new GPIOClass(trig); //create new GPIO object to be attached to  GPIO17
  gpioTrig->export_gpio(); //export GPIO17
  
  cout << " GPIO pins exported" << endl;

  gpioIn->setdir_gpio("in"); // GPIO27 set to input
  gpioTrig->setdir_gpio("out"); //set to output trigger
  cout << " Set GPIO pin directions" << endl;

  bool kill = 1;
  while(kill){
    usleep(500000);  // wait for 0.5 seconds
    gpioIn->getval_gpio(inputstate); //read state of GPIO22 input pin
    gpioEcho->getval_gpio(usstate); //read state of ultrasensor
    cout << "Current input pin state is " << inputstate  <<endl;
    if(inputstate == "0"){ // if input pin is at state "0" i.e. button pressed
      cout << "input pin state is \"Pressed \". Will check input pin state again in 20ms "<<endl;
      usleep(20000);
      cout << "Checking again ....." << endl;
      gpioIn->getval_gpio(inputstate); // checking again to ensure that state "0" is due to button press and not noise
      if(inputstate == "0"){
        cout << " Waiting until pin is unpressed....." << endl;
        while (inputstate == "0"){ 
          
          // turn off trigger
          cout << " >> Settling Trigger....." << endl;
          gpioTrig->setval_gpio("0");
          usleep(20000); //sleep for 0.2s

          // set trigger for 10us
          cout << " >> Pulse Trigger for 10us" << endl;
          gpioTrig->setval_gpio("1");
          usleep(10);
          gpioTrig->setval_gpio("0");


          gpioIn->getval_gpio(inputstate);
          // WHILE HOLD, TEST ULTRA SOUND
        };
        cout << "pin is unpressed" << endl;
        kill = 0;
      }
      else{
          cout << "input pin state is definitely \"UnPressed\". That was just noise." <<endl;
      }
    }
  }

  cout << "Exiting....." << endl;
  gpioIn->unexport_gpio();
  gpioTrig->unexport_gpio();
  return kill;
}
