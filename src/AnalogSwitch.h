/*
 * Analog Switch Library Header
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

/*
 * With the library an analog input can be used
 * for a multi position switch 
 */


#ifndef ANALOGSWITCH_H
#define ANALOGSWITCH_H


#include <Arduino.h>


#define ANALOGSWITCH_MAX_POS 16
#define ANALOGSWITCH_MAX_ANALOG 1023


class ANALOGSWITCH {

	public:

		ANALOGSWITCH(void);

		void begin(uint8_t); // set the port

		uint8_t learn(void); // learn the position from analog input
		uint8_t learn(uint16_t); // store a position

		uint8_t remove(uint8_t); // remove position with index idx

		uint8_t get(void); // get the switch position

	private:
		uint8_t _port; // port number
		uint16_t _positions[ANALOGSWITCH_MAX_POS]; // up to 16 positions
		uint8_t _pos_count; // count of stored positions

		uint16_t _min[ANALOGSWITCH_MAX_POS];
		uint16_t _max[ANALOGSWITCH_MAX_POS];

		uint16_t get_analog(void);
		void update(void); // update min and max values
		void sort(void); // sort the positions

};


#endif