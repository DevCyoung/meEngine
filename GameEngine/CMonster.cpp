#include "pch.h"
#include "CMonster.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CCamera.h"

//test
#include "CTexture.h"
#include "CResourceManager.h"
#include "CKeyManager.h"


CTexture* m_pTexuture;

CMonster::CMonster()
{
	this->CreateCollider();
	this->GetCollider()->SetOffsetPos(Vector2(0.f, 0.f));
	this->GetCollider()->SetScale(Vector2(50.f, 50.f));
	m_pTexuture = GETINSTANCE(CResourceManager)->LoadTexture(L"Player", L"texture\\ppap.bmp");
}

CMonster::~CMonster()
{
}


void CMonster::tick()
{
	CGameObject::tick();

	if (IS_INPUT_TAB(KEY::LBTN))
	{
		Vector2 pos = GETINSTANCE(CKeyManager)->GetMousePos();
		//MousePosition
	}
}

void CMonster::render(HDC _dc)
{
	/*Vector2 pos = this->GetPos();
	Vector2 scale = this->GetScale();
	pos = GETINSTANCE(CCamera)->GetRenderPos(pos);
	Rectangle(
		_dc
		, pos.x - scale.x / 2
		, pos.y - scale.y / 2
		, pos.x + scale.x / 2
		, pos.y + scale.y / 2);*/



	//tes
	Vector2 pos = this->GetPos();
	Vector2 scale = this->GetScale();

	pos = GETINSTANCE(CCamera)->GetRenderPos(pos);

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = 1;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f);
	tBlend.SourceConstantAlpha = 255;
	AlphaBlend
	(
		_dc,
		pos.x - m_pTexuture->Width() / 2,
		pos.y - m_pTexuture->Height() / 2,
		m_pTexuture->Width(),
		m_pTexuture->Height(),
		m_pTexuture->GetDC(),
		0,
		0,
		m_pTexuture->Width(),
		m_pTexuture->Height(),
		tBlend
	);

	//충돌체등 그리기
	CGameObject::render(_dc);
}

void CMonster::OnTriggerEnter(CCollider* _pOhter)
{
}

void CMonster::OnTriggerStay(CCollider* _pOhter)
{
}

void CMonster::OnTriggerExit(CCollider* _pOhter)
{
}