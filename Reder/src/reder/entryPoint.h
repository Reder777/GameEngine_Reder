#pragma once
#ifdef RE_PLATFORM_WINDOWS

extern reder::application* reder::createSandbox();


int main(int argc, char** argv) {

	auto sandbox = reder::createSandbox();
	sandbox->run();
	delete sandbox;
}



#endif 
