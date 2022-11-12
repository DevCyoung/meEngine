#include "pch.h"
#include "CEffect.h"
#include "CAnimator.h"
#include "CAnimation.h"

CEffect::CEffect()
	:m_target(nullptr)
	, m_offset{}
	, m_position{}
	, m_isUsing(false)
	, m_playType(EFFECTPLAY_TYPE::NONE)
{
	CreateAnimator();
	m_playType = EFFECTPLAY_TYPE::ONESHOOT;
	m_renderPer = 2.5f;
}

CEffect::CEffect(const CEffect& _other)
	: m_target(nullptr)
	, m_offset{}
	, m_position{}
	, m_isUsing(false)
	, m_playType(EFFECTPLAY_TYPE::NONE)
{

}

CEffect::~CEffect()
{

}

void CEffect::tick()
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

	CRockmanObj::tick();
}

void CEffect::render(HDC _dc)
{
	if (m_isUsing == false)
	{
		return;
	}

	CRockmanObj::render(_dc);
}

void CEffect::OnShootPlay(Vector2 pos, bool isFlipX)
{
	m_isUsing = true;
	SetPos(pos);
	SetFlipX(isFlipX);
}

void CEffect::LoadAnimation(const std::wstring relativePath)
{
	GetAnimator()->LoadAnimation(relativePath);
}

