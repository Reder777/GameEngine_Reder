#pragma once

/*
ignore scanf,strcpy,strcat warning everywhere
*/
#define _CRT_SECURE_NO_WARNINGS
/*
precompile header file 
*/

#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <string>

#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <array>
#include <reder/debug/instrumentor.h>

#ifdef RE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif