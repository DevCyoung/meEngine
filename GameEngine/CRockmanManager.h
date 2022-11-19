#pragma once

enum class ROCKEVENT
{
	NONE,
	BOSSDIE,
	WIN,
	RETURNHONE,
	ZEROGOOD,
	ZERORETURN,
	FADEEXIT,
	ZERODIE,
	ZERODIEFINISH,
	TODUMMYLEVEL,
	END
};

class CSound;

class CRockmanManager
{
	SINGLETON(CRockmanManager);

private:
	ROCKEVENT	m_event;
	eFADECOLOR  m_fadeColor;
	float		m_stateDelay;

	float		m_whiteDelay;
	float		m_zeroDelay;
	float		m_dumyDleay;
	bool		m_isWhite;

	Vector2		m_tartget;
	Vector2		m_offset;

public:
	int			m_zeroLife;
	int			m_zeroCurHP;
	int			m_zeroMaxHp;

public:
	CSound* m_backGroundsound;

public:
	LEVEL_TYPE	m_nextLevel;

public:
	void tick();
	

public:
	void BossDieBoom(Vector2 monsterPos);
	void SetEvent(ROCKEVENT _event);
	ROCKEVENT GetTarget() { return m_event; }

	void SetTarget(Vector2 vec) {m_tartget = vec;}

	

};

