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
	//16 * 16비트매트릭스
	WORD					m_matrix[(UINT)LAYER::END];
	map<UINT_PTR, BOOL>		m_mapPrevInfo;										//이전프레임에 두충돌체의 충돌여부

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

