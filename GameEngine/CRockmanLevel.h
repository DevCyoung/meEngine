#pragma once
#include "CLevel.h"

enum class eLEVELSTATE
{
    NONE,
    FADEENTER,
    FADEEXIT,
    READY,
    ZEROENTER,
};

class CTexture;
class CEditorLevel;
class CZero;
class CTextureAnim;
class CCameraObj;

class CRockmanLevel :
    public CLevel
{

private:
    CEditorLevel*   m_editor;
protected:
    CCameraObj* m_cam;
public:
    CZero* m_zero;

    CTextureAnim* m_textureReadyAnim;
    eLEVELSTATE     m_levelState;
private:
    float               m_delay;
    float               m_exitDelay;
protected:
    LEVEL_TYPE           m_nextLevel;

protected:
    bool            m_isReady;
public:
    // CLevel을(를) 통해 상속됨
    virtual void init() override;
    virtual void tick() override;

    // CLevel을(를) 통해 상속됨
    virtual void Enter() override;
    virtual void Exit() override;


    void LoadMap(const wstring& str);
    void ZeroEnter(UINT pos);
    void ZeroRetrun();

    void   LevelDealy();
    void   NextAread(UINT pos);

    void  NextLevel(LEVEL_TYPE layer);
    void  NextLevel();

public:
    CRockmanLevel();
    ~CRockmanLevel();
};


