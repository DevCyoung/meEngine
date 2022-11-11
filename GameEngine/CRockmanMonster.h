#pragma once
#include "CRockmanObj.h"



class CRockmanMonster :
    public CRockmanObj
{

public:


public:
	virtual void tick() override;
	virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	//box 
	virtual void OnTriggerEnter(CCollider* _pOhter) override;
	virtual void OnTriggerStay(CCollider* _pOhter) override;
	virtual void OnTriggerExit(CCollider* _pOhter) override;


public:
	void Save(FILE *pFile);
	void Load(FILE* pFile);
	CLONE(CRockmanObj);

public:
	CRockmanMonster();
	CRockmanMonster(const CRockmanMonster& _other);
	~CRockmanMonster();

};

