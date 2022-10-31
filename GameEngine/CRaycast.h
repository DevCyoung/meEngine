#pragma once
#include "CEntity.h"

class CLineCollider;
class CLineColManager;


class CRaycast :
    public CEntity
{
private:
    float m_hoffset;
    float m_voffset;
    float m_hdist;
    float m_vdist;

    Vector2 vOffset;
    Vector2 vhdist;


    CLineCollider* m_arrRay[(UINT)RAY_TYPE::END];


public:
    void TranslateSetPos(Vector2 pos);

 
    CLineCollider*  GetLineCol(RAY_TYPE TPYE);
    int             GetCollideCnt(RAY_TYPE TYPE);
    float           GetVdist() { return vhdist.y; }
    float           GetHdist() { return vhdist.x; }

public:
    bool    GetDownWallColState();
    bool    GetLeftWallColState();
    bool    GetRightWallColState();
    bool    GetUpWallColState();

    CLONE(CRaycast);

    CRaycast();
    ~CRaycast();

    friend CLineColManager;
};

