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
#include "CLineColManager.h"

CTexture* mapText;

CEditorLevel::CEditorLevel()
	: m_hMenu(nullptr)
	, m_eMode(EDITOR_MODE::NONE)
	, m_lineColPreMouse(nullptr)
	, m_objCurmap(nullptr)
	, lineCol(nullptr)
	, MouseX(nullptr)
    , MouseY(nullptr)
	, m_LineMosueMode(MOUSE_MODE::NONE)
	, m_BoxMosueMode(MOUSE_MODE::NONE)
	, size(40.f)
	, m_backGround(nullptr)
	, m_wallDir(WALLDIR::NONE)
	, m_bottom{}
	, m_leftTop{}
	, m_curObj(nullptr)
{
	//mapText = GETINSTANCE(CResourceManager)->LoadTexture(L"CYBER", L"texture\\cyberspace.bmp");
	//CMonster* monster = new CMonster();
	//this->AddObject(monster, LAYER::MONSTER);
	m_wallDir = WALLDIR::LEFT;
}

CEditorLevel::~CEditorLevel()
{	
	//DeleteMenu 는 파일 도움말 등 파일하나를 지우는
	//DestroyMenu 메뉴단위가 없어져야할때
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);

}


void CEditorLevel::tick()
{
	//직접구현했으면 틱돌게햐아함
	CLevel::tick();

	GETINSTANCE(CCamera)->CameraKeyMove(1200.f);

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
		this->DeleteAllObject();
		GETINSTANCE(CLineColManager)->DeletCollider();
		GETINSTANCE(CLineColManager)->ClearFixedTick();
		AddMouseLineollider();
		m_eMode = EDITOR_MODE::LINECOLLIDER;
	}
	if (IS_INPUT_TAB(KEY::_5))
	{
		//여기서 초기화를한다.

		m_eMode = EDITOR_MODE::BOXCOLLIDER;
	}
	Update();
}

void CEditorLevel::render(HDC _dc)
{
	//assert(mapText);

	CLevel::render(_dc);


	//충돌체를 그린다.


	//Vector2 vPos = GetOwner()->GetPos();

	//Rectangle(_dc, (int)(vPos.x - m_vScale.x / 2)
	//	, (int)(vPos.y - m_vScale.y / 2)
	//	, (int)(vPos.x + m_vScale.x / 2)
	//	, (int)(vPos.y + m_vScale.y / 2));

	if (m_eMode == EDITOR_MODE::LINECOLLIDER)
	{
		HPEN hPen = nullptr;
		Vector2 mousePos = GETINSTANCE(CKeyManager)->GetMousePos();
		//mousePos = GETINSTANCE(CCamera)->GetRealPos(mousePos);

		Vector2 p1;
		Vector2 p2;
		switch (m_wallDir)
		{
		case WALLDIR::LEFT:
		{
			hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::BLACK);
			p1.x = mousePos.x - 40.f;
			p1.y = mousePos.y - 40.f;
			p2.x = mousePos.x - 40.f;
			p2.y = mousePos.y + 40.f;
		}
		break;
		case WALLDIR::UP:
		{
			hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::BLUE);
			p1.x = mousePos.x - 40.f;
			p1.y = mousePos.y - 40.f;
			p2.x = mousePos.x + 40.f;
			p2.y = mousePos.y - 40.f;
		}
		break;
		case WALLDIR::RIGHT:
		{
			hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::ORANGE);
			p1.x = mousePos.x + 40.f;
			p1.y = mousePos.y - 40.f;
			p2.x = mousePos.x + 40.f;
			p2.y = mousePos.y + 40.f;
		}
		break;
		case WALLDIR::DOWN:
		{
			hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);
			p1.x = mousePos.x - 40.f;
			p1.y = mousePos.y + 40.f;
			p2.x = mousePos.x + 40.f;
			p2.y = mousePos.y + 40.f;
		}
		break;
		}
	
		HPEN	hOriginPen = (HPEN)SelectObject(_dc, hPen);
		
		
		MoveToEx(_dc, p1.x, p1.y, nullptr);
		LineTo(_dc, p2.x, p2.y);

		//원래대로 되돌려놓기
		SelectObject(_dc, hOriginPen);
	}

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
	case EDITOR_MODE::BOXCOLLIDER:
		CreateBoxMode();
		break;
	}
}


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

void CEditorLevel::UpdateLineCollider()
{
	
}

void CEditorLevel::UpdateAnimation()
{
}

void CEditorLevel::UpdateObject()
{
}

