#include "reder.h"

class exampleLayer :public reder::layer {
public:
	exampleLayer():layer("example"){}

	void onUpdate() override {
		RE_CLIENT_INFO("example layer update!");
	}

	void onEvent(reder::event& e) override {
		RE_CLIENT_TRACE("{0}", e);
	}
};


class Sandbox :public reder::application {

public:

	Sandbox() {
		pushLayer(new exampleLayer());
	}

	~Sandbox() {

	}
};


reder::application* reder::createSandbox() {
	printf("this is the first sandbox!");
	return new Sandbox();
}