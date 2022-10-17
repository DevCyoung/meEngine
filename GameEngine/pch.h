#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <crtdbg.h>
#include <vector> 
#include <list>
#include <map>
#include <string>
#include <assert.h>
#include <commdlg.h>

using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::string;
using std::wstring;

#include "function.h"
#include "define.h"
#include "struct.h"


//미리컴파일된 헤더는 상대적으로 컴파일속도가 빨라진다. 강제적으로 모든곳에서 알게할수있다.




//라이브러리 링킹연결해달라는말
//ParentBitBlit
#pragma comment (lib, "Msimg32.lib")
#pragma comment(lib,"winmm.lib")