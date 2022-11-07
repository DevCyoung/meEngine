#pragma once
#include "CGameObject.h"

class CRockmanObj;
class CLevel;


struct tMonster
{
	MONSETER_TYPE		m_sponType;
	MONSTER_STATE		m_monstreState;

};



class CObjectEdit :
    public CGameObject
{

private:
	//BoxCollide Mode
	Vector2				m_targetPos;
	CCollider*			m_detectObj;
	CRockmanObj*		m_curSelectObj;
	MOUSE_MODE			m_mouseState;
	MONSETER_TYPE		m_sponType;
	MONSTER_STATE		m_monstreState;

public:
	void Update();


private:
	void RegisterObject(CRockmanObj* obj);
public:
	void CreateUI(CLevel* level);
	
	void SelectGameObject(CRockmanObj* obj);

#pragma region VIRTUAL
	virtual void tick()				override;
	virtual void render(HDC _dc)	override;

	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

public:
	void Save(FILE* pFile);
	void Load(FILE* pFile);
#pragma endregion

	

	CLONE(CObjectEdit);

public:
	CObjectEdit();
	CObjectEdit(const CObjectEdit& _other);
	~CObjectEdit();
};

