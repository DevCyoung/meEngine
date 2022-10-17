#pragma once
#include "CEntity.h"

//�����Ŵ����� �پ��� ������ ��������Ž̴�.
//������ �������� ������ ������Ʈ���� ����������̴�.


// �����͸� �ʿ��ϱ⶧���� ��¥ �ʿ��Ѱ͸������´�.
// ��ȯ���� ��������� �����ؾ��Ѵ�. �����Ͻð��� �þ��.
// ������Ͽ��� �ٸ� ����� �����ϴ°��� �����ؾ��Ѵ�.
// �̷����ִ�!
// LNK������ ��ŷ������
// ���漱�𿡼� ������Ÿ������
class CGameObject;

class CLevel :
    public CEntity
{

    //CObj �� ��ӹ޴� �پ��� Ŭ�������� CGameObject�� ��ĳ���� �Ҽ��ִ�.(�����ͺ�����) ��������Ʈ���� �θ���� ����ų���ִ� ������Ÿ��
    //�������� �����ϸ� ������Ʈ ������Ÿ������~
    //��� ������Ʈ�� ���δ� ����� ���´�.
    vector<CGameObject*>   m_arrLayer[(UINT)LAYER::END];

    UINT            m_iTileXCount;
    UINT            m_iTileYCount;

public:
    UINT GetTIleXCount() { return m_iTileXCount; }
    UINT GetTIleYCount() { return m_iTileYCount; }
    

public:
    //�ڽ��̸��� �������̵� ������ �������̵� �Լ���ȣ���� ���ߴٸ� �θ���
    // �� å���� ���������ְԸ���/
    virtual void init() = 0; //�߻�Ŭ������ �ǹ��� �ڽ��� ������ ������ ������
    virtual void tick();
    virtual void final_tick();
    virtual void render(HDC _dc);

    virtual void Enter() = 0;   // ������ ������ �� ȣ�� ��
    virtual void Exit() = 0;    // ������ ��� �� ȣ�� ��

public:
    //_layer is collsion type
    void AddObject(CGameObject* _gameObject, LAYER _layer) { m_arrLayer[(UINT)_layer].push_back(_gameObject); }
    const vector<CGameObject*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; } //���𰡸� ��ȯ�Ҷ� �Ͻ������� ���������. ����̸ſ���
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

