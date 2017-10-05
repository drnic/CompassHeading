#include <CompassHeading.h>

CompassHeading::CompassHeading(float declinationAngle)
{
  /* Assign a unique ID to this sensor at the same time */
  _mag = Adafruit_HMC5883_Unified(12345);
  _declinationAngle = declinationAngle;
}

void CompassHeading::start()
{
  if(!_mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring, and reset!");
    while(1);
  }
}

float CompassHeading::headingDegrees()
{
  /* Get a new sensor event */
  sensors_event_t event;
  _mag.getEvent(&event);

  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  if (DEBUG) {
    Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
  }

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);

  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  heading += _declinationAngle;

  // Correct for when signs are reversed.
  if(heading < 0) {
    heading += 2*PI;
  }

  // Check for wrap due to addition of declination.
  if(heading > 2*PI) {
    heading -= 2*PI;
  }

  // Convert radians to degrees for readability.
  return heading * 180/M_PI;
}

void CompassHeading::displaySensorDetails(void)
{
  sensor_t sensor;
  _mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
  Serial.println("------------------------------------");
  Serial.println("");
}
