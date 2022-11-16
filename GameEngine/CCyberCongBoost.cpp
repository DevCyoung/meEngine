#include "pch.h"
#include "CCyberCongBoost.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CLine.h"
#include "CTimeManager.h"
#include "CZero.h"
#include <cmath>


CCyberCongBoost::CCyberCongBoost()
	:m_offset{}
	, m_target(nullptr)
	, m_isMove(false)
{	
	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\moveboost.anim");
	GetAnimator()->LoadAnimation(L"animation\\monster\\flycong\\idleboost.anim");
}	 

CCyberCongBoost::CCyberCongBoost(const CCyberCongBoost& _other)
	:m_offset{}
	, m_target(nullptr)
	, m_isMove(false)
{

}

CCyberCongBoost::~CCyberCongBoost()
{
}

void CCyberCongBoost::tick()
{
	CRockmanMonster::tick();

	Vector2 pos = m_target->GetPos();

	if (m_target->GetFlipX() == true)
	{
		pos += m_offset;
	}
	else
	{
		pos -= m_offset;
	}

	if (m_isMove == true)
	{
		GetAnimator()->TrigerPlay(L"MOVEBOOST", true);
	}
	else
	{
		GetAnimator()->TrigerPlay(L"IDLEBOOST", true);
	}

	SetPos(pos);
}
