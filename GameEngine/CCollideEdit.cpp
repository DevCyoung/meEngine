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
#include "CNextArea.h"
#include "CDoor1.h"
#include "CDoor2.h"

#include "CLineCollider.h"
#include "CLevel.h"
#include "CEventBox.h"

CCollideEdit::CCollideEdit()
	: m_detectBox(nullptr)
	, m_curGizmoPoint{}
	, m_mouseMode{}
	, m_leftTop{}
	, m_rightbottom{}
	, m_curMakeWall(nullptr)
	, m_curColLine(nullptr)
	, m_editMode(COLIDE_EIDT_MODE::LINE)
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
	, m_editMode(COLIDE_EIDT_MODE::WALL)
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

	if (IS_INPUT_TAB(KEY::TAB))
	{
		UINT a = (UINT)m_editMode;
		++a;
		a %= (UINT)COLIDE_EIDT_MODE::END;
		m_editMode = (COLIDE_EIDT_MODE)a;
	}

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
	if (m_mouseMode == MOUSE_MODE::ONEDOWN && (m_editMode == COLIDE_EIDT_MODE::WALL || m_editMode == COLIDE_EIDT_MODE::BOSSDOOR1BOX || m_editMode == COLIDE_EIDT_MODE::BOSSDOOR2BOX || m_editMode == COLIDE_EIDT_MODE::NEXTAREAEBOX))
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

	//문자열

	CEditorLevel* lv = (CEditorLevel*)GETINSTANCE(CLevelManager)->GetEditorLevel();
	if (lv->m_eMode == EDITOR_MODE::COLLIDE)
	{
		switch (m_editMode)
		{
		case COLIDE_EIDT_MODE::WALL:
			TextOut(_dc, 10, 10, L"WALL", 4);
			break;
		case COLIDE_EIDT_MODE::LINE:
			TextOut(_dc, 10, 10, L"LINE", 4);
			break;
		case COLIDE_EIDT_MODE::NEXTAREAEBOX:
			TextOut(_dc, 10, 10, L"NEXTAREAE", 9);
			break;
		case COLIDE_EIDT_MODE::BOSSDOOR1BOX:
			TextOut(_dc, 10, 10, L"BOSSDOOR1", 9);
			break;
		case COLIDE_EIDT_MODE::BOSSDOOR2BOX:
			TextOut(_dc, 10, 10, L"BOSSDOOR2", 9);
			break;
		}
	}


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
		m_editMode = COLIDE_EIDT_MODE::WALL;
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
			lv->AddObject(m_curColLine, LAYER::LINE);
			m_curColLine->GetLineCollider()->SetP1(m_leftTop);
			m_curColLine->GetLineCollider()->SetP2(m_rightbottom);
			m_curColLine = nullptr;
		}
		break;
		case COLIDE_EIDT_MODE::WALL:
		{
			m_curMakeWall = new CWall();
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			lv->AddObject(m_curMakeWall, LAYER::WALL);
			m_curMakeWall->ResizeCollider(m_leftTop, m_rightbottom);
			m_curMakeWall = nullptr;
		}	
		break;
		case COLIDE_EIDT_MODE::NEXTAREAEBOX:
		{			
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CNextArea* a = new CNextArea();
			a->ResizeCollider(m_leftTop, m_rightbottom);
			lv->AddObject(a, LAYER::EVENT);			
		}
		break;
		case COLIDE_EIDT_MODE::BOSSDOOR1BOX:
		{
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CDoor1* a = new CDoor1();
			a->ResizeCollider(m_leftTop, m_rightbottom);
			lv->AddObject(a, LAYER::EVENT);
		}
		break;
		case COLIDE_EIDT_MODE::BOSSDOOR2BOX:
		{
			CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();
			CDoor2* a = new CDoor2();
			a->ResizeCollider(m_leftTop, m_rightbottom);
			lv->AddObject(a, LAYER::EVENT);
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
		CRockmanObj* obj = dynamic_cast<CRockmanObj*>(m_detectBox->GetOwner());
		if (nullptr != obj)
		{
			if (nullptr != obj->GetLineCollider())
			{
				GETINSTANCE(CLineColManager)->RemoveLine(obj->GetLineCollider()->GetLineCollider());
			}			
		}
		m_detectBox->GetOwner()->Destroy();
	}
	else if (IS_INPUT_TAB(KEY::Q) && m_detectColLine != nullptr)
	{
		CGameObject* obj = m_detectColLine->m_lineOwner;
		assert(obj);
		obj->Destroy();
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

void CCollideEdit::Save(FILE* pFile)
{
	CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();

	//모든벽들
	const vector<CGameObject*>& lineOjs  = lv->GetLayer(LAYER::LINE);
	const vector<CGameObject*>& WallOjs  = lv->GetLayer(LAYER::WALL);
	const vector<CGameObject*>& eventOjs = lv->GetLayer(LAYER::EVENT);

	UINT size = lineOjs.size();
	fwrite(&size, sizeof(UINT), 1, pFile);

	for (size_t i = 0; i < size; i++)
	{
		CLine* line = dynamic_cast<CLine*>(lineOjs[i]);
		assert(line);
		line->Save(pFile);
	}

	size = WallOjs.size();
	fwrite(&size, sizeof(UINT), 1, pFile);

	for (size_t i = 0; i < size; i++)
	{
		CWall* wall = dynamic_cast<CWall*>(WallOjs[i]);
		assert(wall);
		wall->Save(pFile);
	}

	size = eventOjs.size();
	fwrite(&size, sizeof(UINT), 1, pFile);

	for (size_t i = 0; i < size; i++)
	{
		CEventBox* evt = dynamic_cast<CEventBox*>(eventOjs[i]);
		assert(evt);
		COLIDE_EIDT_MODE cem = evt->m_mode;
		fwrite(&cem, sizeof(COLIDE_EIDT_MODE), 1, pFile);
		evt->Save(pFile);
	}
}

void CCollideEdit::Load(FILE* pFile)
{
	UINT size;

	fread(&size, sizeof(UINT), 1, pFile);

	for (size_t i = 0; i < size; i++)
	{
		CLine* line = new CLine();
		assert(line);
		line->Load(pFile);
		CGameObject::Instantiate(line, line->GetPos(), LAYER::LINE);
	}

	fread(&size, sizeof(UINT), 1, pFile);
	for (size_t i = 0; i < size; i++)
	{
		CWall* wall = new CWall();
		assert(wall);
		wall->Load(pFile);
		CGameObject::Instantiate(wall, wall->GetPos(), LAYER::WALL);
	}

	fread(&size, sizeof(UINT), 1, pFile);
	for (size_t i = 0; i < size; i++)
	{
		COLIDE_EIDT_MODE cem;
		fread(&cem, sizeof(COLIDE_EIDT_MODE), 1, pFile);
		CEventBox* envBox = nullptr;
		switch (cem)
		{		
		case COLIDE_EIDT_MODE::NEXTAREAEBOX:
			envBox = new CNextArea();
			break;
		case COLIDE_EIDT_MODE::BOSSDOOR1BOX:
			envBox = new CDoor1();
			break;
		case COLIDE_EIDT_MODE::BOSSDOOR2BOX:
			envBox = new CDoor2();
			break;		
		default:
			assert(envBox);
			break;
		}		
		envBox->Load(pFile);
		CGameObject::Instantiate(envBox, envBox->GetPos(), LAYER::EVENT);
	}
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