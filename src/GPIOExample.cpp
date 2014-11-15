#include "GPIOExample.h"

int testGPIO(int inpin, int outpin){
  string in = "22";
  string out = "27";
  string inputstate;
  GPIOClass* gpioOut = new GPIOClass(in); //create new GPIO object to be attached to  GPIO22
  GPIOClass* gpioIn = new GPIOClass(out); //create new GPIO object to be attached to  GPIO27

  gpioOut->export_gpio(); //export GPIO22
  gpioIn->export_gpio(); //export GPIO27

  cout << " GPIO pins exported" << endl;

  gpioOut->setdir_gpio("in"); //GPIO22 set to output
  gpioIn->setdir_gpio("out"); // GPIO27 set to input

  cout << " Set GPIO pin directions" << endl;
  bool kill = 1;
  while(kill)
  {
    usleep(500000);  // wait for 0.5 seconds
    gpioIn->getval_gpio(inputstate); //read state of GPIO17 input pin
    cout << "Current input pin state is " << inputstate  <<endl;
    if(inputstate == "0") // if input pin is at state "0" i.e. button pressed
    {
        cout << "input pin state is "Pressed ".n Will check input pin state again in 20ms "<<endl;
            usleep(20000);
                cout << "Checking again ....." << endl;
                gpioIn->getval_gpio(inputstate); // checking again to ensure that state "0" is due to button press and not noise
        if(inputstate == "0")
        {
            cout << "input pin state is definitely "Pressed". Turning LED ON" <<endl;
            gpioOut->setval_gpio("1"); // turn LED ON

            cout << " Waiting until pin is unpressed....." << endl;
            while (inputstate == "0"){ 
            gpioIn->getval_gpio(inputstate);
            };
            cout << "pin is unpressed" << endl;
            kill=0;
        }
        else
            cout << "input pin state is definitely "UnPressed". That was just noise." <<endl;

    }
    gpioOut->setval_gpio("0");

  }
  cout << "Exiting....." << endl;
  return kill;
}