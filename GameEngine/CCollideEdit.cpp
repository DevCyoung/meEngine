#include "pch.h"

#include "CCollideEdit.h"

#include "CCamera.h"
#include "CKeyManager.h"
#include "CCollider.h"
#include "CLevelManager.h"
#include "CLineColManager.h"
#include "CEditorLevel.h"
#include "CLevel.h"
#include "CZero.h"

#include "CWall.h"
#include "CLine.h"

#include "CLineCollider.h"


CCollideEdit::CCollideEdit()
	: m_detectBox(nullptr)
	, m_curGizmoPoint{}
	, m_mouseMode{}
	, m_leftTop{}
	, m_rightbottom{}
	, m_curMakeWall(nullptr)
	, m_curColLine(nullptr)
	, m_editMode(COLIDE_EIDT_MODE::BOX)
	, m_mouseX(nullptr)
	, m_mouseY(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(50.f, 50.f));

	m_mouseX = new CLine();
	m_mouseY = new CLine();

	Vector2 mxPos1 = GETINSTANCE(CCamera)->GetRealMousePos() - Vector2(30.f, 0.f);
	Vector2 mxPos2 = GETINSTANCE(CCamera)->GetRealMousePos() + Vector2(30.f, 0.f);

	Vector2 myPos1 = GETINSTANCE(CCamera)->GetRealMousePos() - Vector2(0.f, 30.f);
	Vector2 myPos2 = GETINSTANCE(CCamera)->GetRealMousePos() + Vector2(0.f, 30.f);

	m_mouseX->CreateLineCollider(mxPos1, mxPos2, LINELAYER::MOUSE);
	m_mouseY->CreateLineCollider(myPos1, myPos2, LINELAYER::MOUSE);

	GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::MOUSE, LINELAYER::DOWNWALL);

	m_mouseX->GetLineCollider()->SetEnterEvent((DELEGATECOL)&CCollideEdit::MouseEnterEvent, this);
	m_mouseY->GetLineCollider()->SetEnterEvent((DELEGATECOL)&CCollideEdit::MouseEnterEvent, this);
	m_mouseX->GetLineCollider()->SetExitEvent((DELEGATECOL)&CCollideEdit::MouseExitEvent, this);
	m_mouseY->GetLineCollider()->SetExitEvent((DELEGATECOL)&CCollideEdit::MouseExitEvent, this);
}

CCollideEdit::CCollideEdit(const CCollideEdit& _other)
	: m_detectBox(nullptr)
	, m_curGizmoPoint{}
	, m_mouseMode{}
	, m_leftTop{}
	, m_rightbottom{}
	, m_curMakeWall(nullptr)
	, m_curColLine(nullptr)
	, m_editMode(COLIDE_EIDT_MODE::BOX)
{
}

CCollideEdit::~CCollideEdit()
{
	if (nullptr != m_mouseX)
		delete m_mouseX;
	if (nullptr != m_mouseY)
		delete m_mouseY;
}


void CCollideEdit::tick()
{
	CGameObject::tick();
	Vector2 pos = GETINSTANCE(CCamera)->GetRealMousePos();
	SetPos(pos);

	Vector2 mxPos1 = GETINSTANCE(CCamera)->GetRealMousePos() - Vector2(30.f, 0.f);
	Vector2 myPos1 = GETINSTANCE(CCamera)->GetRealMousePos() - Vector2(0.f, 30.f);
	m_mouseX->GetLineCollider()->TranslateSetPos(mxPos1);
	m_mouseY->GetLineCollider()->TranslateSetPos(myPos1);
}

#pragma region render

void CCollideEdit::render(HDC _dc)
{
	CGameObject::render(_dc);

	if (nullptr != m_detectBox || nullptr != m_detectColLine)
	{
		Rectangle
		(
			_dc,
			m_curGizmoPoint.x - 10.f,
			m_curGizmoPoint.y - 10.f,
			m_curGizmoPoint.x + 10.f,
			m_curGizmoPoint.y + 10.f
		);
	}
	Vector2 lt = GETINSTANCE(CCamera)->GetRenderPos(m_leftTop);
	Vector2 rb = GETINSTANCE(CCamera)->GetRenderPos(m_rightbottom);
	if (m_mouseMode == MOUSE_MODE::ONEDOWN && m_editMode == COLIDE_EIDT_MODE::BOX)
	{
		
		Rectangle
		(
			_dc,
			lt.x,
			lt.y,
			rb.x ,
			rb.y
		);
	}

	if (m_mouseMode == MOUSE_MODE::ONEDOWN && m_editMode == COLIDE_EIDT_MODE::LINE)
	{
		MoveToEx(_dc, lt.x, lt.y, nullptr);
		LineTo(_dc, rb.x, rb.y);
	}

	//충돌체를 그린다.
	// 
	//Vector2 vPos = GetOwner()->GetPos();

	//Rectangle(_dc, (int)(vPos.x - m_vScale.x / 2)
	//	, (int)(vPos.y - m_vScale.y / 2)
	//	, (int)(vPos.x + m_vScale.x / 2)
	//	, (int)(vPos.y + m_vScale.y / 2));

	//if (m_eMode == EDITOR_MODE::LINECOLLIDER)
	//{
	//	HPEN hPen = nullptr;
	//	Vector2 mousePos = GETINSTANCE(CKeyManager)->GetMousePos();
	//	//mousePos = GETINSTANCE(CCamera)->GetRealPos(mousePos);

	//	Vector2 p1;
	//	Vector2 p2;
	//	switch (m_wallDir)
	//	{
	//	case WALLDIR::LEFT:
	//	{
	//		hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::BLACK);
	//		p1.x = mousePos.x - 40.f;
	//		p1.y = mousePos.y - 40.f;
	//		p2.x = mousePos.x - 40.f;
	//		p2.y = mousePos.y + 40.f;
	//	}
	//	break;
	//	case WALLDIR::UP:
	//	{
	//		hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::BLUE);
	//		p1.x = mousePos.x - 40.f;
	//		p1.y = mousePos.y - 40.f;
	//		p2.x = mousePos.x + 40.f;
	//		p2.y = mousePos.y - 40.f;
	//	}
	//	break;
	//	case WALLDIR::RIGHT:
	//	{
	//		hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::ORANGE);
	//		p1.x = mousePos.x + 40.f;
	//		p1.y = mousePos.y - 40.f;
	//		p2.x = mousePos.x + 40.f;
	//		p2.y = mousePos.y + 40.f;
	//	}
	//	break;
	//	case WALLDIR::DOWN:
	//	{
	//		hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);
	//		p1.x = mousePos.x - 40.f;
	//		p1.y = mousePos.y + 40.f;
	//		p2.x = mousePos.x + 40.f;
	//		p2.y = mousePos.y + 40.f;
	//	}
	//	break;
	//	}
	//
	//	HPEN	hOriginPen = (HPEN)SelectObject(_dc, hPen);
	//	
	//	
	//	MoveToEx(_dc, p1.x, p1.y, nullptr);
	//	LineTo(_dc, p2.x, p2.y);

	//	//원래대로 되돌려놓기
	//	SelectObject(_dc, hOriginPen);
	//}

}
#pragma endregion

void CCollideEdit::Update()
{



	if (nullptr != m_detectBox)
	{
		Vector2 vPos = m_detectBox->GetFinalPos();
		Vector2 vScale = m_detectBox->GetScale();

		Vector2 vLeftTop = vPos - vScale / 2;
		Vector2 vrightbottom = vPos + vScale / 2;

		if (GetPos().x < vPos.x)
		{
			m_curGizmoPoint.x = vLeftTop.x;
		}
		else
		{
			m_curGizmoPoint.x = vrightbottom.x;
		}

		if (GetPos().y < vPos.y)
		{
			m_curGizmoPoint.y = vLeftTop.y;
		}
		else
		{
			m_curGizmoPoint.y = vrightbottom.y;
		}

		m_curGizmoPoint = GETINSTANCE(CCamera)->GetRenderPos(m_curGizmoPoint);
	}
	else if (nullptr != m_detectColLine)
	{

		Vector2 mouse = GETINSTANCE(CCamera)->GetRealMousePos();
		Vector2 p1 = m_detectColLine->GetP1();
		Vector2 p2 = m_detectColLine->GetP2();

		if (abs(p1.x - mouse.x) < abs(p2.x - mouse.x))
		{
			m_curGizmoPoint = p1;
		}
		else
		{
			m_curGizmoPoint = p2;
		}

		m_curGizmoPoint = GETINSTANCE(CCamera)->GetRenderPos(m_curGizmoPoint);
	}



	if (IS_INPUT_TAB(KEY::O))
	{
		m_editMode = COLIDE_EIDT_MODE::BOX;
	}
	else if (IS_INPUT_TAB(KEY::P))
	{
		m_editMode = COLIDE_EIDT_MODE::LINE;
	}

	if (IS_INPUT_TAB(KEY::LBTN) && m_mouseMode == MOUSE_MODE::NONE)
	{

		m_mouseMode = MOUSE_MODE::ONEDOWN;
		m_rightbottom = Vector2(0.f, 0.f);
		m_leftTop = GETINSTANCE(CCamera)->GetRealMousePos();

		if (nullptr != m_detectBox || nullptr != m_detectColLine)
		{
			m_leftTop = GETINSTANCE(CCamera)->GetRealPos(m_curGizmoPoint);
		}
	}
	else if (IS_INPUT_TAB(KEY::LBTN) && m_mouseMode == MOUSE_MODE::ONEDOWN)
	{
		m_mouseMode = MOUSE_MODE::NONE;
		switch (m_editMode)
		{
		case COLIDE_EIDT_MODE::LINE:
		{			
			m_curColLine = new CLine();
			m_curColLine->CreateLineCollider(m_leftTop, m_leftTop, LINELAYER::DOWNWALL);
			m_curColLine->SetPos(m_leftTop);
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			lv->AddObject(m_curColLine, LAYER::WALL);
			m_curColLine->GetLineCollider()->SetP1(m_leftTop);
			m_curColLine->GetLineCollider()->SetP2(m_rightbottom);
			m_curColLine = nullptr;
		}
		break;
		case COLIDE_EIDT_MODE::BOX:
		{
			m_curMakeWall = new CWall();
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			lv->AddObject(m_curMakeWall, LAYER::WALL);
			m_curMakeWall->ResizeCollider(m_leftTop, m_rightbottom);
			m_curMakeWall = nullptr;
		}
		break;
		}
	}

	if (m_mouseMode == MOUSE_MODE::ONEDOWN)
	{

		if (nullptr != m_detectBox)
		{
			m_rightbottom = GETINSTANCE(CCamera)->GetRealPos(m_curGizmoPoint);
		}
		else if(nullptr != m_detectColLine)
		{
			m_rightbottom = GETINSTANCE(CCamera)->GetRealPos(m_curGizmoPoint);
		}		
		else
		{
			m_rightbottom = GETINSTANCE(CCamera)->GetRealMousePos();
		}
		if (m_editMode == COLIDE_EIDT_MODE::LINE && IS_INPUT_PRESSED(KEY::LSHIFT))
		{
			m_rightbottom.y = m_leftTop.y;
		}
		if (m_editMode == COLIDE_EIDT_MODE::LINE && IS_INPUT_PRESSED(KEY::LCTRL))
		{
			m_rightbottom.x = m_leftTop.x;
		}
	}




	if (IS_INPUT_TAB(KEY::RBTN))
	{
		CZero* zero = new CZero();
		Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
		pos = GETINSTANCE(CCamera)->GetRealPos(pos);
		CGameObject::Instantiate(zero, pos, LAYER::PLAYER);
	}

	if (IS_INPUT_TAB(KEY::Q) && m_detectBox != nullptr)
	{
		m_detectBox->GetOwner()->Destroy();
	}
	else if (IS_INPUT_TAB(KEY::Q) && m_detectColLine != nullptr)
	{
		GETINSTANCE(CLineColManager)->RemoveLine(m_detectColLine);
		m_detectColLine = nullptr;
	}
}

#pragma region Event
void CCollideEdit::CreateLineMode()
{

}

void CCollideEdit::MouseStayEvent(CLineCollider* _other)
{
}

void CCollideEdit::MouseEnterEvent(CLineCollider* _other)
{
	m_detectColLine = _other;
	_other->SetIsRenderGizmo(true);
}

void CCollideEdit::MouseExitEvent(CLineCollider* _other)
{
	m_detectColLine = nullptr;
	_other->SetIsRenderGizmo(false);
}

void CCollideEdit::OnTriggerEnter(CCollider* _pOhter)
{
	m_detectBox = _pOhter;
}

void CCollideEdit::OnTriggerStay(CCollider* _pOhter)
{

}

void CCollideEdit::OnTriggerExit(CCollider* _pOhter)
{
	m_detectBox = nullptr;
}

#pragma endregion