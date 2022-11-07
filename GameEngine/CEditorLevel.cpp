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
	//DeleteMenu 는 파일 도움말 등 파일하나를 지우는
	//DestroyMenu 메뉴단위가 없어져야할때
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);

}

void CEditorLevel::Save()
{
	//assert(m_backGround);
	/* open a file name
	이미 만들어진 윈도우에서 제공해주는 매우편한 모달방식의 윈도우
	해당창은 그냥 Path 문자열을 저장할뿐임*/
	OPENFILENAME ofn = {};
	wstring strTileFolderPath = GETINSTANCE(CPathManager)->GetMapPath();


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));														//
	ofn.lStructSize = sizeof(ofn);														//
	ofn.hwndOwner = NULL;																//
	ofn.lpstrFile = szFilePath;															//
	ofn.lpstrFile[0] = '\0';															//
	ofn.nMaxFile = 256;																	//
	ofn.lpstrFilter = L"MAP\0*.map";						//실습용 애니메이션
	ofn.nFilterIndex = 1;																//기본필터지정
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//매번 필요없는경로를열면 비효율적이기때문에 그곳을보여줌
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;									//

	//다이어로그열기
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
	ofn.lpstrFilter = L"MAP\0*.map";													//실습용 애니메이션
	ofn.nFilterIndex = 1;																//기본필터지정
	ofn.lpstrFileTitle = NULL;															//
	ofn.nMaxFileTitle = 0;																//
	ofn.lpstrInitialDir = strTileFolderPath.c_str();									//매번 필요없는경로를열면 비효율적이기때문에 그곳을보여줌
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
	//직접구현했으면 틱돌게햐아함
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
	//map 아틀라스 저장

	//카메라시작점

	//플레이어 시작점





	//오브젝트저장(몬스터, 충돌체, 라인충돌체)
	//저장방식
	//LAYEY 와정보를담음

}

#pragma region ENTER_EXIT

void CEditorLevel::Enter()
{
	//메뉴바생성
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_GAMEENGINE));
	}

	HWND hWnd = GETINSTANCE(CEngine)->GetMainWnd();
	SetMenu(hWnd, m_hMenu);
	
	POINT ptWndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CEngine)->WindowReSize(ptWndScreenSize.x, ptWndScreenSize.y);

	//초기 오브젝트 설정
	init();
}

void CEditorLevel::Exit()
{
	//메뉴바뽑기
	HWND hWnd = GETINSTANCE(CEngine)->GetMainWnd();
	SetMenu(hWnd, nullptr);

	POINT ptWndScreenSize = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CEngine)->WindowReSize(ptWndScreenSize.x, ptWndScreenSize.y);
	this->DeleteAllObject();
}

#pragma endregion