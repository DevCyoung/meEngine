#pragma once
#include "pch.h"
#include "CGameObject.h"

class CWall 
	: public CGameObject
{

public:
	/*virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;*/

	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

	void ResizeCollider(Vector2 leftTop, Vector2 bottom);

public:
	CLONE(CWall);

	void Save(FILE* pFile);
	void Load(FILE* pFile);


public:
	CWall();
	CWall(const CWall& _other);
	~CWall();

};

