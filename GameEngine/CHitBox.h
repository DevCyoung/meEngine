#pragma once

#include "CRockmanObj.h"
#include "CCollider.h"
#include "CAnimation.h"

class CHitBox :
    public CRockmanObj
{
public:
	CRockmanObj* _pOwner;
	CAnimator* _pOwnerAnim;
	LAYER		_tartget;
	bool		_isOn;

	int				_prevIdx;
	CAnimation*		_prevAnim;


public:
	virtual void tick() override;
	virtual void render(HDC _dc) override;

	virtual void OnTriggerExit(CCollider* _pOther) override;
	virtual void OnTriggerEnter(CCollider* _pOther) override;


	void SetHitBox(bool b);
	void SetHitScale(tAnimFrm frm);
	void SetTartgetLayer(LAYER layer);
	void SetOwner(CRockmanObj* owner);
	

public:
	CHitBox();	
	~CHitBox();
};

