#pragma once
#include "../debug/instrumentor.h"
#ifdef RE_PLATFORM_WINDOWS

extern reder::application* reder::createSandbox();

/*
this is the only entry main function in all files
different apps defines different action all according to the main function 
*/
int main(int argc, char** argv) {
	RE_PROFILE_BEGIN_SESSION("init", "assets/profileJson/main-init.json");
	reder::log::init();
	auto sandbox = reder::createSandbox();
	RE_PROFILE_END_SESSION();

	RE_PROFILE_BEGIN_SESSION("run", "assets/profileJson/main-run.json");
	sandbox->run();
	RE_PROFILE_END_SESSION();

	RE_PROFILE_BEGIN_SESSION("end", "assets/profileJson/main-end.json");
	delete sandbox;
	RE_PROFILE_END_SESSION();
}



#endif 
