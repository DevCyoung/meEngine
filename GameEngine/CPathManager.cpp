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
	//������ �����Լ� �������ϱ��� ������
	GetCurrentDirectory(256, m_szContentPath);
	//���������� ��
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
	//����� ���� �����ϸ� ������Ʈ ��θ� �˷��ش�.
	//vxcproj ��θ� �˷������.
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