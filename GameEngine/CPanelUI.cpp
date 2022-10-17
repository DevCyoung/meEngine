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

//Ʈ�������� �ϸ�����?
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

	//�θ��ʿ��� �ڱ����� �ٳ����� ���������� �ڽ��������Ͻ�Ŵ
	CUI::tick();
}

void CPanelUI::render(HDC _dc)
{
	//���� �ؽ�ó�������� �ڽ��� �׸���������
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
