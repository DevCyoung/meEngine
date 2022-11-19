#include "pch.h"
#include "CEffectManager.h"
#include "CEffect.h"

#include "CTinEffect.h"
#include "CSliceEffect.h"
#include "CLandDash.h"
#include "CSlideDustEffect.h"
#include "CDashPowerEffect.h"
#include "CWallHitEffect.h"
#include "CRedBoomEffect.h"

#include "CCyberTargetEffect.h"
#include "CZero.h"

CEffectManager::CEffectManager()
	:m_curiDX{}
{
	int a = 0;
}

CEffectManager::~CEffectManager()
{

}

void CEffectManager::tick()
{

}


void CEffectManager::OnShootPlay(EFFECT_TYPE type, Vector2 pos, bool isFlipX)
{
	if (type == EFFECT_TYPE::LANDDASHPOWER)
	{
		m_vecEffect[(UINT)EFFECT_TYPE::LANDDASHPOWER][0]->OnShootPlay(pos, isFlipX);
		return;
	}

	if (type == EFFECT_TYPE::CYBERTARGET)
	{
		m_vecEffect[(UINT)EFFECT_TYPE::CYBERTARGET][0]->OnShootPlay(pos, isFlipX);
		return;
	}
	UINT idx = m_curiDX[(UINT)type];

	m_vecEffect[(UINT)type][idx]->OnShootPlay(pos, isFlipX);
	++m_curiDX[(UINT)type];
	m_curiDX[(UINT)type] %= EFFECTPULLSIZE;
}

void CEffectManager::OnShootPlay(EFFECT_TYPE type, Vector2 pos, bool isFlipX, CRockmanObj* owner)
{	
	m_vecEffect[(UINT)type][0]->m_owner = owner;
	OnShootPlay(type, pos, isFlipX);
}

void CEffectManager::SetPlayerTarget(CZero* target)
{
	CDashPowerEffect* dpEffect = dynamic_cast<CDashPowerEffect*>(m_vecEffect[(UINT)EFFECT_TYPE::LANDDASHPOWER][0]);
	assert(dpEffect);
	dpEffect->m_zero = target;
}

void CEffectManager::LoadAllEffect()
{

	for (size_t i = 0; i < (UINT)EFFECT_TYPE::END; i++)
	{
		m_vecEffect[i].clear();
	}

	for (size_t i = 0; i < (UINT)EFFECT_TYPE::END; i++)
	{
		m_curiDX[i] = 0;
	}



	
	for (size_t i = 0; i < EFFECTPULLSIZE; i++)
	{
		CEffect* effect = new CTinEffect();
		m_vecEffect[(UINT)EFFECT_TYPE::TIN].push_back(effect);
		CGameObject::Instantiate(effect, effect->GetPos(), LAYER::EDITOR);
	}

	for (size_t i = 0; i < EFFECTPULLSIZE; i++)
	{
		CEffect* effect = new CSliceEffect();
		m_vecEffect[(UINT)EFFECT_TYPE::SLOPSLICE].push_back(effect);
		CGameObject::Instantiate(effect, effect->GetPos(), LAYER::EDITOR);
	}

	for (size_t i = 0; i < EFFECTPULLSIZE; i++)
	{
		CEffect* effect = new CLandDash();
		m_vecEffect[(UINT)EFFECT_TYPE::LANDDASH].push_back(effect);
		CGameObject::Instantiate(effect, effect->GetPos(), LAYER::EDITOR);
	}

	for (size_t i = 0; i < EFFECTPULLSIZE; i++)
	{
		CEffect* effect = new CSlideDustEffect();
		m_vecEffect[(UINT)EFFECT_TYPE::WALLSLIDEDUST].push_back(effect);
		CGameObject::Instantiate(effect, effect->GetPos(), LAYER::EDITOR);
	}

	for (size_t i = 0; i < EFFECTPULLSIZE; i++)
	{
		CEffect* effect = new CWallHitEffect();
		m_vecEffect[(UINT)EFFECT_TYPE::WALLHIT].push_back(effect);
		CGameObject::Instantiate(effect, effect->GetPos(), LAYER::EDITOR);
	}




	{
		CEffect* effect = new CDashPowerEffect();
		m_vecEffect[(UINT)EFFECT_TYPE::LANDDASHPOWER].push_back(effect);
		CGameObject::Instantiate(effect, effect->GetPos(), LAYER::EDITOR);
	}

	for (size_t i = 0; i < EFFECTPULLSIZE; i++)
	{
		CEffect* effect = new CRedBoomEffect();
		m_vecEffect[(UINT)EFFECT_TYPE::BOOMRED].push_back(effect);
		CGameObject::Instantiate(effect, effect->GetPos(), LAYER::EDITOR);
	}

	{
		CEffect* effect = new CCyberTargetEffect();
		m_vecEffect[(UINT)EFFECT_TYPE::CYBERTARGET].push_back(effect);
		CGameObject::Instantiate(effect, effect->GetPos(), LAYER::EDITOR);
	}
}