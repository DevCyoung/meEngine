#pragma once
class CCollider;

union CollisionID
{
	struct
	{
		UINT LeftID;
		UINT RightID;
	};
	UINT_PTR id;
};

class CCollisionManager
{
	SINGLETON(CCollisionManager);

private:
	//16 * 16��Ʈ��Ʈ����
	WORD					m_matrix[(UINT)LAYER::END];
	map<UINT_PTR, BOOL>		m_mapPrevInfo;										//���������ӿ� ���浹ü�� �浹����

public:
	void LayerRegister(LAYER _left, LAYER _right);
	void Clear() { memset(m_matrix, sizeof(WORD), (UINT)LAYER::END); }

	bool					m_isDraw;
public:
	void SetDrawCollide(bool b) { m_isDraw= b; }
	bool GetDrawCollide() { return m_isDraw; }

public:
	void tick();
	

private:
	void CollisionBtwLayer(LAYER _left, LAYER _right);
	BOOL CollisionBtwCollider(const CCollider* _pleft, const CCollider* _pright);

};

