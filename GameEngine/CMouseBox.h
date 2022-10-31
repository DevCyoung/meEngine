#pragma
#include "CGameObject.h"

class CCollider;
class CWall;
class CLine;

enum class COLIDE_EIDT_MODE
{
	NONE,
	LINE,
	BOX,
	END,
};

class CMouseBox :
	public CGameObject
{
public:

	MOUSE_MODE          m_mouseMode;
	Vector2             m_leftTop;
	Vector2             m_rightbottom;
	Vector2				m_curGizmoPoint;


	//BoxCollide Mode
	CCollider*			m_detectBox;
	CWall*				m_curColWall;

	//LineCollide Mode
	CLineCollider*		m_detectColLine;
	CLine*				m_curColLine;
	CLine*				m_mouseX;
	CLine*				m_mouseY;

	COLIDE_EIDT_MODE	m_editMode;
	virtual void tick() override;
	//virtual void fixed_tick() override;
	virtual void render(HDC _dc) override;

	virtual void OnTriggerEnter(CCollider* _pOhter);
	virtual void OnTriggerStay(CCollider* _pOhter);
	virtual void OnTriggerExit(CCollider* _pOhter);

	void CreateBoxMode();
	void CreateLineMode();

	void MouseStayEvent(CLineCollider* _other);
	void MouseEnterEvent(CLineCollider* _other);
	void MouseExitEvent(CLineCollider* _other);

	CLONE(CMouseBox);

public:
	CMouseBox();
	CMouseBox(const CMouseBox& _other);
	~CMouseBox();
};
