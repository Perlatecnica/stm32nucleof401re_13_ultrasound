/* Copyright (c) 2017 STMicroelectronics
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/****************************************************
*           RAPID PROTOTYPING WITH NUCLEO           *
* Example Code 06: Variable resistor                *
* Author: Mauro D'Angelo                            *
* Organization: Perlatecnica APS ETS                *
*****************************************************/

#include "mbed.h"
#include "hcsr04.h"

UnbufferedSerial pc(USBTX,USBRX);
DigitalOut led(LED1);

HCSR04 sensor(PA_8, PB_10);

int main() {

    int i=0;
    int measure[5];
    float averageValue;

    // Main loop
    while(1) {
    	led = !led;

		// Reading the measure of the distance
        measure[i] = sensor.get_dist_cm();
        i++;

		// It calculates the average every 5 samples
        if(i==5){
            averageValue = sensor.filter(measure, 5);
            // Stampa sulla seriale la misura della distanza in cm
            printf("%.0f cm\r\n", averageValue);
        	i = 0;
        }

        // Wait for 100 ms before reading the distance measured
        ThisThread::sleep_for(100ms);
    }
}
