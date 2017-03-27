/* Blue Robotics Arduino MS5837-30BA Pressure/Temperature Sensor Library
------------------------------------------------------------
 
Title: Blue Robotics Arduino MS5837-30BA Pressure/Temperature Sensor Library
Description: This library provides utilities to communicate with and to
read data from the Measurement Specialties MS5837-30BA pressure/temperature 
sensor.
Authors: Rustom Jehangir, Blue Robotics Inc.
         Adam �imko, Blue Robotics Inc.
-------------------------------
The MIT License (MIT)
Copyright (c) 2015 Blue Robotics Inc.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-------------------------------*/ 

#ifndef MS5837_H_BLUEROBOTICS
#define MS5837_H_BLUEROBOTICS

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>


class MS5837 {
public:
	static constexpr float Pa = 100.0f;
	static constexpr float bar = 0.001f;
	static constexpr float mbar = 1.0f;

	MS5837();

	void init();

	/** Provide the density of the working fluid in kg/m^3. Default is for 
	 * seawater. Should be 997 for freshwater.
	 */
	void setFluidDensity(float density);

	/** The read from I2C takes up for 40 ms, so use sparingly is possible.
	 */
	void read_pressure();

	/** This function loads the datasheet test case values to verify that
	 *  calculations are working correctly. No example checksum is provided
	 *  so the checksum test may fail.
	 */
	void readTestCase();

	/** Pressure returned in mbar or mbar*conversion rate.
	 */
	float getPressure(float conversion = 1.0f);

	/** Temperature returned in deg C.
	 */
	float getTemperature();

	/** Depth returned in meters (valid for operation in incompressible
	 *  liquids only. Uses density that is set for fresh or seawater.
	 */
	float getDepth();

	/** Altitude returned in meters (valid for operation in air only).
	 */
	float altitude();

    		void readlog(void);
    		FILE * pPRESFile;
    		char presfilename[100];
    		char presfile[50];
		struct timeval tval_before_pres;
		time_t nowtime;
        	struct tm *nowtm;

private:
	uint16_t C[8];
	uint32_t D1, D2;
	int32_t TEMP;
	int32_t P;

	float fluidDensity;

	/** Performs calculations per the sensor data sheet for conversion and
	 *  second order compensation.
	 */
	void calculate();

	uint8_t crc4(uint16_t n_prom[]);

	int file;
	int adapter_nr; 
	char filename[40];
};

#endif