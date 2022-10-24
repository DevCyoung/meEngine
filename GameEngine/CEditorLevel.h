#pragma once
#include "CLevel.h"


//에디터모드
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



    std::vector<CLineCollider*> m_vecLineCol;

public:
    void Update();
public:
    void UpdateTile();
    void UpdateAnimation();
    void UpdateObject();
    void UpdateLineCollider();

public:
    void CreateUI();

public:
    // CLevel을(를) 통해 상속됨
    virtual void init() override;
    virtual void tick() override;
    //virtual void render(HDC _dc) override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    void SaveTIle();
    void LoadTIle();
    void SaveLineCollider();
    void LoadLineColldier();

    //LineCollider Edit
public:
    CLineCollider* m_preVMouseCol;
    void LineMouseEvent(CLineCollider* _other, LINECOL_MODE _mode);
    void CreateLineMode();

    //mouseEvent
public:
    void MouseStayEvent(CLineCollider* _other);
    void MouseEnterEvent(CLineCollider* _other);
    void MouseExitEvent(CLineCollider* _other);



public:
    CEditorLevel();
    ~CEditorLevel();

};

