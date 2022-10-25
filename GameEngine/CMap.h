#pragma once
#include "CGameObject.h"

class CLineCollider;
class CTexture;
class CEditorLevel;

//�ʵ� ƽ�� ���ƾ��Ѵ�.
class CMap :
    public CGameObject
{
    CTexture*                   m_mapAtlas;



public:
    void init();



public:
    virtual void tick();
    virtual void render(HDC _dc);


    CLONE(CMap)
public:
    CMap();
  //  CMap(const CGameObject& _other);
    ~CMap();


    friend CEditorLevel;
};