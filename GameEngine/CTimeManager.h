#pragma once
class CTimeManager
{
	SINGLETON(CTimeManager);


private:
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;

	UINT			m_iCallCount;
	float			m_fDeltaTime;
	float			m_fTime;
	float			m_delay;

public:
	void init();
	void tick();
	void render();

public:
	void  SetDelayTime(float delay) { m_delay = delay; }
	float GetDeltaTime() { return m_fDeltaTime * m_delay; }
	float GEtRealDetaTime() { return m_fDeltaTime; }
};

