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
	if (IS_INPUT_TAB(KEY::N))
	{
		bool b = GETINSTANCE(CCollisionManager)->GetDrawCollide();
		b = !b;
		GETINSTANCE(CCollisionManager)->SetDrawCollide(b);
	}
	if (IS_INPUT_TAB(KEY::M))
	{
		bool b = GETINSTANCE(CLineColManager)->GetDrawCollide();
		b = !b;
		GETINSTANCE(CLineColManager)->SetDrawCollide(b);
	}
}

void CMap::render(HDC _dc)
{
	Vector2 vPos = GetPos();
	vPos = GETINSTANCE(CCamera)->GetRenderPos(vPos);
	CRenderHelper::StretchRender(_dc, this->m_mapAtlas, vPos);

	//CRenderHelper::StretchRender()
}

