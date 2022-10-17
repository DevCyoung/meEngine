#include "pch.h"
#include "CUI.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CKeyManager.h"
#include "CTexture.h"


CUI::CUI()
	: m_bLbtnDown(false)
	, m_bMouseOn(false)
	, m_bCmrAfctd(false)
	, m_pParentUI(nullptr)
	, m_pIdleTex(nullptr)
{
}

CUI::CUI(const CUI& _other)
	: CGameObject(_other)
	, m_pParentUI(nullptr)
	, m_pIdleTex(_other.m_pIdleTex)
	, m_bLbtnDown(false)
	, m_bMouseOn(false)
	, m_bCmrAfctd(_other.m_bCmrAfctd)
{
	for (size_t i = 0; i < _other.m_vecChildUI.size(); i++)
	{
		AddChildUI(_other.m_vecChildUI[i]->Clone());		
	}
}

CUI::~CUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		delete m_vecChildUI[i];
	}
}

//UI�� �������ؾ��Ѵ�.
void CUI::tick()
{
	// ���콺 üũ �ϱ����� ��ġ ���
	m_vFinalPos = GetPos();

	if (m_pParentUI)
	{
		m_vFinalPos += m_pParentUI->GetFinalPos();
	}

	// ���콺 üũ
	MouseOnCheck();

	//Child UI call tick
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick();
	}
}


void CUI::render(HDC _dc)
{
	//�浹ü�� �׸���.
	HPEN hPen = GETINSTANCE(CEngine)->GetPen(PEN_TYPE::GREEN);
	HBRUSH	hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN	hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH	hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	//ī�޶��̵��� UI�������� �״���������� ��Ȳ������ �ڽ��� �ٸ��Լ����Ҽ��־����.
	//Vector2 vPos = GETINSTANCE(CCamera)->GetRenderPos(m_vFinalPos);
	//�׳ɺ�����ġ�μ���
	Vector2 vPos = GetPos();

	if (m_bCmrAfctd)
	{
		vPos = GETINSTANCE(CCamera)->GetRenderPos(vPos);
	}

	Vector2 vScale = GetScale();
	//Vector2 vPos = GetOwner()->GetPos();

	Rectangle
	(
		_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y)
	);

	//��� �귯�� �ǵ�����
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);

	render_childUI(_dc);
}

void CUI::render_childUI(HDC _dc)
{
	//�ڽ� UI render �θ� ���� �׷������մϴ�.
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::SetIdleTex(CTexture* _pTex)
{
	m_pIdleTex = _pTex;

	if (nullptr != m_pIdleTex)
	{
		Vector2 vScale = Vector2((float)m_pIdleTex->Width(), (float)m_pIdleTex->Height());
		SetScale(vScale);
	}
}

void CUI::MouseOnCheck()
{
	
	Vector2 vPos = GetFinalPos();
	Vector2 vScale = GetScale();
	Vector2 vMousePos = GETINSTANCE(CKeyManager)->GetMousePos();
	if (m_bCmrAfctd)
	{
		vMousePos = GETINSTANCE(CCamera)->GetRealPos(vMousePos);
	}

	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x && vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
	{		
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}


}