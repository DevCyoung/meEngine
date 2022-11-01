#include "pch.h"
#include "CEditorLevel.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CTile.h"
#include "resource.h"

#include "CUI.h"
#include "CButton.h"




//Map
#include "CRenderHelper.h"
#include "CMonster.h"
#include "CLineColManager.h"

//Editor
#include "CCollideEdit.h"

//Manager
#include "CLevelManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"
#include "CCollisionManager.h"
#include "CObjectEdit.h"

CTexture* mapText;

CEditorLevel::CEditorLevel()
	: m_hMenu(nullptr)
	, m_eMode(EDITOR_MODE::NONE)
	, m_collideEditor(nullptr)
{
	//mapText = GETINSTANCE(CResourceManager)->LoadTexture(L"CYBER", L"texture\\cyberspace.bmp");
	//CMonster* monster = new CMonster();
	//this->AddObject(monster, LAYER::MONSTER);
	//m_wallDir = WALLDIR::LEFT;
	m_collideEditor = new CCollideEdit();
	AddObject(m_collideEditor, LAYER::MOUSE);

	m_objectEditor = new CObjectEdit();
	m_objectEditor->CreateUI(this);
	AddObject(m_objectEditor, LAYER::MOUSE);

	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MOUSE, LAYER::WALL);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MOUSE, LAYER::PLAYER);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MOUSE, LAYER::MONSTER);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MOUSE, LAYER::OBJECT);
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

	GETINSTANCE(CCamera)->CameraKeyMove(1200.f);

	if (IS_INPUT_TAB(KEY::_1))
	{
		m_eMode = EDITOR_MODE::ATLAS;
	}
	if (IS_INPUT_TAB(KEY::_2))
	{
		m_eMode = EDITOR_MODE::COLLIDE;
	}
	if (IS_INPUT_TAB(KEY::_3))
	{
		m_eMode = EDITOR_MODE::OBJECT;
	}
	if (IS_INPUT_TAB(KEY::ESE))
	{
		//refresh
	}
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
	case EDITOR_MODE::ATLAS:
		break;
	case EDITOR_MODE::COLLIDE:
		m_collideEditor->Update();
		break;
	case EDITOR_MODE::OBJECT:
		m_objectEditor->Update();
		break;
	}
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

void CEditorLevel::SaveGame()
{

}

#pragma region ENTER_EXIT

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

#pragma endregion