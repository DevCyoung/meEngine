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

//helper
#include "CRenderHelper.h"

CObjectEdit::CObjectEdit()
	: m_curSelectObj(nullptr)
	, m_detectObj(nullptr)
	, m_mouseState(MOUSE_MODE::NONE)
	, m_targetPos{}
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(50.f, 50.f));

}

CObjectEdit::CObjectEdit(const CObjectEdit& _other)
	:m_curSelectObj(nullptr)
	, m_detectObj(nullptr)
	, m_mouseState(MOUSE_MODE::NONE)
	, m_targetPos{}
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
			pSaveButton->SetScale(Vector2(100.f, 50.f));
			pSaveButton->SetPos(Vector2(10.f, 20.f));
			pSaveButton->SetDelegate(this, (DELEGATERockman)&CObjectEdit::SelectObject);
			//pSaveButton->SetIdleTex(pButtonTex);
			pSaveButton->SetRockman(new CZero());
			pSaveButton->SetPressedTex(pButtonPressedTex);			
		}
		pPanelUI->AddChildUI(pSaveButton);
		//level->AddObject(pSaveButton, LAYER::UI);


		CButton* pLoadButton = pSaveButton->Clone();
		{
			pLoadButton->SetPos(Vector2(150.f, 20.f));
			pLoadButton->SetRockman(new CMiru());
			pLoadButton->SetDelegate(this, (DELEGATERockman)&CObjectEdit::SelectObject);
		}
		pPanelUI->AddChildUI(pLoadButton);
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

void CObjectEdit::SelectObject(CRockmanObj* obj)
{
	m_curSelectObj = obj;
	m_mouseState = MOUSE_MODE::ONEDOWN;
}

void CObjectEdit::Update()
{
	m_targetPos = GETINSTANCE(CKeyManager)->GetMousePos();
	
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
		if (IS_INPUT_TAB(KEY::LBTN))
		{
			CRockmanObj* newObj = m_curSelectObj->Clone();		
			//m_targetPos = GETINSTANCE(CKeyManager)->GetMousePos();
			m_targetPos = GETINSTANCE(CCamera)->GetRealPos(m_targetPos);
			CGameObject::Instantiate(newObj, m_targetPos, newObj->GetLayer() );
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

