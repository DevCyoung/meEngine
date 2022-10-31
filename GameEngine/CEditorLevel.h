#pragma once
#include "CLevel.h"
class CMap;



class CLineCollider;
class CWall;

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
    // CLevel을(를) 통해 상속됨
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

    void SaveBoxCollider();
    void LoadBoxCollider();

    //LineCollider Edit
public:
    CLineCollider*      m_lineColPreMouse;
    CLineCollider*      lineCol;
    CLineCollider*      MouseX;
    CLineCollider*      MouseY;
    MOUSE_MODE          m_LineMosueMode;
    CGameObject*        m_objCurmap;
    CMap*               m_backGround;
    WALLDIR             m_wallDir;



    float size;
    void LineMouseEvent(CLineCollider* _other, LINECOL_MODE _mode);
    void CreateLineMode();
    void CreateLineUI();
    void AddMouseLineollider();
    void DeleteMouse();

    //void InitLine();
    void StartMapEditMode();


public:
    MOUSE_MODE          m_BoxMosueMode;
    Vector2             m_leftTop;
    Vector2             m_bottom;
    CWall*              m_curObj;
    //BoxCollide Edit
    void CreateBoxMode();
    

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

