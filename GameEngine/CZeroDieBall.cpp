#include "pch.h"
#include "CZeroDieBall.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTimeManager.h"

CZeroDieBall::CZeroDieBall()
	:m_dir{}
	,m_timeDelay(0.f)
{
	GetAnimator()->LoadAnimation(L"animation\\effect\\chareffect\\dieball.anim");
	m_renderPer = 3.0f;
}

CZeroDieBall::CZeroDieBall(const CZeroDieBall& _other)
{
}

CZeroDieBall::~CZeroDieBall()
{
}



void CZeroDieBall::tick()
{
	if (m_isUsing == false)
	{
		return;
	}

	m_timeDelay += DELTATIME;

	if (m_timeDelay >= 0.8f)
	{
		m_isUsing = false;
		return;
	}

	CRockmanObj::tick();

	Vector2 pos = GetPos();
	pos += m_dir * DELTATIME * 600.f;
	SetPos(pos);
}

void CZeroDieBall::OnShootPlay(Vector2 pos, bool isFlipX)
{
	CEffect::OnShootPlay(pos, isFlipX);
	Vector2 dir = {};
	dir.x = cosf(rand() % 360);
	dir.y = sinf(rand() % 360);
	m_dir = dir;
	m_timeDelay = 0.f;
	GetAnimator()->Play(L"DIEBALL", true);
}

