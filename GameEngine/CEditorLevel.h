#pragma once
#include "CLevel.h"
class CMap;

//�����͸��
enum class EDITOR_MODE
{
    TILE,
    ANIMATION,
    OBJECT,
    LINECOLLIDER,
    NONE
};

enum class LINECOL_MODE
{
    ADD,
    REMOVE,
    NONE,
};

enum class LINECOLMOUSE_MODE
{
    ONEDOWN,
    TWODOWN,
    NONE,
};


class CLineCollider;

class CEditorLevel :
    public CLevel
{

public:
    HMENU           m_hMenu;
    EDITOR_MODE     m_eMode;
    



public:
    void Update();
public:
    void CreateTileMode();
    void UpdateAnimation();
    void UpdateObject();
    void UpdateLineCollider();

public:
    void CreateUI();

public:
    // CLevel��(��) ���� ��ӵ�
    virtual void init() override;
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    void SaveTIle();
    void LoadTIle();

    void SaveLineCollider();
    void LoadLineCollider();

    //LineCollider Edit
public:
    CLineCollider* m_lineColPreMouse;
    CGameObject*   m_objCurmap;
    CLineCollider* lineCol;
    CLineCollider* MouseX;
    CLineCollider* MouseY;
    LINECOLMOUSE_MODE m_LineMosueMode;
    CMap* m_backGround;

    float size;
    void LineMouseEvent(CLineCollider* _other, LINECOL_MODE _mode);
    void CreateLineMode();
    void CreateLineUI();
    void AddMouseLineollider();


    //void InitLine();
    void StartMapEditMode();
    void CreateMouseCol();

    //mouseEvent
public:
    void MouseStayEvent(CLineCollider* _other);
    void MouseEnterEvent(CLineCollider* _other);
    void MouseExitEvent(CLineCollider* _other);
    //LineCol


public:
    CEditorLevel();
    ~CEditorLevel();

};

