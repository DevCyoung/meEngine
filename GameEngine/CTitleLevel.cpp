#include "pch.h"
#include "CTitleLevel.h"
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"
#include "CCollisionManager.h"
#include "CKeyManager.h"
#include "CCamera.h"
#include "CLevelManager.h"
#include "CPlatform.h"


CTitleLevel::CTitleLevel()
{

}

CTitleLevel::~CTitleLevel()
{

}

void CTitleLevel::init()
{

	/*CGameObject* platform = new CPlatform();
	platform->SetPos(Vector2(500.f, 250.f));
	platform->SetScale(Vector2(10.f, 100.f));
	this->AddObject(platform, LAYER::PLATFORM);*/


	CGameObject* Monster = new CMonster();
	Monster->SetPos(Vector2(50.f, 50.f));
	Monster->SetScale(Vector2(100.f, 100.f));
	this->AddObject(Monster, LAYER::BACKGROUND);
		
	CGameObject* player = new CPlayer();
	player->SetPos(Vector2(50.f, 50.f));
	player->SetScale(Vector2(10000000.f, 10000000.f));
	this->AddObject(player, LAYER::PLAYER);



	/*GETINSTANCE(CCamera)->SetLook(Vector2(-2368.38f, -1436.f));
	player->SetPos(Vector2(-2575.16f, -1300.53f));
	platform->SetPos(Vector2(-2575.16f, -1225.53f));*/


	/*CGameObject* monster = new CMonster();
	monster->SetPos(Vector2(500.f, 100.f));
	monster->SetScale(Vector2(100.f, 100.f));
	this->AddObject(monster, LAYER::MONSTER);*/

	/*CGameObject* platform = new CPlatform();
	platform->SetPos(Vector2(500.f, 500.f));
	this->AddObject(platform, LAYER::PLATFORM);

	CCollisionManager* pColMgr = GETINSTANCE(CCollisionManager);
	pColMgr->LayerRegister(LAYER::PLAYER, LAYER::MONSTER);
	pColMgr->LayerRegister(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);
	*/

	GETINSTANCE(CCollisionManager)->LayerRegister(LAYER::PLAYER, LAYER::PLATFORM);

}

void CTitleLevel::tick()
{
	CLevel::tick();

	if (IS_INPUT_TAB(KEY::SPACE))
	{

	}

	if (IS_INPUT_TAB(KEY::ENTER))
	{
		//CCamera::GetInst()->FadeOut(1.f);
		//CCamera::GetInst()->FadeIn(1.f);	
		//CCamera::GetInst()->CameraShake(15.f, 600.f, 0.3f);

		//ChangeLevel(LEVEL_TYPE::STAGE_01);

		CLevelManager::LoadLevel(LEVEL_TYPE::EDITOR);
	}

	if (IS_INPUT_TAB(KEY::RBTN))
	{
		//CForce* pForce = new CForce;
		//pForce->SetLifeTime(1.5f);
		//pForce->SetForceScale(200.f);
		//pForce->SetForceRadius(500.f);

		//Vec2 vMousePos = MOUSE_POS;
		//vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
		//Instantiate(pForce, vMousePos, LAYER::FORCE);		
	}

	//if (IS_INPUT_TAB(KEY::LBTN))
	//{
	//	CPlatform* pPlatform = new CPlatform;

	//	Vector2 vMousePos = GETINSTANCE(CKeyManager)->GetMousePos();
	//	vMousePos = GETINSTANCE(CCamera)->GetRealPos(vMousePos);


	//	//Gameobject static 으로 변경할것
	//	pPlatform->Instantiate(pPlatform, vMousePos, LAYER::PLATFORM);
	//}
	
}

void CTitleLevel::Enter()
{
	this->init();
}

void CTitleLevel::Exit()
{
	this->DeleteAllObject();
}