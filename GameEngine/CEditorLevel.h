#pragma once
#include "CLevel.h"
class CMap;



class CLineCollider;
class CMouseBox;
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

    MOUSE_MODE          m_LineMosueMode;
    CGameObject*        m_objCurmap;
    CMap*               m_backGround;
    WALLDIR             m_wallDir;

    //Editing Collider
    CLineCollider*  m_MouseX;
    CLineCollider*  m_MouseY;
    CMouseBox*      m_MouseBox;



    float size;
    void LineMouseEvent(CLineCollider* _other, LINECOL_MODE _mode);
    void CreateLineMode();
    void CreateLineUI();
    void DeleteMouse();

    //void InitLine();
    void StartMapEditMode();


    void AddMouseLineCollider();
    void AddMouseBoxCollider();

public:
   
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

