#include "pch.h"
#include "CCongBullet.h"
#include "CTimeManager.h"
#include "CCollider.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CZero.h"

#include "CLevelManager.h"

CCongBullet::CCongBullet()
	:m_speed(0.f)
	, m_dir{}
	, m_isHit(false)
	, m_lifeTime(0.f)
{

	CreateCollider();
	GetCollider()->SetScale(Vector2(15.f, 15.f));

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\cong\\bullet.anim");
	GetAnimator()->Play(L"ATTACK", true);

	m_speed = 450.f;
}

CCongBullet::CCongBullet(const CCongBullet& _other)
	:m_speed(0.f)
	, m_dir{}
	, m_isHit(false)
	, m_lifeTime(0.f)
{
}

CCongBullet::~CCongBullet()
{
}

void CCongBullet::tick()
{
	if (m_isHit)
	{
		this->Destroy();
	}

	CRockmanMonster::tick();
	Vector2 pos = GetPos();

	if (m_dir.x < 0)
	{
		pos.x -= m_speed * DELTATIME;
	}
	else
	{
		pos.x += m_speed * DELTATIME;
	}

	m_lifeTime += DELTATIME;

	if (m_lifeTime >= 20.f)
	{
		this->Destroy();
	}
	

	SetPos(pos);
}

void CCongBullet::render(HDC _dc)
{
	CRockmanMonster::render(_dc);
}



void CCongBullet::OnTriggerEnter(CCollider* _pOther)
{
	CRockmanMonster::OnTriggerEnter(_pOther);

	if (LAYER::PLAYER == _pOther->GetOwner()->GetLayer())
	{
		CZero* zero = GETINSTANCE(CLevelManager)->GetPlayerObject();
		if (DAMAGED_STATE::ULTIMAGE != zero->m_damagedState)
		{
			m_isHit = true;
		}			
	}
}





