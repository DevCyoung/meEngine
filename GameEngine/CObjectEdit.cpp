#include "pch.h"
#include "CObjectEdit.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CTile.h"
#include "resource.h"

#include "CKeyManager.h"
#include "CPathManager.h"
#include "CUI.h"
#include "CButton.h"
#include "CPanelUI.h"
#include "CCollisionManager.h"
#include "CLineColManager.h"
#include "CCollider.h"
#include "CEditorLevel.h"

#include "CLevelManager.h"
#include "CLevel.h"

#include "CAnimator.h"
#include "CAnimation.h"
//obj
#include "CZero.h"
#include "CMiru.h"
#include "CRockmanObj.h"
#include "CTry.h"
#include "CGosm.h"

//helper
#include "CRenderHelper.h"

#include "CLevelManager.h"

#include "CCong.h"

CObjectEdit::CObjectEdit()
	: m_curSelectObj(nullptr)
	, m_detectObj(nullptr)
	, m_mouseState(MOUSE_MODE::NONE)
	, m_targetPos{}
	, m_sponType{}
	, m_monstreState{}
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(50.f, 50.f));
	m_sponType = MONSETER_TYPE::NONE;
}

CObjectEdit::CObjectEdit(const CObjectEdit& _other)
	:m_curSelectObj(nullptr)
	, m_detectObj(nullptr)
	, m_mouseState(MOUSE_MODE::NONE)
	, m_targetPos{}
	, m_sponType{}
	, m_monstreState{}
{

}

CObjectEdit::~CObjectEdit()
{

}


void CObjectEdit::tick()
{
	Vector2 pos = GETINSTANCE(CCamera)->GetRealMousePos();
	SetPos(pos);
}

void CObjectEdit::render(HDC _dc)
{
	if (nullptr != m_curSelectObj && m_mouseState == MOUSE_MODE::ONEDOWN)
	{
		CAnimation* anim = m_curSelectObj->GetAnimator()->FindAnimation(L"IDLE");
		tAnimFrm frm = anim->GetFrame(0);
		Vector2 mousePos = GETINSTANCE(CKeyManager)->GetMousePos();

		CRenderHelper::StretchRender(anim->GetAtlas()->GetDC(), frm.vLeftTop.x, frm.vLeftTop.y, frm.vSize.x, frm.vSize.y,
			_dc, m_targetPos.x, m_targetPos.y, frm.vOffset.x, frm.vOffset.y, false);





		HPEN pen = GETINSTANCE(CEngine)->GetPen((PEN_TYPE)m_monstreState);
		HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HPEN	hOriginPen = (HPEN)SelectObject(_dc, pen);
		HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

		CEditorLevel* lv = (CEditorLevel*)GETINSTANCE(CLevelManager)->GetEditorLevel();
		if (lv->m_eMode == EDITOR_MODE::OBJECT)
		{
			switch (m_monstreState)
			{
			case MONSTER_STATE::TYPE1:
				TextOut(_dc, 10, 10, L"Type1", 5);
				break;
			case MONSTER_STATE::TYPE2:
				TextOut(_dc, 10, 10, L"Type2", 5);
				break;
			case MONSTER_STATE::TYPE3:
				TextOut(_dc, 10, 10, L"Type3", 5);
				break;
			case MONSTER_STATE::TYPE4:
				TextOut(_dc, 10, 10, L"Type4", 5);
				break;
			}
		}


		SelectObject(_dc, hOriginPen);
		SelectObject(_dc, hOriginBrush);
		
	}
	
	


}

void CObjectEdit::RegisterObject(CRockmanObj* obj)
{

}

void CObjectEdit::CreateUI(CLevel* level)
{
	//카메라시점
	Vector2 vResolution = GETINSTANCE(CEngine)->GetWndScreenSize();
	GETINSTANCE(CCamera)->SetLook(vResolution / 2.f);


	// Button 이 사용할 텍스쳐
	CTexture*	pButtonTex			 = GETINSTANCE(CResourceManager)->LoadTexture(L"Button", L"texture\\button.bmp");
	CTexture*	pButtonPressedTex	 = GETINSTANCE(CResourceManager)->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
	CTexture*	pPanelTex			 = GETINSTANCE(CResourceManager)->LoadTexture(L"Panel", L"texture\\OakUI.bmp");


	//UI배치
	CPanelUI* pPanelUI = new CPanelUI();
	{
		pPanelUI->SetIdleTex(pPanelTex);
		pPanelUI->SetPos(Vector2(vResolution.x - pPanelTex->Width() + 20.f, 10.f));


		CButton* pSaveButton = new CButton();
		{
			pSaveButton->SetScale(Vector2(50.f, 50.f));
			pSaveButton->SetPos(Vector2(10.f, 20.f));
			//pSaveButton->SetDelegate(this, (DELEGATERockman)&CObjectEdit::SelectGameObject);			
			//pSaveButton->SetRockman(new CZero())
		}
		pPanelUI->AddChildUI(pSaveButton);
		//level->AddObject(pSaveButton, LAYER::UI);


		CButton* pLoadButton = pSaveButton->Clone();
		{

			pLoadButton->SetPos(Vector2(10.f, 70.f));
			pLoadButton->SetRockman(new CMiru());
			pLoadButton->SetDelegate(this, (DELEGATERockman)&CObjectEdit::SelectGameObject);
		}
		pPanelUI->AddChildUI(pLoadButton);


		//try
		CButton* pLoadButton2 = pSaveButton->Clone();
		{

			pLoadButton2->SetPos(Vector2(120.f, 20.f));
			pLoadButton2->SetRockman(new CGosm());
			pLoadButton2->SetDelegate(this, (DELEGATERockman)&CObjectEdit::SelectGameObject);
		}
		pPanelUI->AddChildUI(pLoadButton2);

		CButton* pLoadButton3 = pSaveButton->Clone();
		{
			pLoadButton3->SetPos(Vector2(10.f, 120.f));
			pLoadButton3->SetRockman(new CTry());
			pLoadButton3->SetDelegate(this, (DELEGATERockman)&CObjectEdit::SelectGameObject);
		}
		pPanelUI->AddChildUI(pLoadButton3);


		CButton* pLoadButton4 = pSaveButton->Clone();
		{
			pLoadButton4->SetPos(Vector2(50.f, 120.f));
			pLoadButton4->SetRockman(new CCong());
			pLoadButton4->SetDelegate(this, (DELEGATERockman)&CObjectEdit::SelectGameObject);
		}
		pPanelUI->AddChildUI(pLoadButton4);
		


		//level->AddObject(pLoadButton, LAYER::UI);
	}
	level->AddObject(pPanelUI, LAYER::UI);
	
	//GETINSTANCE(CLevelManager)->GetCurLevel()->AddObject(pPanelUI, LAYER::UI);

	//for (size_t i = 0; i < 100; i++)
	//{
	//	pPanelUI = pPanelUI->Clone();
	//	pPanelUI->SetPos(Vector2(vResolution.x - pPanelTex->Width() + 20.f - pPanelTex->Width(), 10.f));
	//	AddObject(pPanelUI, LAYER::UI);
	//}
}

void CObjectEdit::SelectGameObject(CRockmanObj* obj)
{
	m_curSelectObj = obj;
	m_mouseState = MOUSE_MODE::ONEDOWN;
}

void CObjectEdit::Update()
{
	m_targetPos = GETINSTANCE(CKeyManager)->GetMousePos();

	if (IS_INPUT_TAB(KEY::SPACE))
	{
		GETINSTANCE(CLevelManager)->GetCurLevel()->DeleteAllObject(LAYER::MONSTER);		
	}
	
	if (nullptr != m_detectObj)
	{
		Vector2 rpos = GETINSTANCE(CCamera)->GetRealPos(m_detectObj->GetOwner()->GetPos());
		if (IS_INPUT_PRESSED(KEY::LSHIFT))
		{
			m_targetPos.y = m_detectObj->GetOwner()->GetPos().y;
		}
		if (IS_INPUT_PRESSED(KEY::LCTRL))
		{
			m_targetPos.x = m_detectObj->GetOwner()->GetPos().x;
		}
	}

	if (nullptr != m_curSelectObj && m_mouseState == MOUSE_MODE::ONEDOWN)
	{

		if (IS_INPUT_TAB(KEY::TAB))
		{
			m_monstreState = MONSTER_STATE(((UINT)m_monstreState + 1) % (UINT)MONSTER_STATE::END);
		}

		if (IS_INPUT_TAB(KEY::LBTN))
		{
			CRockmanObj* newObj = m_curSelectObj;

			if (newObj->m_sponType == MONSETER_TYPE::GOSM)
			{
				newObj = new CGosm();
				newObj->m_sponType = MONSETER_TYPE::GOSM;
			}
			else if (newObj->m_sponType == MONSETER_TYPE::TRY)
			{
				newObj = new CTry();
				newObj->m_sponType = MONSETER_TYPE::TRY;
			}
			else if (newObj->m_sponType == MONSETER_TYPE::MIRU)
			{
				newObj = new CMiru();
				newObj->m_sponType = MONSETER_TYPE::MIRU;
			}
			else if (newObj->m_sponType == MONSETER_TYPE::CONG)
			{
				newObj = new CCong();
				newObj->m_sponType = MONSETER_TYPE::CONG;
			}

			newObj->m_monsterState = m_monstreState;

			m_targetPos = GETINSTANCE(CKeyManager)->GetMousePos();
			m_targetPos = GETINSTANCE(CCamera)->GetRealPos(m_targetPos);
			CGameObject::Instantiate(newObj, m_targetPos, LAYER::MONSTER );




			//m_mouseState = MOUSE_MODE::NONE;
			//m_curSelectObj = nullptr;
		}
	}

	if (IS_INPUT_TAB(KEY::R))
	{
		m_curSelectObj = nullptr;
		m_detectObj = nullptr;
	}

	m_targetPos = GETINSTANCE(CKeyManager)->GetMousePos();

}


#pragma region Box

void CObjectEdit::OnTriggerEnter(CCollider* _pOhter)
{
	m_detectObj = _pOhter;
}

void CObjectEdit::OnTriggerStay(CCollider* _pOhter)
{

}

void CObjectEdit::OnTriggerExit(CCollider* _pOhter)
{
	//m_detectObj = nullptr;
	m_detectObj = nullptr;
}
#pragma endregion

void CObjectEdit ::Save(FILE* pFile)
{
	CLevel* lv = GETINSTANCE(CLevelManager)->GetCurLevel();

	//모든벽들
	const vector<CGameObject*>& monsters = lv->GetLayer(LAYER::MONSTER);	

	UINT size = monsters.size();
	fwrite(&size, sizeof(UINT), 1, pFile);

	for (size_t i = 0; i < size; i++)
	{
		CRockmanMonster* monster = dynamic_cast<CRockmanMonster*>(monsters[i]);
		assert(monster);
		MONSETER_TYPE sopneType = monster->m_sponType;
		fwrite(&sopneType, sizeof(MONSETER_TYPE), 1, pFile);
		monster->Save(pFile);
	}
}
void CObjectEdit ::Load(FILE* pFile)
{
	UINT size;

	fread(&size, sizeof(UINT), 1, pFile);
	for (size_t i = 0; i < size; i++)
	{
		MONSETER_TYPE mtype;
		fread(&mtype, sizeof(mtype), 1, pFile);
		CRockmanMonster* monster = nullptr;
		switch (mtype)
		{
		case MONSETER_TYPE::MIRU:
			monster = new CMiru();
			break;
		case MONSETER_TYPE::TRY:
			monster = new CTry();
			break;
		case MONSETER_TYPE::GOSM:
			monster = new CGosm();
			break;				
		case MONSETER_TYPE::CONG:
			monster = new CCong();
			break;
		}		
		assert(monster);		
		
		monster->m_sponType = mtype;
		monster->Load(pFile);
		
		CGameObject::Instantiate(monster, monster->GetPos(), LAYER::MONSTER);
	}
}