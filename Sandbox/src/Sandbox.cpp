#include "reder.h"

class Sandbox :public reder::application {

public:

	Sandbox() {

	}

	~Sandbox() {

	}
};


reder::application* reder::createSandbox() {
	printf("this is the first sandbox!");
	return new Sandbox();
}