#pragma once
#include "CHitBox.h"
class CMonsterHitBox :
    public CHitBox
{
public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;

	virtual void OnTriggerExit(CCollider* _pOther) override;
	virtual void OnTriggerEnter(CCollider* _pOther) override;


public:
	CMonsterHitBox();
	~CMonsterHitBox();
};

