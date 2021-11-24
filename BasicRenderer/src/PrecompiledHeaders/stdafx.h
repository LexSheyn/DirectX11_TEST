#ifndef STDAFX_H
#define STDAFX_H

// Custom types
typedef          bool      bool8;

typedef          char      char8;

typedef signed   char      int8;
typedef signed   short     int16;
typedef signed   int       int32;
typedef signed   long long int64;

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef float              float32;
typedef double             float64;

// Constants
#define Pi_float32 3.141592f
#define Pi_float64 3.14159265358979323846

// Windows 10 x64
//#include "Win10/win_setup.h"

// DirectX 11
#include "Win10/directx_setup.h"

// C++ core
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <math.h>
#include <unordered_map>
#include <map>
#include <exception>
#include <queue>
#include <bitset>
#include <optional>
#include <memory>

#endif // STDAFX_H