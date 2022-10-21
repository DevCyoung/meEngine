#include "pch.h"
#include "CCollisionLevel.h"
#include "CLineColManager.h"
#include "CLineCollider.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CCamera.h"

CLineCollider* collider1;
CLineCollider* collider2;
CLineCollider* collider3;

CCollisionLevel::CCollisionLevel()
{
	
}

CCollisionLevel::~CCollisionLevel()
{

}



void CCollisionLevel::init()
{
	collider1 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(25.f, 75.f), Vector2(75.f, 75.f), LAYER::PLAYER);
	collider3 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(50.f, 50.f), Vector2(50, 100.f), LAYER::PLAYER);
	
	tColliEvent eventCol = {};

	eventCol.func = (DELEGATECol)&CCollisionLevel::TestEventEnter;
	eventCol.instance = collider1;
	collider1->SetOnTriggerEnterEvent(eventCol);
	collider3->SetOnTriggerEnterEvent(eventCol);
	eventCol.func = (DELEGATECol)&CCollisionLevel::TestEventExit;
	eventCol.instance = collider1;
	collider1->SetOnTriggerExitEvent(eventCol);
	collider3->SetOnTriggerExitEvent(eventCol);
	


	
	

	



	//GETINSTANCE(CCamera)->SetLook(Vector2(50.f, 50.f));


	collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(30.f, 30.f), Vector2(200.f, 150.f), LAYER::MONSTER);

	collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(80.f, 80.f), Vector2(150.f, 80.f), LAYER::MONSTER);

	collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(200.f, 150.f), Vector2(350, 150.f), LAYER::MONSTER);

	collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(350, 150.f), Vector2(520, 30.f), LAYER::MONSTER);

	for (size_t i = 0; i < 1; i++)
	{
		collider2 = GETINSTANCE(CLineColManager)->CreateLine(Vector2(300, 300.f), Vector2(300, 500.f), LAYER::MONSTER);
	}
	



	GETINSTANCE(CLineColManager)->LayerRegister(LAYER::PLAYER, LAYER::MONSTER);
}

void CCollisionLevel::tick()
{
	CLevel::tick();

	Vector2 p1 = collider1->GetP1();
	Vector2 p2 = collider1->GetP2();

	Vector2 p3 = collider3->GetP1();
	Vector2 p4 = collider3->GetP2();

	if (IS_INPUT_PRESSED(KEY::RIGHT))
	{
		p1.x += 100 * DELTATIME;
		p2.x += 100 * DELTATIME;
		p3.x += 100 * DELTATIME;
		p4.x += 100 * DELTATIME;

	}
	if (IS_INPUT_PRESSED(KEY::LEFT))
	{
		p1.x -= 100 * DELTATIME;
		p2.x -= 100 * DELTATIME;
		p3.x -= 100 * DELTATIME;
		p4.x -= 100 * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::UP))
	{
		p1.y -= 100 * DELTATIME;
		p2.y -= 100 * DELTATIME;
		p3.y -= 100 * DELTATIME;
		p4.y -= 100 * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::DOWN))
	{
		p1.y += 100 * DELTATIME;
		p2.y += 100 * DELTATIME;
		p3.y += 100 * DELTATIME;
		p4.y += 100 * DELTATIME;
	}
	collider1->SetP1(p1);
	collider1->SetP2(p2);

	collider3->SetP1(p3);
	collider3->SetP2(p4);
}

void CCollisionLevel::render(HDC _dc)
{
	GETINSTANCE(CLineColManager)->render(_dc);
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
}

void CCollisionLevel::TestEventExit(CLineCollider* _lineCol)
{	
	//MessageBox(nullptr, L"Exit", L"Exit", MB_OK);
}
