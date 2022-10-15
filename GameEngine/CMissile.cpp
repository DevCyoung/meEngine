#include "pch.h"
#include "CMissile.h"
#include "CTimeManager.h"
#include "CCamera.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CEventManager.h"

CMissile::CMissile()
	: m_fSpeed(400.f)
	, m_angle(270.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(15.f, 15.f));
	GetCollider()->SetOffsetPos(Vector2(0.f, 0.f));

	this->SetScale(Vector2(25.f, 25.f));
}

CMissile::~CMissile()
{

}


void CMissile::tick()
{
	Vector2 pos = this->GetPos();

	pos.x += cosf(RAD * m_angle) * m_fSpeed * DELTATIME;
	pos.y += sinf(RAD * m_angle) * m_fSpeed * DELTATIME;

	this->SetPos(pos);
	CGameObject::tick();
}

void CMissile::render(HDC _dc)
{
	Vector2 pos = this->GetPos();
	Vector2 scale = this->GetScale();

	pos = GETINSTANCE(CCamera)->GetRenderPos(pos);
	Rectangle(
		_dc
		, pos.x - scale.x / 2
		, pos.y - scale.y / 2
		, pos.x + scale.x / 2
		, pos.y + scale.y / 2);

	//충돌체등 그리기
	CGameObject::render(_dc);
}

void CMissile::OnTriggerEnter(CCollider* _pOhter)
{
	this->Destroy();
}

void CMissile::OnTriggerStay(CCollider* _pOhter)
{

}

void CMissile::OnTriggerExit(CCollider* _pOhter)
{

}

