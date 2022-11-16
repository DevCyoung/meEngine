#include "pch.h"
#include "CCyberMissile.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CLine.h"
#include "CTimeManager.h"
#include "CLevelManager.h"

#include "CZero.h"
#include <cmath>

CCyberMissile::CCyberMissile()
	:m_zero(nullptr)
	, m_lifeTIme(0.f)
	, m_isBall(false)
	, m_deadTime(0.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(30.f, 30.f));	

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\missile\\missiledown.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\missile\\missileleft.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\missile\\missileleftdown.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\missile\\missileleftdowndown.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\missile\\missileleftdowndowndown.anim");

	GetAnimator()->LoadAnimation(L"animation\\monster\\cyberboss\\missile\\attack3ball.anim");

	GetAnimator()->Play(L"MISSILELEFT", true);

	m_isCollision = false;

	m_zero = GETINSTANCE(CLevelManager)->GetPlayerObject();
}

CCyberMissile::CCyberMissile(const CCyberMissile& _other)
	:m_zero(nullptr)
	, m_lifeTIme(0.f)
	, m_isBall(false)
	, m_deadTime(0.f)
{
}

CCyberMissile::~CCyberMissile()
{
}


void CCyberMissile::tick()
{
	m_lifeTIme += DELTATIME;
	if (m_lifeTIme >= 1.5f)
	{
		
		m_isBall = true;
	}

	if (m_isBall == true)
	{
		m_deadTime += DELTATIME;
		if (m_deadTime >= 1.3f)
		{
			this->Destroy();
		}
	}

	if (m_isBall == true)
	{
		GetAnimator()->TrigerPlay(L"ATTACK3BALL", true);
		return;
	}

	
	Vector2 dir = m_zero->GetPos() - GetPos();
	dir.Normalize();

	Vector2 pos = GetPos() + dir * 300.f * DELTATIME;

	pos.x = GetPos().x + dir.x * 520.f * DELTATIME;
	pos.y = GetPos().y + dir.y * 400.f * DELTATIME;

	float len = (GetPos() - m_zero->GetPos()).Length();

	double x = dir.x;
	double y = dir.y;

	if (dir.x > 0)
	{
		x *= 1.f;
	}
	else
	{
		x *= -1.f;
	}

	if (dir.y > 0)
	{
		y *= 1.f;
	}
	else
	{
		y *= -1.f;
	}

	double angleInRadians = std::atan2(y, x);

	int angleInDegrees = (angleInRadians / 3.14f) * 180.0;




	//1사분면
	if (0 <= angleInDegrees && angleInDegrees <= 18)
	{
		GetAnimator()->TrigerPlay(L"MISSILELEFT", true);
	}
	else if (18 <= angleInDegrees && angleInDegrees <= 36)
	{

		if (x >= 0)
		{
			//1사분면
			if (y <= 0)
			{
				int a = 0;
			}
		}
		GetAnimator()->TrigerPlay(L"MISSILELEFTD", true);
	}
	else if (36 <= angleInDegrees && angleInDegrees <= 54)
	{
		GetAnimator()->TrigerPlay(L"MISSILELEFTDD", true);
	}
	else if (54 <= angleInDegrees && angleInDegrees <= 72)
	{
		GetAnimator()->TrigerPlay(L"MISSILELEFTDDD", true);
	}
	else if (72 <= angleInDegrees && angleInDegrees <= 90)
	{
		GetAnimator()->TrigerPlay(L"MISSILEDOWN", true);
	}


	if (len <= 0.5f)
	{
		pos = m_zero->GetPos();
	}

	if (dir.x > 0.f)
	{
		SetFlipX(true);
	}
	else
	{
		SetFlipX(false);
	}

	if (dir.y < 0.f)
	{
		SetFilpY(true);
	}
	else
	{
		SetFilpY(false);
	}

	SetPos(pos);
}

void CCyberMissile::fixed_tick()
{
}

void CCyberMissile::render(HDC _dc)
{
	CRockmanMonster::render(_dc);
}

void CCyberMissile::OnTriggerEnter(CCollider* _pOhter)
{
	if (_pOhter->GetOwner()->GetLayer() == LAYER::PLAYER)
	{
		GetAnimator()->TrigerPlay(L"ATTACK3BALL", true);
		m_isBall = true;
		//this->Destroy();
	}
}

void CCyberMissile::OnTriggerStay(CCollider* _pOhter)
{
}

void CCyberMissile::OnTriggerExit(CCollider* _pOhter)
{
}

