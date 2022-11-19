#include "pch.h"
#include "CDumyLevel.h"
#include "CLevelManager.h"
#include "CRockmanManager.h"

CDumyLevel::CDumyLevel()
{
}

CDumyLevel::~CDumyLevel()
{
}


void CDumyLevel::init()
{

}

void CDumyLevel::tick()
{

}

void CDumyLevel::Enter()
{
	LEVEL_TYPE ltype =  GETINSTANCE(CRockmanManager)->m_nextLevel;
	GETINSTANCE(CLevelManager)->LoadLevel(ltype);	
}

void CDumyLevel::Exit()
{

}

