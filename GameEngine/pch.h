#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
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


//�̸������ϵ� ����� ��������� �����ϼӵ��� ��������. ���������� �������� �˰��Ҽ��ִ�.




//���̺귯�� ��ŷ�����ش޶�¸�
//ParentBitBlit
#pragma comment (lib, "Msimg32.lib")
#pragma comment(lib,"winmm.lib")