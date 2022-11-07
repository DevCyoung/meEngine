#pragma once
#include "CGameObject.h"

class CLineCollider;
class CTexture;
class CEditorLevel;

//∏ µµ ∆Ω¿Ã µπæ∆æﬂ«—¥Ÿ.
class CMap :
    public CGameObject
{
public:
    CTexture*                   m_mapAtlas;
    vector<Vector2>		        m_cameraPos;
    vector<Vector2>		        m_playerPos;




public:
    void init();



public:
    virtual void tick();
    virtual void render(HDC _dc);

    CTexture* GetAtlas() { return m_mapAtlas; }
    void SetAtlas(CTexture* tex){ m_mapAtlas = tex; }





    CLONE(CMap)
public:
    CMap();
  //  CMap(const CGameObject& _other);
    ~CMap();


    friend CEditorLevel;
};