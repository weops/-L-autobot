#ifndef ZX_SENSOR_H
#define ZX_SENSOR_H

#include <string>
using namespace std;
/* GPIO Class
 * Purpose: Each object instantiated from this class will control a GPIO pin
 * The GPIO pin number must be passed to the overloaded class constructor
 */
class ZXSensor
{
public:
    ZXSensor();  // create a GPIO object that controls GPIO4 (default)
    ZXSensor(int[] GPIO); // create a GPIO object that controls GPIOx, where x is passed to this constructor
private:
    string gpionum; // GPIO number associated with the instance of an object
};
 
#endif