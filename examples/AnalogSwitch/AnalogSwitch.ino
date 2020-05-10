/*
 * Analog Switch Library Example
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

/*
 * With the library an analog input can be used
 * for a multi position switch.
 *
 * Begin a ANALOGSWITCH on an analog port and learn the
 * analog values of the positions.
 *
 * The get() method returns the position number (1-n).
 */


/*
 * HARDWARE
 *
 * +5V                        GND
 *  |                          |
 *  | ------ | ------ | ------ |
 *  --| R1 |---| R2 |---| R3 |--
 *  | ------ | ------ | ------ |
 *  |        |        |        |
 *  |  SW1   |  SW2   |  SW3   |
 *  ---/ -  ---/ -  ---/ -  ---/ -
 *       |       |       |       |
 *       ----------------------------------A0
 */

#include "AnalogSwitch.h"


ANALOGSWITCH sw;


void setup() {

	Serial.begin(115200);
	Serial.println("Start analog switch");

	// start using analog input A0
	sw.begin(A0);

	// set five points
	sw.learn(0);
	sw.learn(680);
	sw.learn(338);
	sw.learn(1023);

}


void loop() {

	Serial.print("Analog value: ");
	Serial.println(analogRead(A0));

	Serial.print(" > Switch position: ");
	Serial.println(sw.get());

	delay(1000);
	
}