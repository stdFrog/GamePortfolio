#pragma once

#include <map>
#include <set>
#include <list>
#include <array>
#include <memory>
#include <vector>
#include <string>
#include <format>
#include <iostream>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>

#include <assert.h>
#pragma comment(lib, "MsImg32")

/*
	깊이 버퍼 대신 그려줄 순서를 정하는 간단한 방법으로 열거형 타입을 택했다.
*/
enum LAYER_TYPE {
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	LAYER_UI,

	LAYER_TYPE_LAST_COUNT
};

enum COLLISION_LAYER_TYPE {
	CLT_OBJECT = 0x1,
	CLT_GROUND = 0x2,
	CLT_WALL = 0x4
};