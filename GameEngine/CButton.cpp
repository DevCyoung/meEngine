#include "pch.h"
#include "CButton.h"

#include "CLevelManager.h"
#include "CEditorLevel.h"
#include "CLevel.h"
#include "CTexture.h"

CButton::CButton()
	: m_pPressedTex(nullptr)
	, m_pHighlightTex(nullptr)
	, m_pInst(nullptr)
	, m_pDelegateFunc(nullptr)
{
}

CButton::~CButton()
{

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

	if (!pTargetTex)
	{
		CUI::render(_dc);
		return;
	}

	Vector2 vPos = GetFinalPos();
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
}
