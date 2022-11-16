#include "pch.h"
#include "CCyberCongBullet.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CLine.h"
#include "CTimeManager.h"
#include "CZero.h"
#include "CAnimation.h"
#include <cmath>


#include "CCollider.h"

#include "CLevelManager.h"

CCyberCongBullet::CCyberCongBullet()
	:m_lifeTIme(0.f)
	, m_deadTime(0.f)
	, m_targetdir{}
	, m_isBall(false)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(10.f, 10.f));

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\bullet\\boom.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\bullet\\idle.anim");

	CreateRigidbody();
	GetRigidbody()->SetGravity(false);

	m_hp = 1;
	m_deadTime = 20.f;
	GetAnimator()->Play(L"IDLE", true);
}

CCyberCongBullet::CCyberCongBullet(const CCyberCongBullet& _other)
	:m_lifeTIme(0.f)
	, m_deadTime(0.f)
	, m_targetdir{}
	, m_isBall(false)
{
}

CCyberCongBullet::~CCyberCongBullet()
{
}


void CCyberCongBullet::tick()
{
	CRockmanMonster::tick();


	Vector2 pos = GetPos();
	m_lifeTIme += DELTATIME;

	if (m_lifeTIme >= 20.f)
	{
		this->Destroy();
		return;
	}

	if (m_isBall == true && GetAnimator()->GetCurAnimation()->IsFinish() == true)
	{
		this->Destroy();
		return;
	}

	if (m_isBall == true)
		return;
	pos += m_targetdir * 200.f * DELTATIME;
	SetPos(pos);
}


void CCyberCongBullet::OnTriggerEnter(CCollider* _pOhter)
{
	if (m_isBall == true)
		return;

	CRockmanMonster::OnTriggerEnter(_pOhter);

	if (_pOhter->GetOwner()->GetLayer() == LAYER::PLAYER)
	{
		CZero* zero = GETINSTANCE(CLevelManager)->GetPlayerObject();
		if (DAMAGED_STATE::ULTIMAGE != zero->m_damagedState)
		{
			GetAnimator()->TrigerPlay(L"BOOM", false);
			m_isBall = true;
		}


	}
	else if (_pOhter->GetOwner()->GetLayer() == LAYER::WALL)
	{
		GetAnimator()->TrigerPlay(L"BOOM", false);
		m_isBall = true;		
	}
}


