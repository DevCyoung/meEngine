#pragma once
#include "CEntity.h"

//레벨매니저가 다양한 레벨을 들고있을거싱다.
//각각의 레벨에는 수많은 오브젝트들이 들어있을것이다.


// 포인터만 필요하기때문에 진짜 필요한것만가져온다.
// 순환참조 헤더구조를 조심해야한다. 컴파일시간도 늘어난다.
// 헤더파일에서 다른 헤더를 참조하는것을 지양해야한다.
// 이런게있다!
// LNK에러는 링킹에러다
// 전방선언에선 포인터타입을씀
class CGameObject;

class CLevel :
    public CEntity
{

    //CObj 를 상속받는 다양한 클래스들을 CGameObject로 업캐스팅 할수있다.(포인터변수로) 모든오브젝트들의 부모까지 가르킬수있는 포인터타입
    //다형성을 생각하면 오브젝트 포인터타입으로~
    //모든 오브젝트는 전부다 여기로 들어온다.
    vector<CGameObject*>   m_arrLayer[(UINT)LAYER::END];

    UINT            m_iTileXCount;
    UINT            m_iTileYCount;

public:
    UINT GetTIleXCount() { return m_iTileXCount; }
    UINT GetTIleYCount() { return m_iTileYCount; }
    

public:
    //자식이만약 오버라이딩 했으면 오버라이딩 함수를호출함 안했다면 부모쪽
    // 즉 책임을 내가질수있게만듬/
    virtual void init() = 0; //추상클래스가 되버림 자식은 무조건 구현을 강제함
    virtual void tick();
    virtual void final_tick();
    virtual void render(HDC _dc);

    virtual void Enter() = 0;   // 레벨에 진입할 때 호출 됨
    virtual void Exit() = 0;    // 레벨을 벗어날 때 호출 됨

public:
    //_layer is collsion type
    void AddObject(CGameObject* _gameObject, LAYER _layer) { m_arrLayer[(UINT)_layer].push_back(_gameObject); }
    const vector<CGameObject*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; } //무언가를 반환할때 일시적으로 만들어진다. 비용이매우비쌈
    void DeleteAllObject();
    void DeleteAllObject(LAYER _eLayer);

    //void DeleteObject(LAYER _eLayer);
    void CreateTile(UINT _X, UINT _Y);

    void SetFocusUI(CGameObject* _pUI);


public:
    CLONE_DEACTIVATE(CLevel);

public:
    CLevel();
    ~CLevel();
};

