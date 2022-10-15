#pragma once
#include "CGameObject.h"
class CTexture;

class CTile :
    public CGameObject
{

private:
    CTexture* m_pAtlas;
    int             m_iImgIdx;

public:
    virtual void tick();
    virtual void render(HDC _dc);


public:
    void SetAtlas(CTexture* _pAtlas) { m_pAtlas = _pAtlas; }
    void SetImgIdx(int _imgidx);
    void AddImgIdx();


public:
    void Save(FILE* _pFile);
    void Load(FILE* _pFile);

public:
    CLONE(CTile);

public :
    CTile();
    ~CTile();
};


