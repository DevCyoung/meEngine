#include "pch.h"
#include "CEditorLevel.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CTile.h"
#include "resource.h"
#include "CLevelManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"
#include "CUI.h"
#include "CButton.h"




//Map
#include "CRenderHelper.h"
#include "CMonster.h"

CTexture* mapText;

CEditorLevel::CEditorLevel()
	: m_hMenu(nullptr)
	, m_eMode(EDITOR_MODE::NONE)
	, m_lineColPreMouse(nullptr)
	, m_objCurmap(nullptr)
	, lineCol(nullptr)
	, MouseX(nullptr)
    , MouseY(nullptr)
	, m_LineMosueMode{}
	, size(40.f)
	, m_backGround(nullptr)
{
	//mapText = GETINSTANCE(CResourceManager)->LoadTexture(L"CYBER", L"texture\\cyberspace.bmp");
	//CMonster* monster = new CMonster();
	//this->AddObject(monster, LAYER::MONSTER);

}

CEditorLevel::~CEditorLevel()
{	
	//DeleteMenu �� ���� ���� �� �����ϳ��� �����
	//DestroyMenu �޴������� ���������Ҷ�
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);

}


void CEditorLevel::tick()
{
	//�������������� ƽ���������
	CLevel::tick();
	


	if (IS_INPUT_TAB(KEY::_1))
	{
		m_eMode = EDITOR_MODE::TILE;
	}
	if (IS_INPUT_TAB(KEY::_2))
	{
		m_eMode = EDITOR_MODE::ANIMATION;
	}
	if (IS_INPUT_TAB(KEY::_3))
	{
		m_eMode = EDITOR_MODE::OBJECT;
	}
	if (IS_INPUT_TAB(KEY::_4))
	{
		StartMapEditMode();
		m_eMode = EDITOR_MODE::LINECOLLIDER;
	}

	
	if (IS_INPUT_TAB(KEY::ENTER))
	{		
		//CLevelManager::LoadLevel(LEVEL_TYPE::TITLE);
	}
	GETINSTANCE(CCamera)->CameraKeyMove(1200.f);



	Update();
}

void CEditorLevel::render(HDC _dc)
{
	//assert(mapText);

	CLevel::render(_dc);



}



void CEditorLevel::Update()
{
	switch (m_eMode)
	{
	case EDITOR_MODE::TILE:
		CreateTileMode();
		break;
	case EDITOR_MODE::ANIMATION:
		break;
	case EDITOR_MODE::OBJECT:
		//CreateObjectMode();
		break;	
	case EDITOR_MODE::LINECOLLIDER:
		CreateLineMode();
		break;
	}
}


void CEditorLevel::Enter()
{
	//�޴��ٻ���
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_GAMEENGINE));
	}

	HWND hWnd = GETINSTANCE(CEngine)->GetMainWnd();
	SetMenu(hWnd, m_hMenu);
	
	POINT ptWndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CEngine)->WindowReSize(ptWndScreenSize.x, ptWndScreenSize.y);



	//�ʱ� ������Ʈ ����
	init();
}

void CEditorLevel::Exit()
{
	//�޴��ٻ̱�
	HWND hWnd = GETINSTANCE(CEngine)->GetMainWnd();
	SetMenu(hWnd, nullptr);

	POINT ptWndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CEngine)->WindowReSize(ptWndScreenSize.x, ptWndScreenSize.y);
	this->DeleteAllObject();
}

void CEditorLevel::UpdateLineCollider()
{
	
}

void CEditorLevel::UpdateAnimation()
{
}

void CEditorLevel::UpdateObject()
{
}

