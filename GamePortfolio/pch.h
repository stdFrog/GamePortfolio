#pragma once
#define RELEASE_VERSION_INFO 100

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Common Utility Library
#include "StandardLibrary.h"
#include "GameMath.h"
#include "Vector.h"
#include "Matrix.h"
#include "Transform.h"
#include "WindowsUtility.h"

// Global Manager
#include "InputManager.h"

// Common User Defines Library
#include "ObjectHeaders.h"
// #include "LineMesh.h"
#include "SceneHeaders.h"
#include "EngineHeaders.h"
#include "GameRenderer.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type

#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "winmm")
#pragma comment(lib, "dsound")