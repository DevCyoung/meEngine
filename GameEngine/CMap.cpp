#include "pch.h"
#include "CMap.h"
#include "CRenderHelper.h"
#include "CCamera.h"
#include "CKeyManager.h"

#include "CLineColManager.h"
#include "CCollisionManager.h"

CMap::CMap()
	: m_mapAtlas(nullptr)
	, m_cameraPos{}
	, m_playerPos{}
{
	init();
}

CMap::~CMap()
{

}


void CMap::init()
{

}

void CMap::tick()
{
}

void CMap::render(HDC _dc)
{
	Vector2 vPos = GetPos();
	vPos = GETINSTANCE(CCamera)->GetRenderPos(vPos);	
	CRenderHelper::StretchRender(_dc, this->m_mapAtlas, vPos, GetFilpY());

	

	//CRenderHelper::StretchRender()
}

