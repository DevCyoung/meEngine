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
	static CLineCollider* lineCol = nullptr;
	static CLineCollider* MouseX = nullptr;
	static CLineCollider* MouseY = nullptr;
	static float size = 40.f;


	static LINECOLMOUSE_MODE mode = LINECOLMOUSE_MODE::NONE;

	if (nullptr == MouseX)
	{
		Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();

		Vector2 p1 = Vector2(-size   / 2.f , 0.f);
		Vector2 p2 = Vector2( size   / 2.f , 0.f);;
		Vector2 p3 = Vector2( 0, -size / 2.f);;
		Vector2 p4 = Vector2( 0, +size / 2.f);;;

		MouseX = GETINSTANCE(CLineColManager)->CreateLine(p1, p2, LAYER::MOUSE);
		MouseY = GETINSTANCE(CLineColManager)->CreateLine(p3, p4, LAYER::MOUSE);

		MouseX->SetEnterEvent((DELEGATECOL)&CEditorLevel::MouseEnterEvent, this);
		MouseY->SetEnterEvent((DELEGATECOL)&CEditorLevel::MouseEnterEvent, this);
		MouseX->SetExitEvent((DELEGATECOL)&CEditorLevel::MouseExitEvent, this);
		MouseY->SetExitEvent((DELEGATECOL)&CEditorLevel::MouseExitEvent, this);		

		GETINSTANCE(CLineColManager)->LayerRegister(LAYER::MOUSE, LAYER::WALL);
		GETINSTANCE(CLineColManager)->LayerRegister(LAYER::WALL, LAYER::PLAYER);
	}

	if (IS_INPUT_TAB(KEY::LBTN))
	{
		switch (mode)
		{
		case LINECOLMOUSE_MODE::NONE:
		{
			mode = LINECOLMOUSE_MODE::ONEDOWN;
			Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
			pos = GETINSTANCE(CCamera)->GetRealPos(pos);

			if (nullptr != m_preVMouseCol)
			{
				float dis1 = m_preVMouseCol->GetP1Length(pos);
				float dis2 = m_preVMouseCol->GetP2Length(pos);

				//가장가까운점찾기
				if (dis1 > dis2)
				{
					pos = m_preVMouseCol->GetP2();
				}
				else
				{
					pos = m_preVMouseCol->GetP1();
				}
			}



			lineCol = GETINSTANCE(CLineColManager)->CreateLine(pos, pos, LAYER::WALL);
		}
		break;
		case LINECOLMOUSE_MODE::ONEDOWN:
		{
			mode = LINECOLMOUSE_MODE::TWODOWN;
			Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
			pos = GETINSTANCE(CCamera)->GetRealPos(pos);

			if (nullptr != m_preVMouseCol)
			{
				float dis1 = m_preVMouseCol->GetP1Length(pos);
				float dis2 = m_preVMouseCol->GetP2Length(pos);

				//가장가까운점찾기
				if (dis1 > dis2)
				{
					pos = m_preVMouseCol->GetP2();
				}
				else
				{
					pos = m_preVMouseCol->GetP1();
				}
			}
			lineCol->SetP2(pos);
		}
			break;
		case LINECOLMOUSE_MODE::TWODOWN:
		{
			mode = LINECOLMOUSE_MODE::NONE;
		}
			break;			
		}
	}


	//shift 정렬
	if (LINECOLMOUSE_MODE::ONEDOWN == mode && nullptr != lineCol)
	{
		Vector2 mousePos = GETINSTANCE(CKeyManager)->GetMousePos();
		Vector2 pos = GETINSTANCE(CCamera)->GetRealPos(mousePos);

		if (IS_INPUT_PRESSED(KEY::LSHIFT))
		{
			Vector2 p1 = lineCol->GetP1();
			//x로그리기
			if (abs(p1.y - pos.y) <= 100.f)
			{
				pos.y = lineCol->GetP1().y;
			}
			else
			{
				pos.x = lineCol->GetP1().x;
			}
		}


		lineCol->SetP2(pos);
	}





	if (nullptr != MouseX)
	{		

		Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
		pos = GETINSTANCE(CCamera)->GetRealPos(pos);

		//setOffset

		MouseX->TranslateSetPos(pos + Vector2(-size / 2, 0));
		MouseY->TranslateSetPos(pos + Vector2(0, -size / 2));
	}

	if (IS_INPUT_TAB(KEY::Q))
	{
		if (m_preVMouseCol == nullptr)
			return;
		GETINSTANCE(CLineColManager)->RemoveLine(m_preVMouseCol);
	}

	if (IS_INPUT_TAB(KEY::RBTN))
	{
		CZero* zero = new CZero();
		Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
		pos = GETINSTANCE(CCamera)->GetRealPos(pos);
		zero->SetPos(pos);
		this->AddObject(zero, LAYER::PLAYER);
	}
	
}

void CEditorLevel::MouseStayEvent(CLineCollider* _other)
{
	//_other->SetRenderPoint(true);
}

void CEditorLevel::MouseEnterEvent(CLineCollider* _other)
{		
	m_preVMouseCol = _other;
	_other->SetRenderPoint(true);
}

void CEditorLevel::MouseExitEvent(CLineCollider* _other)
{
	m_preVMouseCol = nullptr;
	_other->SetRenderPoint(false);
}
