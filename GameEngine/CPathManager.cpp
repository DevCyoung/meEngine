#include "pch.h"
#include "CPathManager.h"

CPathManager::CPathManager()
	:m_szContentPath{}
{
}

CPathManager::~CPathManager()
{
}


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
	this->render();
}

void CPathManager::render()
{
	//SetWindowText(CEngine::GetInst()->GetMainWnd(), m_szContentPath);
}
