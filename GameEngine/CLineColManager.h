#pragma once

class CLineCollider;
class CEditorLevel;
class CMap;

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

	vector<CLineCollider*>		m_veclineCol[(UINT)LAYER::END];
	//16 * 16비트매트릭스
	WORD						m_matrix[(UINT)LAYER::END];


public:
	void LayerRegister(LAYER _left, LAYER _right);
	void Clear() { memset(m_matrix, sizeof(WORD), (UINT)LAYER::END); }

public:
	void tick();
	void render(HDC _dc	);

private:
	void CollisionBtwLayer(LAYER _left, LAYER _right);
	BOOL CollisionBtwCollider( CLineCollider* _pleft,  CLineCollider* _pright);

public:
	CLineCollider* CreateLine(Vector2 p1, Vector2 p2, LAYER l);

private:
	void RemoveLine(CLineCollider* _line);
	void DeletCollider();



private:
	void Save(FILE* _pFile);
	void Load(FILE* _pFile);

	friend CEditorLevel;
};

