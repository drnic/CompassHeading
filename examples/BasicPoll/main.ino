#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <CompassHeading.h>

// Explanation and first-person pronoun from
//   https://raw.githubusercontent.com/adafruit/Adafruit_HMC5883_Unified/master/examples/magsensor/magsensor.ino
// Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
// Find yours here: http://www.magnetic-declination.com/
// Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
// If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
#define DECLINATION_ANGLE 0.22
CompassHeading compass = CompassHeading(DECLINATION_ANGLE);

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Compass Heading Test"); Serial.println("");

  /* Initialise the sensor. Blocks if not found. */
  compass.start();

  /* Display some basic information on this sensor */
  compass.displaySensorDetails();
  delay(500);
}

void loop(void)
{
  float heading = compass.headingDegrees();
  Serial.print("Heading (degrees): "); Serial.println(heading);

  delay(500);
}
