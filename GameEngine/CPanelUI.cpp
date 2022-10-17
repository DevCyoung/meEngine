#include "pch.h"
#include "CPanelUI.h"
#include "CTexture.h"
#include "CKeyManager.h"


CPanelUI::CPanelUI()
{
}

CPanelUI::~CPanelUI()
{
}

//트리구조로 하면좋나?
void CPanelUI::tick()
{

	if (IsLbtnDown())
	{
		Vector2 vMove = GETINSTANCE(CKeyManager)->GetMousePos() - m_vPressedPos;
		Vector2 vPos = GetPos();

		vPos += vMove;
		SetPos(vPos);

		m_vPressedPos = GETINSTANCE(CKeyManager)->GetMousePos();
	}

	//부모쪽에서 자기할일 다끝내고 계층적으로 자식한테할일시킴
	CUI::tick();
}

void CPanelUI::render(HDC _dc)
{
	//나의 텍스처가업스면 자식은 그리지도않음
	if (nullptr == GetIdleTex())
		return;
	Vector2 vPos = GetPos();
	TransparentBlt(_dc, vPos.x, vPos.y, GetIdleTex()->Width(), GetIdleTex()->Height(), GetIdleTex()->GetDC(), 0, 0, GetIdleTex()->Width(), GetIdleTex()->Height(), RGB(255, 0, 255));


	render_childUI(_dc);
}

void CPanelUI::MouseLbtnDown()
{
	CUI::MouseLbtnDown();
	m_vPressedPos = GETINSTANCE(CKeyManager)->GetMousePos();
}

void CPanelUI::MouseLbtnClicked()
{
	int a = 0;
}
