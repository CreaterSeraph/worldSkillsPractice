#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <optional>
#include <thread>
#include <algorithm>
#include <string>
#include <array>
#include <random>
#include <math.h>
#include <bitset>
#include <queue>
#include <cmath>
#include <string_view>
#include <filesystem>

using namespace std;

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl
#else
#define DEBUG_LOG(log)
#endif

const int WINSIZEX = 1280;
const int WINSIZEY = 720;

extern POINT ptMouse;

#define Device DXUTGetD3D9Device()

#include "cTransform.h"
#include "texture.h"
#include "font.h"
#include "cKeyManager.h"
#include "cSceneManager.h"
#include "cImageManager.h"
#include "randManager.h"