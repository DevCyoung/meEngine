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
	this->render();
}

void CPathManager::render()
{
	//SetWindowText(CEngine::GetInst()->GetMainWnd(), m_szContentPath);
}
