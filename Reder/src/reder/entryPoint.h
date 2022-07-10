#pragma once
#ifdef RE_PLATFORM_WINDOWS

extern reder::application* reder::createSandbox();


int main(int argc, char** argv) {
	reder::log::init();
	RE_CORE_INFO("this is first info!");
	RE_CLIENT_WARN("this is first warn!");
	auto sandbox = reder::createSandbox();
	sandbox->run();
	delete sandbox;
}



#endif 
