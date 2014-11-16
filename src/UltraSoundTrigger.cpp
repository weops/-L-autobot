#include <we_autobot/UltraSoungTrigger.h>
#include <time.h>

//int testGPIO(int inpin, int outpin){
int main(int argc, char **argv){
  ros::init( argc, argv, "usTrigger" );
  ros::NodeHandle n;

  string in = "22"; //button
  string inputstate = "1";
  GPIOClass* gpioIn = new GPIOClass(in); //create new GPIO object to be attached to  GPIO22
  gpioIn->export_gpio(); //export GPIO22


  string out = "4"; //led
  GPIOClass* gpioOut = new GPIOClass(out); //create new GPIO object to be attached to  GPIO4
  gpioOut->export_gpio(); //export GPIO4

  string trig = "17"; //trigger
  GPIOClass* gpioTrig = new GPIOClass(trig); //create new GPIO object to be attached to  GPIO17
  gpioTrig->export_gpio(); //export GPIO17
  
  cout << " GPIO pins exported" << endl;

  gpioIn->setdir_gpio("in"); // GPIO27 set to input
  gpioOut->setdir_gpio("out"); //GPIO22 set to output
  gpioTrig->setdir_gpio("out"); //set to output trigger
  cout << " Set GPIO pin directions" << endl;

  bool kill = 10;
  while(kill > 0){
    usleep(500000);  // wait for 0.5 seconds
    gpioIn->getval_gpio(inputstate); //read state of GPIO22 input pin
    cout << "Current input pin state is " << inputstate  <<endl;
    if(inputstate == "0"){ // if input pin is at state "0" i.e. button pressed
      cout << "input pin state is \"Pressed \". Will check input pin state again in 20ms "<<endl;
      usleep(20000);
      cout << "Checking again ....." << endl;
      gpioIn->getval_gpio(inputstate); // checking again to ensure that state "0" is due to button press and not noise
      if(inputstate == "0"){
        gpioOut->setval_gpio("1"); // turn LED ON
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

          usleep(20000);
          gpioIn->getval_gpio(inputstate);
          // WHILE HOLD, TEST ULTRA SOUND
        };
        cout << "pin is unpressed" << endl;
        gpioOut->setval_gpio("0"); // turn LED OFF
        kill = kill - 1;
      }
      else{
          cout << "input pin state is definitely \"UnPressed\". That was just noise." <<endl;
      }
    }
  }
  cout << "Exiting....." << endl;
  gpioIn->unexport_gpio();
  gpioOut->unexport_gpio();
  gpioTrig->unexport_gpio();
  return kill;
}
