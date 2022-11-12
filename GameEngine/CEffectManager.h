#pragma once

#define EFFECTPULLSIZE	15
class CEffect;
class CZero;

class CEffectManager
{
	SINGLETON(CEffectManager);

	vector<CEffect*>	m_vecEffect[(UINT)EFFECT_TYPE::END];
	UINT				m_curiDX[(UINT)EFFECT_TYPE::END];

public:
	void tick();
	void LoadAllEffect();
	void OnShootPlay(EFFECT_TYPE type, Vector2 pos, bool isFlipX);

	void SetPlayerTarget(CZero* target);
};

