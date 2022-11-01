#include "pch.h"
#include "CButton.h"

#include "CLevelManager.h"
#include "CEditorLevel.h"
#include "CLevel.h"
#include "CTexture.h"
#include "CRockmanObj.h"

#include "CAnimator.h"
#include "CAnimation.h"

CButton::CButton()
	: m_pPressedTex(nullptr)
	, m_pHighlightTex(nullptr)
	, m_pInst(nullptr)
	, m_pDelegateFunc(nullptr)
	, m_rockObj(nullptr)
{
}

CButton::~CButton()
{
	if (nullptr != m_rockObj)
	{
		delete m_rockObj;
	}
}

void CButton::render(HDC _dc)
{
	CTexture* pTargetTex = GetIdleTex();

	if (IsLbtnDown())
	{
		if (m_pPressedTex)
			pTargetTex = m_pPressedTex;
	}
	else if (IsMouseOn())
	{
		if (m_pHighlightTex)
			pTargetTex = m_pHighlightTex;
	}

	
	Vector2 vPos = GetFinalPos();

	if (nullptr != m_rockObj)
	{
		CAnimation* anim = m_rockObj->GetAnimator()->FindAnimation(L"IDLE");
		HDC src = anim->GetAtlas()->GetDC();

		tAnimFrm frm = anim->GetFrame(0);

		TransparentBlt(_dc, vPos.x, vPos.y, frm.vSize.x, frm.vSize.y, src, frm.vLeftTop.x, frm.vLeftTop.y, frm.vSize.x, frm.vSize.y, RGB(255, 0, 255));
		return;
	}

	if (!pTargetTex)
	{
		CUI::render(_dc);
		return;
	}
	BitBlt(_dc, vPos.x, vPos.y, pTargetTex->Width(), pTargetTex->Height(), pTargetTex->GetDC(), 0, 0, SRCCOPY);

	//까먹지말고 자식유아이 렌더링 호출
	render_childUI(_dc);
}

void CButton::MouseLbtnClicked()
{
	if (m_pInst && m_pDelegateFunc)
	{
		(m_pInst->*m_pDelegateFunc)();
	}

	if (m_rockObj && m_pInstRock && m_pDelegateFuncRock)
	{
		(m_pInstRock->*m_pDelegateFuncRock)(m_rockObj);
	}
}
