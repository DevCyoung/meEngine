#include "pch.h"
#include "CGameObject.h"
#include "CEventManager.h"

#include "CCollider.h"
#include "CRigidbody.h"
#include "CAnimator.h"



CGameObject::CGameObject()
	: m_vPos{}
	, m_vScale{}
	, m_bDead(false)
	, m_isFlipX(false)
	, m_isFlipY(false)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidbody(nullptr)
	, m_preFramePos{}
	, m_tag{}
{
}

CGameObject::CGameObject(const CGameObject& _other)
	: CEntity(_other)
	, m_vPos(_other.m_vPos)
	, m_vScale(_other.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidbody(nullptr)
	, m_bDead(false)
	, m_isFlipX(_other.m_isFlipX)
	, m_isFlipY(_other.m_isFlipY)
	, m_preFramePos{}
	, m_tag(_other.m_tag)
{
	if (nullptr != _other.m_pCollider)
	{
		m_pCollider = _other.m_pCollider->Clone();
		m_pCollider->SetOwner(this);
	}

	if (nullptr != _other.m_pAnimator)
	{
		m_pAnimator = _other.m_pAnimator->Clone();
		m_pAnimator->SetOwner(this);
	}

	if (nullptr != _other.m_pRigidbody)
	{
		m_pRigidbody = _other.m_pRigidbody->Clone();
		m_pRigidbody->SetOwner(this);
	}
}
CGameObject::~CGameObject()
{
	if (nullptr != m_pAnimator)
		delete m_pAnimator;
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (nullptr != m_pRigidbody)
		delete m_pRigidbody;
}

//Component tick
void CGameObject::tick()
{

	if (nullptr != m_pRigidbody)
		m_pRigidbody->tick();

	if (nullptr != m_pCollider)
		m_pCollider->tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->tick();

}

void CGameObject::final_tick()
{
	if (nullptr != m_pRigidbody)
		m_pRigidbody->final_tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->final_tick();

	if (nullptr != m_pCollider)
		m_pCollider->final_tick();			//콜라이더 최종위치는 가장마지막에
}

void CGameObject::fixed_tick()
{
	m_preFramePos = GetPos();
}

void CGameObject::render(HDC _dc)
{
	if (nullptr != m_pAnimator)
		m_pAnimator->render(_dc);

	if (nullptr != m_pCollider)
		m_pCollider->render(_dc);

	if (nullptr != m_pRigidbody)
		m_pRigidbody->render(_dc);
}

void CGameObject::CreateCollider()
{
	if (nullptr == m_pCollider)
		m_pCollider = new CCollider(this);
}

void CGameObject::CreateAnimator()
{
	if (nullptr == m_pAnimator)
		m_pAnimator = new CAnimator(this);
}

void CGameObject::CreateRigidbody()
{
	if (nullptr == m_pRigidbody)
		m_pRigidbody = new CRigidbody(this);
}


void CGameObject::Destroy()
{
	if (this->IsDead())
		return;
	tEvent evn = {};
	evn.eType = EVENT_TYPE::DELETE_OBJECT;
	evn.wParam = (DWORD_PTR)this;
	GETINSTANCE(CEventManager)->AddEvent(evn);
}


void CGameObject::Instantiate(CGameObject* _pNewObj, Vector2 _vPos, LAYER _eLayer)
{
	_pNewObj->SetPos(_vPos);
	tEvent _evn = {};
	_evn.eType = EVENT_TYPE::CREATE_OBJECT;
	_evn.wParam = (DWORD_PTR)_pNewObj;
	_evn.lParam = (DWORD_PTR)_eLayer;
	GETINSTANCE(CEventManager)->AddEvent(_evn);
}


void CGameObject::OnTriggerEnter(CCollider* _pOther)
{
}
void CGameObject::OnTriggerStay(CCollider* _pOther)
{
}
void CGameObject::OnTriggerExit(CCollider* _pOther)
{
}


void CGameObject::OnTriggerEnterUp(CCollider* _pOther)
{
}

void CGameObject::OnTriggerEnterDown(CCollider* _pOther)
{
}
void CGameObject::OnTriggerEnterLeft(CCollider* _pOther)
{
}

void CGameObject::OnTriggerEnterRight(CCollider* _pOther)
{
}





void CGameObject::OnTriggerStayUp(CCollider* _pOther)
{
}

void CGameObject::OnTriggerStayDown(CCollider* _pOther)
{
}

void CGameObject::OnTriggerStayLeft(CCollider* _pOther)
{
}

void CGameObject::OnTriggerStayRight(CCollider* _pOther)
{
}




void CGameObject::OnTriggerExitUp(CCollider* _pOther)
{
}

void CGameObject::OnTriggerExitDown(CCollider* _pOther)
{
}

void CGameObject::OnTriggerExitLeft(CCollider* _pOther)
{
}

void CGameObject::OnTriggerExitRight(CCollider* _pOther)
{
}





void CGameObject::Func(CGameObject* _obj, void(CGameObject::* Function)(void))
{	
	((*_obj).*Function)();
}

void CGameObject::Func()
{
}
