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

//Manager
#include "CLevelManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"
#include "CLineColManager.h"


//linecol;
#include "CLineCollider.h"

#include "CPanelUI.h"
#include "CZero.h"
//void CEditorLevel::LineMouseEvent(CLineCollider* _other, LINECOL_MODE _mode)
//{
//	switch (_mode)
//	{
//	case LINECOL_MODE::ADD:
//	{
//
//	}
//		break;
//	case LINECOL_MODE::REMOVE:
//	{
//		GETINSTANCE(CLineColManager)->RemoveLine(_other);
//	}
//		break;
//	case LINECOL_MODE::NONE:
//		break;
//	}
//	
//}
//
//void CEditorLevel::CreateLineMode()
//{
	//Vector2 pos;
	//pos = GETINSTANCE(CKeyManager)->GetMousePos();
	//pos = GETINSTANCE(CCamera)->GetRealPos(pos);
	//if (IS_INPUT_TAB(KEY::LBTN))
	//{
	//	switch (m_LineMosueMode)
	//	{
	//	case MOUSE_MODE::NONE:
	//	{
	//		m_LineMosueMode = MOUSE_MODE::ONEDOWN;
	//		

	//		if (nullptr != m_lineColPreMouse)
	//		{
	//			float dis1 = m_lineColPreMouse->GetP1Length(pos);
	//			float dis2 = m_lineColPreMouse->GetP2Length(pos);

	//			//가장가까운점찾기
	//			if (dis1 > dis2)
	//			{
	//				pos = m_lineColPreMouse->GetP2();
	//			}
	//			else
	//			{
	//				pos = m_lineColPreMouse->GetP1();
	//			}
	//		}
	//		switch (m_wallDir)
	//		{
	//		case WALLDIR::LEFT:
	//			lineCol = GETINSTANCE(CLineColManager)->CreateLine(pos, pos, LINELAYER::LEFTWALL);
	//			break;
	//		case WALLDIR::UP:
	//			lineCol = GETINSTANCE(CLineColManager)->CreateLine(pos, pos, LINELAYER::UPWALL);
	//			break;
	//		case WALLDIR::RIGHT:
	//			lineCol = GETINSTANCE(CLineColManager)->CreateLine(pos, pos, LINELAYER::RIGHTWALL);
	//			break;
	//		case WALLDIR::DOWN:
	//			lineCol = GETINSTANCE(CLineColManager)->CreateLine(pos, pos, LINELAYER::DOWNWALL);
	//			break;
	//		}
	//		
	//	}
	//	break;
	//	case MOUSE_MODE::ONEDOWN:
	//	{
	//		if (IS_INPUT_PRESSED(KEY::LSHIFT))
	//		{
	//			Vector2 p1 = lineCol->GetP1();
	//			if (abs(p1.y - pos.y) <= 50.f)
	//			{
	//				pos.y = lineCol->GetP1().y;
	//			}
	//			else
	//			{
	//				pos.x = lineCol->GetP1().x;
	//			}
	//		}
	//		else if (nullptr != m_lineColPreMouse)
	//		{
	//			float dis1 = m_lineColPreMouse->GetP1Length(pos);
	//			float dis2 = m_lineColPreMouse->GetP2Length(pos);

	//			//가장가까운점찾기
	//			if (dis1 > dis2)
	//			{
	//				pos = m_lineColPreMouse->GetP2();
	//			}
	//			else
	//			{
	//				pos = m_lineColPreMouse->GetP1();
	//			}
	//		}
	//		m_LineMosueMode = MOUSE_MODE::NONE;
	//		lineCol->m_dir = m_wallDir;
	//		lineCol = nullptr;
	//		return;
	//	}
	//	break;
	//	}
	//}

	//pos = GETINSTANCE(CKeyManager)->GetMousePos();
	//pos = GETINSTANCE(CCamera)->GetRealPos(pos);

	//if (m_LineMosueMode == MOUSE_MODE::ONEDOWN && lineCol)
	//{
	//	if (IS_INPUT_PRESSED(KEY::LSHIFT))
	//	{
	//		Vector2 p1 = lineCol->GetP1();
	//		if (abs(p1.y - pos.y) <= 50.f)
	//		{
	//			pos.y = lineCol->GetP1().y;
	//		}
	//		else
	//		{
	//			pos.x = lineCol->GetP1().x;
	//		}
	//	}
	//	else if (nullptr != m_lineColPreMouse && lineCol != m_lineColPreMouse)
	//	{
	//		float dis1 = m_lineColPreMouse->GetP1Length(pos);
	//		float dis2 = m_lineColPreMouse->GetP2Length(pos);

	//		//가장가까운점찾기
	//		if (dis1 > dis2)
	//		{
	//			pos = m_lineColPreMouse->GetP2();
	//		}
	//		else
	//		{
	//			pos = m_lineColPreMouse->GetP1();
	//		}
	//	}
	//	lineCol->SetP2(pos);
	//}
	//
	//pos = GETINSTANCE(CKeyManager)->GetMousePos();
	//pos = GETINSTANCE(CCamera)->GetRealPos(pos);
	//if (m_MouseX != nullptr && m_MouseY != nullptr)
	//{
	//	m_MouseX->TranslateSetPos(pos + Vector2(-size / 2, 0));
	//	m_MouseY->TranslateSetPos(pos + Vector2(0, -size / 2));
	//}
	//if (IS_INPUT_TAB(KEY::_7))
	//{
	//	StartMapEditMode();
	//}
	//if (IS_INPUT_TAB(KEY::_8))
	//{
	//	SaveLineCollider();
	//}
	//if (IS_INPUT_TAB(KEY::_9))
	//{
	//	LoadLineCollider();
	//}

	//if (IS_INPUT_TAB(KEY::RBTN))
	//{
	//	CZero* zero = new CZero();
	//	Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
	//	pos = GETINSTANCE(CCamera)->GetRealPos(pos);
	//	zero->SetPos(pos);
	//	this->AddObject(zero, LAYER::PLAYER);
	//}
	//if (IS_INPUT_TAB(KEY::Q) && m_lineColPreMouse != nullptr)
	//{
	//	GETINSTANCE(CLineColManager)->RemoveLine(m_lineColPreMouse);
	//	m_lineColPreMouse = nullptr;
	//}

	//if (IS_INPUT_TAB(KEY::E))
	//{
	//	UINT wallNum = (UINT)m_wallDir;
	//	++wallNum;
	//	wallNum %= (UINT)WALLDIR::NONE;
	//	m_wallDir = (WALLDIR)wallNum;

	//}
//}

//
//void CEditorLevel::MouseStayEvent(CLineCollider* _other)
//{
//	//_other->SetRenderPoint(true);
//	//if (lineCol == _other)
//	//	return;
//}
//
//void CEditorLevel::MouseEnterEvent(CLineCollider* _other)
//{
//	/*if (lineCol == _other)
//		return;
//	m_lineColPreMouse = _other;
//	_other->SetIsRenderGizmo(true);*/
//}
//
//void CEditorLevel::MouseExitEvent(CLineCollider* _other)
//{
//	/*if (lineCol == _other)
//		return;
//	m_lineColPreMouse = nullptr;
//	_other->SetIsRenderGizmo(false);*/
//}

//
//void CEditorLevel::CreateLineUI()
//{
//	//카메라시점
//	Vector2 vResolution = GETINSTANCE(CEngine)->GetWndScreenSize();
//	GETINSTANCE(CCamera)->SetLook(vResolution / 2.f);
//
//
//	// Button 이 사용할 텍스쳐
//	CTexture* pButtonTex = GETINSTANCE(CResourceManager)->LoadTexture(L"Button", L"texture\\buttojuhylee.bmp");
//	CTexture* pButtonPressedTex = GETINSTANCE(CResourceManager)->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
//	CTexture* pPanelTex = GETINSTANCE(CResourceManager)->LoadTexture(L"Panel", L"texture\\OakUI.bmp");
//
//
//
//	//UI배치
//	CPanelUI* pPanelUI = new CPanelUI();
//	{
//		pPanelUI->SetIdleTex(pPanelTex);
//		pPanelUI->SetPos(Vector2(vResolution.x - pPanelTex->Width() + 20.f, 10.f));
//
//		CButton* pSaveButton = new CButton();
//		{
//			pSaveButton->SetScale(Vector2(100.f, 50.f));
//			pSaveButton->SetPos(Vector2(10.f, 20.f));
//			pSaveButton->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTIle);
//			pSaveButton->SetIdleTex(pButtonTex);
//			pSaveButton->SetPressedTex(pButtonPressedTex);
//		}
//		pPanelUI->AddChildUI(pSaveButton);
//
//
//		CButton* pLoadButton = pSaveButton->Clone();
//		{
//			pLoadButton->SetPos(Vector2(150.f, 20.f));
//			pLoadButton->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTIle);
//		}
//		pPanelUI->AddChildUI(pLoadButton);
//	}
//	AddObject(pPanelUI, LAYER::UI);
//}
//
//void CEditorLevel::AddMouseLineCollider()
//{
//	/*GETINSTANCE(CLineColManager)->DeletCollider();
//	this->DeleteAllObject();*/
//
//
//	////클리어해서 맵이랑 마우스 다시 설정해야함.
//	//Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
//
//	//Vector2 p1 = Vector2(-size / 2.f, 0.f);
//	//Vector2 p2 = Vector2(size / 2.f, 0.f);;
//	//Vector2 p3 = Vector2(0, -size / 2.f);;
//	//Vector2 p4 = Vector2(0, +size / 2.f);;;
//
//	//m_MouseX = GETINSTANCE(CLineColManager)->CreateLine(p1, p2, LINELAYER::MOUSE);
//	//m_MouseY = GETINSTANCE(CLineColManager)->CreateLine(p3, p4, LINELAYER::MOUSE);
//
//	//m_MouseX->SetEnterEvent((DELEGATECOL)&CEditorLevel::MouseEnterEvent, this);
//	//m_MouseY->SetEnterEvent((DELEGATECOL)&CEditorLevel::MouseEnterEvent, this);
//	//m_MouseX->SetExitEvent((DELEGATECOL)&CEditorLevel::MouseExitEvent, this);
//	//m_MouseY->SetExitEvent((DELEGATECOL)&CEditorLevel::MouseExitEvent, this);
//
//	//GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::MOUSE, LINELAYER::LEFTWALL);
//	//GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::MOUSE, LINELAYER::RIGHTWALL);
//	//GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::MOUSE, LINELAYER::UPWALL);
//	//GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::MOUSE, LINELAYER::DOWNWALL);
//
//	//
//	//GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::LEFTWALL, LINELAYER::PLAYER);
//
//	//m_LineMosueMode = MOUSE_MODE::NONE;
//	//m_eMode = EDITOR_MODE::LINECOLLIDER;
//}
//
//void CEditorLevel::DeleteMouse()
//{
//	//if (nullptr != m_MouseX )
//	//{
//	//	GETINSTANCE(CLineColManager)->RemoveLine(m_MouseX);
//	//	m_MouseX = nullptr;
//	//}
//
//	//if (nullptr != m_MouseY)
//	//{
//	//	GETINSTANCE(CLineColManager)->RemoveLine(m_MouseY);
//	//	m_MouseY = nullptr;
//	//}
//}