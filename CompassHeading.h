#ifndef CompassHeading_h
#define CompassHeading_h

#ifndef DEBUG
#define DEBUG false
#endif

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

class CompassHeading
{
  public:
    CompassHeading(float declinationAngle);

    void start();
    float headingDegrees();
    void displaySensorDetails(void);

  private:
    float _declinationAngle;
    Adafruit_HMC5883_Unified _mag;
};

#endif
