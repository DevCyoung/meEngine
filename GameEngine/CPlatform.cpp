#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"
#include "CRigidbody.h"
#include "CPlayer.h"


CPlatform::CPlatform()
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(400.f, 50.f));
}

CPlatform::~CPlatform()
{
}

void CPlatform::OnTriggerEnter(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;
	
	pPlayer->GetRigidbody()->SetGround(true);
}

void CPlatform::OnTriggerStay(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());

	Vector2 pos = pPlayer->GetPos();
	Vector2 platPos = this->GetPos();

	if (platPos.y - pos.y < pPlayer->GetCollider()->GetScale().y + GetCollider()->GetScale().y)
	{
		pos.y = platPos.y + (-pPlayer->GetCollider()->GetScale().y / 2 - GetCollider()->GetScale().y / 2);
		//pos.y = platPos.y - (GetCollider()->GetScale().y / 2);
	}
	pPlayer->SetPos(pos);
}

void CPlatform::OnTriggerExit(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;

	pPlayer->GetRigidbody()->SetGround(false);
}