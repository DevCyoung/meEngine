#pragma once

class CLineCollider;

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
	vector<CLineCollider*>		m_veclineCol[(UINT)LAYER::END];
	//16 * 16��Ʈ��Ʈ����
	WORD						m_matrix[(UINT)LAYER::END];
	map<UINT_PTR, BOOL>			m_mapPrevInfo;										//���������ӿ� ���浹ü�� �浹����


public:
	void LayerRegister(LAYER _left, LAYER _right);
	void Clear() { memset(m_matrix, sizeof(WORD), (UINT)LAYER::END); }

public:
	void tick();
	void render(HDC _dc	);

private:
	void CollisionBtwLayer(LAYER _left, LAYER _right);
	BOOL CollisionBtwCollider(const CLineCollider* _pleft, const CLineCollider* _pright);

public:
	CLineCollider* CreateLine(Vector2 p1, Vector2 p2, LAYER l);
};

