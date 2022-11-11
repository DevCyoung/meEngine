#pragma once

class CGameObject;

enum class eHitInfo
{
	ULTIMATE,
	DELAYHIT,
	DEFAULTHIT,
};


class CHitManager
{
	SINGLETON(CHitManager);

	vector<tAnimFrm>	m_vecDuration;
	float				m_hitTimedselay;

public:
	void tick();
	void AddAtackDelay(tAnimFrm& frm) { m_vecDuration.push_back(frm); }
};

