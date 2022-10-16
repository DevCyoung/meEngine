#include "pch.h"
#include "CStartLevel.h"
#include "CKeyManager.h"
#include "CLevelManager.h"


//testgit

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}


void CStartLevel::init()
{

}

void CStartLevel::tick()
{
	CLevel::tick();

	if (IS_INPUT_TAB(KEY::ENTER))
	{
		CLevelManager::LoadLevel(LEVEL_TYPE::TITLE);
	}
}

void CStartLevel::Enter()
{
	this->init();
}

void CStartLevel::Exit()
{
	this->DeleteAllObject();
}

