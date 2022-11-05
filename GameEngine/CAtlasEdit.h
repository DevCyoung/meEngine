#pragma
#include "CGameObject.h"

class CRockmanObj;
class CLevel;
class CTexture;
class CMap;


class CAtlasEdit :
	public CGameObject
{

private:
	//BoxCollide Mode
	/*Vector2				m_targetPos;
	CCollider*			m_detectObj;
	CRockmanObj*		m_curSelectObj;
	MOUSE_MODE			m_mouseState;*/
	
	CMap*				m_backGround;

public:
	void Update();
	void DrawRect(Vector2 size, PEN_TYPE pen, vector<Vector2>& vector, HDC _dc);

	
	void Save(FILE* pFile);
	void Load(FILE* pFile);

#pragma region VIRTUAL
	virtual void tick()				override;
	virtual void render(HDC _dc)	override;
#pragma endregion



	CLONE(CAtlasEdit);

public:
	CAtlasEdit();
	CAtlasEdit(const CAtlasEdit& _other);
	~CAtlasEdit();
};

