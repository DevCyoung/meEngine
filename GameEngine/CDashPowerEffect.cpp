#include "pch.h"
#include "CDashPowerEffect.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CPlayerController.h"
#include "CZero.h"


CDashPowerEffect::CDashPowerEffect()
	:m_zero(nullptr)
{
	GetAnimator();
	GetAnimator()->LoadAnimation(L"animation\\effect\\chareffect\\landdashpower.anim");
	m_renderPer = 3;
	m_offset = Vector2(100.f, +34.f);
}

CDashPowerEffect::CDashPowerEffect(const CDashPowerEffect& _other)	
	:m_zero(nullptr)
{
}

CDashPowerEffect::~CDashPowerEffect()
{
}

void CDashPowerEffect::tick()
{
	if (m_isUsing == false)
	{
		return;
	}

	if (GetAnimator()->GetCurAnimation()->IsFinish() == true)
	{
		m_isUsing = false;
		return;
	}

	if (m_zero == nullptr)
	{
		m_isUsing = false;
		return;
	}

	if (m_zero->GetState() != PLAYER_STATE::DASH)
	{
		m_isUsing = false;
		return;
	}

	Vector2 pos = m_zero->GetPos();
	Vector2 offset = m_offset;
	if (GetFlipX() == false)
	{
		offset.x *= -1;
	}

	pos += offset;
	SetPos(pos);
	CEffect::tick();
}

void CDashPowerEffect::render(HDC _dc)
{
	if (m_isUsing == false)
		return;
	CEffect::render(_dc);
}



void CDashPowerEffect::OnShootPlay(Vector2 pos, bool isFlipX)
{
	CEffect::OnShootPlay(pos, isFlipX);
	GetAnimator()->Play(L"LANDDASHPOWER", false);
}

