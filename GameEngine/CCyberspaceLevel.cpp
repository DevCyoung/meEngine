#include "pch.h"
#include "CCyberspaceLevel.h"
#include "CTextureAnim.h"
#include "CGameObject.h"
#include "CCamera.h"
#include "CEditorLevel.h"
#include "CLevelManager.h"
#include "CKeyManager.h"

#include "CZero.h"
#include "CMapManager.h"
#include "CAnimator.h"
#include "CTextureAnim.h"
#include "CSoundMgr.h"
#include "CSound.h"
#include "CResourceManager.h"

//»èÁ¦
#include "CHPbar.h"
#include "CCyberKujacer.h"

CCyberspaceLevel::CCyberspaceLevel()
{
	
}

CCyberspaceLevel::~CCyberspaceLevel()
{
}

void CCyberspaceLevel::init()
{
	CRockmanLevel::init();
	m_nextLevel = LEVEL_TYPE::CYBERSPACE2;


	//background play
	CSound* sound = GETINSTANCE(CResourceManager)->LoadSound(L"cyberbackground1", L"sound\\cyberspacebackground.wav");
	sound->SetVolume(16.f);
	//GETINSTANCE(CSoundMgr)->RegisterToBGM(sound);
	sound->PlayToBGM(true);
	//sound->Play();


	//test hpbar zerohpbar.bmp
	

}
void CCyberspaceLevel::tick()
{
	CRockmanLevel::tick();



	if (IS_INPUT_TAB(KEY::ENTER))
	{
		//exit
		NextLevel(LEVEL_TYPE::CYBERSPACE2);
		//GETINSTANCE(CLevelManager)->LoadLevel(LEVEL_TYPE::CYBERSPACE2);
	}
	if (m_levelState == eLEVELSTATE::FADEENTER)
	{
		
		//GETINSTANCE(CResourceManager)->FindSound(L"cyberbackground1")->Play();
		
	}
	//if (cyberspacebackground.wav)
}

void CCyberspaceLevel::Enter()
{
	
	CRockmanLevel::Enter();	
	init();
	LoadMap(L"cyber\\cyberspace_Level_1.map");
	GETINSTANCE(CMapManager)->MapCameraSet(0);		
}

void CCyberspaceLevel::Exit()
{
	CRockmanLevel::Exit();
}

