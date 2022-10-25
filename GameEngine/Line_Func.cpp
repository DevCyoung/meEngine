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
void CEditorLevel::LineMouseEvent(CLineCollider* _other, LINECOL_MODE _mode)
{
	switch (_mode)
	{
	case LINECOL_MODE::ADD:
	{

	}
		break;
	case LINECOL_MODE::REMOVE:
	{
		GETINSTANCE(CLineColManager)->RemoveLine(_other);
	}
		break;
	case LINECOL_MODE::NONE:
		break;
	}
	
}

void CEditorLevel::CreateLineMode()
{
	if (IS_INPUT_TAB(KEY::LBTN))
	{
		switch (m_LineMosueMode)
		{
		case LINECOLMOUSE_MODE::NONE:
		{
			m_LineMosueMode = LINECOLMOUSE_MODE::ONEDOWN;
			Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
			pos = GETINSTANCE(CCamera)->GetRealPos(pos);

			if (nullptr != m_lineColPreMouse)
			{
				float dis1 = m_lineColPreMouse->GetP1Length(pos);
				float dis2 = m_lineColPreMouse->GetP2Length(pos);

				//가장가까운점찾기
				if (dis1 > dis2)
				{
					pos = m_lineColPreMouse->GetP2();
				}
				else
				{
					pos = m_lineColPreMouse->GetP1();
				}
			}
			lineCol = GETINSTANCE(CLineColManager)->CreateLine(pos, pos, LAYER::WALL);
		}
		break;
		case LINECOLMOUSE_MODE::ONEDOWN:
		{
			if (nullptr == lineCol)
			{
				m_LineMosueMode = LINECOLMOUSE_MODE::NONE;
				return;
			}

			m_LineMosueMode = LINECOLMOUSE_MODE::NONE;
		}
		break;

		}
	}

	//draw
	if (lineCol == nullptr)
		return;
	//shift 정렬

	Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
	pos = GETINSTANCE(CCamera)->GetRealPos(pos);


	if (m_LineMosueMode == LINECOLMOUSE_MODE::ONEDOWN)
	{

		if (IS_INPUT_PRESSED(KEY::LSHIFT))
		{
			Vector2 p1 = lineCol->GetP1();
			if (abs(p1.y - pos.y) <= 10.f)
			{
				pos.y = lineCol->GetP1().y;
			}
			else
			{
				pos.x = lineCol->GetP1().x;
			}
		}
		else if (nullptr != m_lineColPreMouse)
		{
			float dis1 = m_lineColPreMouse->GetP1Length(pos);
			float dis2 = m_lineColPreMouse->GetP2Length(pos);

			//가장가까운점찾기
			if (dis1 > dis2)
			{
				pos = m_lineColPreMouse->GetP2();
			}
			else
			{
				pos = m_lineColPreMouse->GetP1();
			}
		}


		lineCol->SetP2(pos);


	}
	if (nullptr != MouseX)
	{

		Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
		pos = GETINSTANCE(CCamera)->GetRealPos(pos);
		MouseX->TranslateSetPos(pos + Vector2(-size / 2, 0));
		MouseY->TranslateSetPos(pos + Vector2(0, -size / 2));
	}

	if (IS_INPUT_TAB(KEY::Q))
	{
		if (m_lineColPreMouse == nullptr)
			return;
		GETINSTANCE(CLineColManager)->RemoveLine(m_lineColPreMouse);
		m_lineColPreMouse = nullptr;
	}

	if (IS_INPUT_TAB(KEY::RBTN))
	{
		CZero* zero = new CZero();
		Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
		pos = GETINSTANCE(CCamera)->GetRealPos(pos);
		zero->SetPos(pos);
		this->AddObject(zero, LAYER::PLAYER);
	}


	if (IS_INPUT_TAB(KEY::_8))
	{
		//StartMapEditMode();
		SaveLineCollider();
	}
	if (IS_INPUT_TAB(KEY::_9))
	{
		//StartMapEditMode();
		LoadLineCollider();
	}

}


void CEditorLevel::MouseStayEvent(CLineCollider* _other)
{
	//_other->SetRenderPoint(true);
}

void CEditorLevel::MouseEnterEvent(CLineCollider* _other)
{		
	m_lineColPreMouse = _other;
	_other->SetRenderPoint(true);
}

void CEditorLevel::MouseExitEvent(CLineCollider* _other)
{
	m_lineColPreMouse = nullptr;
	_other->SetRenderPoint(false);
}


void CEditorLevel::CreateLineUI()
{
	//카메라시점
	Vector2 vResolution = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CCamera)->SetLook(vResolution / 2.f);


	// Button 이 사용할 텍스쳐
	CTexture* pButtonTex = GETINSTANCE(CResourceManager)->LoadTexture(L"Button", L"texture\\buttojuhylee.bmp");
	CTexture* pButtonPressedTex = GETINSTANCE(CResourceManager)->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
	CTexture* pPanelTex = GETINSTANCE(CResourceManager)->LoadTexture(L"Panel", L"texture\\OakUI.bmp");



	//UI배치
	CPanelUI* pPanelUI = new CPanelUI();
	{
		pPanelUI->SetIdleTex(pPanelTex);
		pPanelUI->SetPos(Vector2(vResolution.x - pPanelTex->Width() + 20.f, 10.f));

		CButton* pSaveButton = new CButton();
		{
			pSaveButton->SetScale(Vector2(100.f, 50.f));
			pSaveButton->SetPos(Vector2(10.f, 20.f));
			pSaveButton->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTIle);
			pSaveButton->SetIdleTex(pButtonTex);
			pSaveButton->SetPressedTex(pButtonPressedTex);
		}
		pPanelUI->AddChildUI(pSaveButton);


		CButton* pLoadButton = pSaveButton->Clone();
		{
			pLoadButton->SetPos(Vector2(150.f, 20.f));
			pLoadButton->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTIle);
		}
		pPanelUI->AddChildUI(pLoadButton);
	}
	AddObject(pPanelUI, LAYER::UI);
}

void CEditorLevel::AddMouseLineollider()
{
	GETINSTANCE(CLineColManager)->DeletCollider();

	//클리어해서 맵이랑 마우스 다시 설정해야함.
	Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();

	Vector2 p1 = Vector2(-size / 2.f, 0.f);
	Vector2 p2 = Vector2(size / 2.f, 0.f);;
	Vector2 p3 = Vector2(0, -size / 2.f);;
	Vector2 p4 = Vector2(0, +size / 2.f);;;

	MouseX = GETINSTANCE(CLineColManager)->CreateLine(p1, p2, LAYER::MOUSE);
	MouseY = GETINSTANCE(CLineColManager)->CreateLine(p3, p4, LAYER::MOUSE);

	MouseX->SetEnterEvent((DELEGATECOL)&CEditorLevel::MouseEnterEvent, this);
	MouseY->SetEnterEvent((DELEGATECOL)&CEditorLevel::MouseEnterEvent, this);
	MouseX->SetExitEvent((DELEGATECOL)&CEditorLevel::MouseExitEvent, this);
	MouseY->SetExitEvent((DELEGATECOL)&CEditorLevel::MouseExitEvent, this);

	GETINSTANCE(CLineColManager)->LayerRegister(LAYER::MOUSE, LAYER::WALL);
	GETINSTANCE(CLineColManager)->LayerRegister(LAYER::WALL, LAYER::PLAYER);
}
