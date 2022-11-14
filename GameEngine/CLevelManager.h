#pragma once

#include "CLevel.h"

class CZero;

class CLevelManager
{
	SINGLETON(CLevelManager)

private:
	CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel* m_pCurLevel;

public:
	void init();
	void tick();
	void fixed_tick();
	void render(HDC m_hDC);



public:
	static void LoadLevel(LEVEL_TYPE type);
	CLevel* GetCurLevel() { return m_pCurLevel; }
	CLevel* GetEditorLevel() { return m_arrLevel[(UINT)LEVEL_TYPE::EDITOR]; }
	CZero*  GetPlayerObject();

private:
	void LoadLevelEvent(LEVEL_TYPE type);

	

	friend class CEventManager;
};

