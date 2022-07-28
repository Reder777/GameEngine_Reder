#include "reder.h"
#include "imgui.h"

class exampleLayer :public reder::layer {
public:

	exampleLayer():layer("example"){}

	virtual void imguiRender() override {
		ImGui::Begin("hello");
		ImGui::Text("world");
		ImGui::End();
	}

	void onUpdate() override {
#if SHOW_ALL_DEBUG_INFO
		RE_CLIENT_INFO("example layer update!");
#endif
#if SHOW_TEST_INFO
		if (reder::input::isKeyPressed(RE_KEY_TAB)) {
			RE_CLIENT_TRACE("tab pressed");
		}
		//reder's keyCode test 
#endif
	}
	void onEvent(reder::event& e) override {


#if SHOW_TEST_INFO
		RE_CLIENT_TRACE("{0}", e);
		if (e.getEventType() == reder::eventType::KeyPressed) {
			reder::keyPressedEvent& event = (reder::keyPressedEvent&)e;
			RE_CLIENT_TRACE("{0}", (char)event.getKeyCode());
		}
#endif

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