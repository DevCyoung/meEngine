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

#include "CAtlasEdit.h"

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

	m_atlasEditor = new CAtlasEdit();
	AddObject(m_atlasEditor, LAYER::MOUSE);

	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MOUSE, LAYER::WALL);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MOUSE, LAYER::PLAYER);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MOUSE, LAYER::MONSTER);
	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MOUSE, LAYER::OBJECT);


	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::MONSTER, LAYER::WALL);

}


CEditorLevel::~CEditorLevel()
{	
	//DeleteMenu �� ���� ���� �� �����ϳ��� �����
	//DestroyMenu �޴������� ���������Ҷ�
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);

}

void CEditorLevel::Save()
{
	//assert(m_backGround);
	/* open a file name
	�̹� ������� �����쿡�� �������ִ� �ſ����� ��޹���� ������
	�ش�â�� �׳� Path ���ڿ��� �����һ���*/
	OPENFILENAME ofn = {};
	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetMapPath();


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));														//
	ofn.lStructSize = sizeof(ofn);														//
	ofn.hwndOwner = NULL;																//
	ofn.lpstrFile = szFilePath;															//
	ofn.lpstrFile[0] = '\0';															//
	ofn.nMaxFile = 256;																	//
	ofn.lpstrFilter = L"MAP\0*.map";						//�ǽ��� �ִϸ��̼�
	ofn.nFilterIndex = 1;																//�⺻��������
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//�Ź� �ʿ���°�θ����� ��ȿ�����̱⶧���� �װ���������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	//���̾�α׿���
	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");
	assert(pFile);

	m_atlasEditor->Save(pFile);
	m_collideEditor->Save(pFile);
	m_objectEditor->Save(pFile);

	fclose(pFile);
}

void CEditorLevel::Load()
{
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetMapPath();

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));														//
	ofn.lStructSize = sizeof(ofn);														//
	ofn.hwndOwner = NULL;																//
	ofn.lpstrFile = szFilePath;															//
	ofn.lpstrFile[0] = '\0';															//
	ofn.nMaxFile = 256;																	//
	ofn.lpstrFilter = L"MAP\0*.map";													//�ǽ��� �ִϸ��̼�
	ofn.nFilterIndex = 1;																//�⺻��������
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//�Ź� �ʿ���°�θ����� ��ȿ�����̱⶧���� �װ���������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	if (false == GetOpenFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");
	assert(pFile);

	m_atlasEditor->Load(pFile);
	m_collideEditor->Load(pFile);
	m_objectEditor->Load(pFile);

	fclose(pFile);
}

void CEditorLevel::Load(const wstring& relativePath)
{
	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetMapPath();

	wchar_t szFilePath[256] = {};

	FILE* pFile = nullptr;
	strTileFolderPath += relativePath;
	_wfopen_s(&pFile, strTileFolderPath.c_str(), L"rb");
	assert(pFile);

	m_atlasEditor->Load(pFile);
	m_collideEditor->Load(pFile);
	m_objectEditor->Load(pFile);


	fclose(pFile);
}
void CEditorLevel::tick()
{
	//�������������� ƽ���������
	CLevel::tick();

	if (IS_INPUT_RELEASE(KEY::F))
	{
		GETINSTANCE(CCamera)->CameraKeyMove(300.f);
	}
	else
	{
		GETINSTANCE(CCamera)->CameraKeyMove(1300.f);
	}
	

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
	if (IS_INPUT_TAB(KEY::_4))
	{
		Save();
	}
	if (IS_INPUT_TAB(KEY::_5))
	{
		Load();
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
		m_atlasEditor->Update();
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
	//map ��Ʋ�� ����

	//ī�޶������

	//�÷��̾� ������





	//������Ʈ����(����, �浹ü, �����浹ü)
	//������
	//LAYEY ������������

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