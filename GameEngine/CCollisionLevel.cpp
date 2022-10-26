#include "pch.h"
#include "CCollisionLevel.h"
#include "CLineColManager.h"
#include "CLineCollider.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CCamera.h"
#include "CZero.h"

CLineCollider* collider1;
CLineCollider* collider2;
CLineCollider* collider3;

CCollisionLevel::CCollisionLevel()
{
	
}

CCollisionLevel::~CCollisionLevel()
{

}

CLineCollider* collider = nullptr;

void CCollisionLevel::init()
{
	collider1 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(25.f, 75.f), Vector2(75.f, 75.f), LINELAYER::PLAYER);
	collider3 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(50.f, 50.f), Vector2(50, 100.f), LINELAYER::PLAYER);
	
	tColliEvent eventCol = {};

	//eventCol.func = (DELEGATECOL)&CCollisionLevel::TestEventEnter;
	//eventCol.instance = collider1;
	//collider1->SetOnTriggerEnterEvent(eventCol);
	//collider3->SetOnTriggerEnterEvent(eventCol);
	//eventCol.func = (DELEGATECOL)&CCollisionLevel::TestEventExit;
	//eventCol.instance = collider1;
	//collider1->SetOnTriggerExitEvent(eventCol);
	//collider3->SetOnTriggerExitEvent(eventCol);

	//eventCol.func = (DELEGATECOL)&CCollisionLevel::TestEventOverlap;
	//eventCol.instance = collider3;
	//collider3->SetOnTriggerStayEvent(eventCol);


	//GETINSTANCE(CCamera)->SetLook(Vector2(50.f, 50.f));


	//collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(30.f, 30.f), Vector2(200.f, 150.f), LAYER::MONSTER);

	//collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(80.f, 80.f), Vector2(150.f, 80.f), LAYER::MONSTER);

	//collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(200.f, 150.f), Vector2(350, 150.f), LAYER::MONSTER);

	//collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(350, 150.f), Vector2(520, 30.f), LAYER::MONSTER);

	for (size_t i = 0; i < 1; i++)
	{
		//collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(300, 300.f), Vector2(300, 500.f), LAYER::MONSTER);
	}
	
	for (size_t i = 0; i < 1; i++)
	{
		CZero* zero = new CZero();
		zero->SetPos(Vector2(150.f, 50.f));
		this->AddObject(zero, LAYER::PLAYER);
	}

	//GETINSTANCE(CLineColManager)->LayerRegister(LINELAYER::PLAYER, LINELAYER::MONSTER);
}

void CCollisionLevel::tick()
{
	CLevel::tick();

}

void CCollisionLevel::render(HDC _dc)
{
	CLevel::render(_dc);
	//GETINSTANCE(CLineColManager)->render(_dc);
}

void CCollisionLevel::Enter()
{
	this->init();
}



void CCollisionLevel::Exit()
{
	this->DeleteAllObject();
}

void CCollisionLevel::TestEventEnter(CLineCollider* _lineCol)
{
	//MessageBox(nullptr, L"Enter", L"Enter", MB_OK);
	collider = _lineCol;
}

void CCollisionLevel::TestEventExit(CLineCollider* _lineCol)
{
	collider = nullptr;
}

void CCollisionLevel::TestEventOverlap(CLineCollider* _lineCol)
{
	if (collider3 == nullptr)
		return;
	//살짝남겨두고붙인다.
	//현재위치
	Vector2 inter = _lineCol->GetIntersction();
	Vector2 p1 = collider3->GetP1();
	Vector2 p2 = collider3->GetP2();

	p1.y = inter.y + 50;
	p2.y = inter.y + 50;

	collider3->SetP1(p1);
	collider3->SetP1(p2);
	//collider = _lineCol;
}

