#pragma once
#include "CEventBox.h"




class CCameraWall;
class CWall;

enum class DOORSTATE
{
	IDLE,
	OPEN,
	CLOSE,
	NONE,
	SPONMONSTER,
	EMD,
};

class CDoor1 :
    public CEventBox
{
public:

	CWall*			m_wall;
	CCameraWall*	m_cameraWall;
	DOORSTATE		m_state;
	float			m_destPos;
	float			m_zeroPos;
	virtual void tick() override;
	virtual void render(HDC _dc) override;

public:
	virtual void OnTriggerEnter(CCollider* _pOther);

	void WorkDoor();
	void InterRactDoor();

public:
	CDoor1();
	~CDoor1();

	// CEventBox을(를) 통해 상속됨
	virtual void Save(FILE* pFile) override;
	virtual void Load(FILE* pFile) override;
};

