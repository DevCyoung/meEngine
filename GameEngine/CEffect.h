#pragma once
#include "CRockmanObj.h"

enum class EFFECTPLAY_TYPE
{
	NONE,
	ONESHOOT,
	FOLLOW
};

class CEffect :
    public CRockmanObj
{

protected:
	CRockmanObj*			m_target;
	
	Vector2					m_offset;
	Vector2					m_position;
	bool					m_isUsing;

	EFFECTPLAY_TYPE			m_playType;


public:
	CRockmanObj* m_owner;

public:
	virtual void tick() override;	
	virtual void render(HDC _dc) override;
	virtual void OnShootPlay(Vector2 pos, bool isFlipX);

	void LoadAnimation(const std::wstring relativePath);

	CLONE(CRockmanObj);

public:
	CEffect();
	CEffect(const CEffect& _other);
	~CEffect();

};

