#include "pch.h"
#include "CCyberTargetEffect.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CPlayerController.h"
#include "CZero.h"
#include "CCyberKujacer.h"
#include "CTimeManager.h"


#include "CLevelManager.h"
#include "CLevel.h"
#include "CRockmanLevel.h"




CCyberTargetEffect::CCyberTargetEffect()
	:m_zero(nullptr)
	, m_boss(nullptr)
{
	GetAnimator();
	GetAnimator()->LoadAnimation(L"animation\\effect\\cyberbosseffect\\targeteffect.anim");
	m_renderPer = 3;
	m_offset = Vector2(100.f, 0.f);	
}

CCyberTargetEffect::CCyberTargetEffect(const CCyberTargetEffect& _other)
	: m_zero(nullptr)
	, m_boss(nullptr)
{
}

CCyberTargetEffect::~CCyberTargetEffect()
{
}


void CCyberTargetEffect::tick()
{
	if (m_zero == nullptr)
	{
		CRockmanLevel* lv = dynamic_cast<CRockmanLevel*>(GETINSTANCE(CLevelManager)->GetCurLevel());
		assert(lv);
		if (lv->m_zero == nullptr)
		{
			return;
		}
		m_zero = lv->m_zero;
		assert(m_zero);
	}


	if (m_isUsing == false)
	{
		return;
	}

	if (m_zero == nullptr || m_owner == nullptr)
	{
		m_isUsing = false;
		return;
	}

	if (m_boss == nullptr)
	{
		CCyberKujacer* obj = dynamic_cast<CCyberKujacer*>(m_owner);
		assert(obj);		
		m_boss = obj;
	}

	if (m_boss->m_bossState != CYBERBOSS_STATE::ATTACK3 && m_boss->m_bossState != CYBERBOSS_STATE::ATTACK3SHOOT)
	{
		m_isUsing = false;
		return;
	}

	

	Vector2 dir = m_zero->GetPos() - GetPos();		
	dir.Normalize();

	Vector2 pos =GetPos() + dir * 700.f * DELTATIME;

	float len = (GetPos() - m_zero->GetPos()).Length();

	if (len <= 0.5f)
	{
		pos = m_zero->GetPos();
	}

	SetPos(pos);
}

void CCyberTargetEffect::render(HDC _dc)
{
	if (m_isUsing == false)
		return;

	if (m_boss->m_bossState == CYBERBOSS_STATE::HPZERO)
	{
		return;
	}
	CEffect::render(_dc);
}



void CCyberTargetEffect::OnShootPlay(Vector2 pos, bool isFlipX)
{
	CEffect::OnShootPlay(pos, isFlipX);
	GetAnimator()->Play(L"TARGETEFFECT", true);
}
