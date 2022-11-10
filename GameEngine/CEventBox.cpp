#include "pch.h"
#include "CEventBox.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CZero.h"
#include "CCollisionManager.h"

CEventBox::CEventBox()
	: m_evt{}
	, m_mode{}
	, m_zero(nullptr)
	, m_bCollison(false)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(50.f, 50.f));
}

CEventBox::~CEventBox()
{
}


void CEventBox::tick()
{
	CRockmanObj::tick();
}

void CEventBox::render(HDC _dc)
{
	if (GETINSTANCE(CCollisionManager)->GetDrawCollide() == false)
		return;
	CRockmanObj::render(_dc);
}

void CEventBox::SetCollisionEvent(CEntity* obj, DELEGATE func)
{	
	m_evt.func = func;
	m_evt.instance = obj;
}

void CEventBox::OnTriggerEnter(CCollider* _pOther)
{
	if (LAYER::PLAYER == _pOther->GetOwner()->GetLayer())
	{
		m_zero = dynamic_cast<CZero*>(_pOther->GetOwner());
	}
}

void CEventBox::ResizeCollider(Vector2 leftTop, Vector2 bottom)
{
	//중심점구하기

	Vector2 pos = {};
	Vector2 scale = {};
	Vector2 l = {};
	Vector2 b = {};


	scale.x = abs(bottom.x - leftTop.x);
	scale.y = abs(bottom.y - leftTop.y);

	l.x = min(leftTop.x, bottom.x);
	l.y = min(leftTop.y, bottom.y);
	b.x = max(leftTop.x, bottom.x);
	b.y = max(leftTop.y, bottom.y);

	leftTop = l;

	pos.x = leftTop.x + scale.x / 2;
	pos.y = leftTop.y + scale.y / 2;

	GetCollider()->SetScale(scale);
	SetPos(pos);
}