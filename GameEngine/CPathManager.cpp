#include "pch.h"
#include "CPathManager.h"

CPathManager::CPathManager()
	: m_szContentPath{}
	, m_szMapPath{}
	, m_szAnimPath{}
	, m_szEffectath{}
	, m_szSoundPath{}
{
}

CPathManager::~CPathManager()
{
}

BOOL		wstrcomp(const wchar_t* a, const wchar_t* b);

void CPathManager::init()
{
	//윈도우 제공함수 실행파일기준 절대경로
	GetCurrentDirectory(256, m_szContentPath);
	//상위폴더로 감
	wchar_t  buff[256] = L"\\bin\\resource\\";
	wchar_t* temp = buff;
	wchar_t* str = m_szContentPath;
	while (*str)
		++str;
	while (*str != '\\')
		--str;
	while (*temp)
	{
		*str = *temp;
		++str;
		++temp;
	}
	*str = L'\0';
	// + bin\content	
	//디버깅 모드로 시작하면 프로젝트 경로를 알려준다.
	//vxcproj 경로를 알려줘버림.
	wstring contentPath = m_szContentPath;
	contentPath += +L"texture\\map\\";
	wcscpy_s(m_szMapPath, 256, contentPath.c_str());
	this->render();
}

void CPathManager::render()
{
	//SetWindowText(CEngine::GetInst()->GetMainWnd(), m_szContentPath);
}

void CPathManager::FulloRelativePath(wstring& fullpath)
{
	const wchar_t* str = fullpath.c_str();


	while (*str)
	{
		++str;
	}

	while (*str != L':')
	{
		if (*str == L'\\')
		{
		
			if (wstrcomp(str, L"\\resource"))
			{
				break; 
			}
			fullpath = (str + 1);
		}
		--str;
	}
}

BOOL		wstrcomp(const wchar_t* a, const wchar_t* b)
{
	while (*a || *b)
	{
		if (*a != *b)
			break;
		++a;
		++b;
	}
	if (*a == L'\0' || *b == L'\0')
		return TRUE;
	return FALSE;
}