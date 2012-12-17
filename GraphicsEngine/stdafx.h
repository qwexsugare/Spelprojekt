#ifndef STDAFX_H
#define STDAFX_H

#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <Windows.h>
#include <D3D10.h>
#include <D3DX10.h>

#include <vector>
#include <string>
using namespace std;

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

#endif