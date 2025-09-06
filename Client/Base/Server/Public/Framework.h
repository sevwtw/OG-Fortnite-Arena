#pragma once

// Windows Header Files
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <intrin.h>
#include <sstream>
#include <array>
#include <tlhelp32.h>
#include <future>
#include <set>

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

#include <Server/SDK/SDK.hpp>
#pragma comment(lib, "minhook/minhook.lib")

using namespace SDK;

static uintptr_t ImageBase = InSDKUtils::GetImageBase();

namespace Framework {
	static void ExampleFunction();
}