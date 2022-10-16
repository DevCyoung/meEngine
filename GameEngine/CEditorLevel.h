#pragma once
#include "CLevel.h"


//에디터모드
enum class EDITOR_MODE
{
    TILE,
    ANIMATION,
    OBJECT,

    NONE
};


class CEditorLevel :
    public CLevel
{

public:
    HMENU           m_hMenu;
    EDITOR_MODE     m_eMode;

public:
    void Update();
    void UpdateTile();
    void UpdateAnimation();
    void UpdateObject();

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

public:
    CEditorLevel();
    ~CEditorLevel();

};

