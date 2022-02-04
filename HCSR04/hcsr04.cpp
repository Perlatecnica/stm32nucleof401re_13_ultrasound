/* Copyright (c) 2022 Perlatecnica
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#include "hcsr04.h"

HCSR04::HCSR04(PinName TrigPin,PinName EchoPin):
    trigger(TrigPin), echo(EchoPin)
{
	trigger=0;
}

HCSR04::~HCSR04()
{
}


unsigned int HCSR04::get_dist_cm()
{
	// Run Trigger
	trigger=1;
	timer.reset();
	wait_us(10);
	trigger=0;

	//wait for echo high
	while (echo==0) {};

	//echo is high, so start timer
	timer.start();

	//wait for echo low
	while (echo==1) {};

	//stop timer and read value
	timer.stop();

	// Gather Echo Pulse duration
	echopulsedur = timer.elapsed_time().count();

	//scale to cm
	distance = (echopulsedur)/58.0;

	return distance;
}

float HCSR04::filter(int* measure, int n) {
	int temp;
	for(int i=0; i<n-1; i++) {
		for(int k=0; k<n-1-i; k++) {
			if(measure[k] > measure[k+1]) {
				temp = measure[k];
				measure[k] = measure[k+1];
				measure[k+1] = temp;
	        }
	     }
	 }
	if(n%2==0) {
	    int pos_1 = (int)n/2.0 + .5;
	    int pos_2 = (int)n/2.0 - .5;
		value = (measure[pos_1]+measure[pos_2])/2;
	} else {
		value = measure[n/2];
	}
	return value;
}

