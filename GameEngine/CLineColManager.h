#pragma once

class CLineCollider;
class CEditorLevel;
class CMap;
class CRaycast;

union CLineColliderID
{
	struct
	{
		UINT LeftID;
		UINT RightID;
	};
	UINT_PTR id;
};


class CLineColManager
{
	SINGLETON(CLineColManager);

private:
	CMap*						m_curMap;
	map<UINT_PTR, BOOL>			m_mapPrevInfo;										//이전프레임에 두충돌체의 충돌여부

	vector<CLineCollider*>		m_veclineCol[(UINT)LINELAYER::END];
	vector<tFixedEvent>			m_vecFixedEvent;

	//16 * 16비트매트릭스
	WORD						m_matrix[(UINT)LINELAYER::END];


public:
	void LayerRegister(LINELAYER _left, LINELAYER _right);
	void Clear() { memset(m_matrix, sizeof(WORD), (UINT)LINELAYER::END); }

public:
	void tick();
	void fixed_tick();
	void render(HDC _dc	);

private:
	void CollisionBtwLayer(LINELAYER _left, LINELAYER _right);
	BOOL CollisionBtwCollider( CLineCollider* _pleft,  CLineCollider* _pright);

public:
	CLineCollider*	CreateLine(Vector2 p1, Vector2 p2, LINELAYER l);
	CLineCollider*	CreateRay(Vector2 point, Vector2 dir, Vector2 offset, float distance, LINELAYER _layer);
	void			CreateRaycast(CRaycast& ray, Vector2 vOffset, Vector2 vhdist);

public:
	void AddFixedTick(DELEGATE func, CEntity* instance);
	void ClearFixedTick() { m_vecFixedEvent.clear(); }

public:
	void RemoveLine(CLineCollider* _line);
	void DeletCollider();



private:
	void Save(FILE* _pFile);
	void Load(FILE* _pFile);

	friend CEditorLevel;
};

