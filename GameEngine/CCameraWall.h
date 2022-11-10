#pragma once
#include "CWall.h"

class CCameraWall :
    public CWall
{
public:

	COLLIDE_DIR m_dir;

	virtual void OnTriggerStay(CCollider* _pOther);
	

public:
	CLONE(CWall);

	void Save(FILE* pFile);
	void Load(FILE* pFile);

	virtual void render(HDC _dc) override;
public:
	CCameraWall();
	CCameraWall(const CWall& _other);
	~CCameraWall();
};
