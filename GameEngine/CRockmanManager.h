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
	END
};

class CRockmanManager
{
	SINGLETON(CRockmanManager);

private:
	ROCKEVENT	m_event;
	eFADECOLOR  m_fadeColor;
	float		m_stateDelay;

	float		m_whiteDelay;
	bool		m_isWhite;

	Vector2		m_tartget;
	Vector2		m_offset;

public:
	void tick();
	

public:
	void BossDieBoom(Vector2 monsterPos);
	void SetEvent(ROCKEVENT _event);
	ROCKEVENT GetTarget() { return m_event; }

	void SetTarget(Vector2 vec) {m_tartget = vec;}

	

};

