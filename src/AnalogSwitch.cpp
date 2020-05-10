/*
 * Analog Switch Library
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

/*
 * With the library an analog input can be used
 * for a multi position switch 
 */


#include "AnalogSwitch.h"


ANALOGSWITCH::ANALOGSWITCH(void) {
	_port = false;
}


// start at port number
void ANALOGSWITCH::begin(uint8_t port) {
	_port = port;
}


// get switch position
uint8_t ANALOGSWITCH::get(void) {

	uint8_t i = 0;

	// get analog value
	uint16_t analogval = get_analog();

	// calculate switch position
	// iterate positions
	while (i < _pos_count) {

		// check position
		// return current counter+1 (valid positions start at 1)
		// return 0: no position found
		if (_min[i] <= analogval && analogval <= _max[i]) {
			i++;
			break;
		}

		i++;
	}

	return i;
}


// learn position
// returns new position count
uint8_t ANALOGSWITCH::learn() {

	// has free value
	if (_pos_count < ANALOGSWITCH_MAX_POS) {
		_positions[_pos_count] = get_analog();
		_pos_count++;
	}

	sort();
	update();

	return _pos_count;
}


uint8_t ANALOGSWITCH::learn(uint16_t value) {

	// has free value
	if (_pos_count < ANALOGSWITCH_MAX_POS) {
		_positions[_pos_count] = value;
		_pos_count++;
	}

	sort();
	update();

	return _pos_count;
}


// remove position with index n
uint8_t ANALOGSWITCH::remove(uint8_t idx) {

	// index is valid and count not null
	if (idx < _pos_count && _pos_count > 0) {

		uint8_t i = idx;

		while (i<_pos_count) {
			_positions[i] = _positions[i+1];
			i++;
		}

		_pos_count--;
	}

	sort();
	update();

	return _pos_count;
}


// update min and max values
void ANALOGSWITCH::update(void) {

	uint8_t i = 0;

Serial.println();

	// calculate switch position
	// iterate positions
	while (i < _pos_count) {

		// get lower limit
		// not at the beginn
		if (i > 0) {
			_min[i] = ((_positions[i] - _positions[i-1]) / 2) + _positions[i-1];
		}
		else {
			_min[i] = 0;
		}


		// get upper limit
		// not at the end
		if (i < (_pos_count - 1)) {
			_max[i] = ((_positions[i+1] - _positions[i]) / 2) + _positions[i] - 1;
		}
		else {
			_max[i] = ANALOGSWITCH_MAX_ANALOG;
		}

		i++;
	}
}


// sort positions ascending
void ANALOGSWITCH::sort(void) {

	uint16_t i;
	uint16_t o;
	uint16_t temp;

    for(i = 0; i < (_pos_count-1); i++) {

        for(o = 0; o < (_pos_count-(i+1)); o++) {

			if(_positions[o] > _positions[o+1]) {

				temp = _positions[o];
				_positions[o] = _positions[o+1];
				_positions[o+1] = temp;
			}
        }
    }

}


// get analog value
uint16_t ANALOGSWITCH::get_analog(void) {
	if (_port) {
		return analogRead(_port);
	}

	return false;
}