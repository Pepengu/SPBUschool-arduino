#include "snake.h"

ring_buffer<uint8_t, 16> rb;

void setup(){
	Serial.begin(9600);
	
	rb.push_back(123);
	rb.push_front(42);

	for(int i = 0; i < rb.size(); ++i){
		Serial.print(rb[i], " ");
	}

	Serial.println(rb.back());
	Serial.println(rb.pop_front());
	Serial.println(rb.front());
	Serial.println(rb.pop_back());
	Serial.println(rb.size());
}
