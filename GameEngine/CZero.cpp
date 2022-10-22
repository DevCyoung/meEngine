#include "pch.h"
#include "CZero.h"
#include "CLineColManager.h"
#include "CLineCollider.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CCamera.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResourceManager.h"

CTexture* mm_pTexuture = nullptr;
CZero::CZero()
	:m_downColLeft(nullptr)
	, m_landDir{}
	, m_downColRight{}
	, m_rayDistance(0.f)
	, m_bisLand(false)
	, m_curLand(nullptr)
	, m_downLandCheck(nullptr)
{
	m_rayDistance = 70.f;

	m_downColLeft = GETINSTANCE(CLineColManager)->CreateLine(Vector2(0.f, 0.f), Vector2(0.f, m_rayDistance), LAYER::PLAYER);
	m_downColRight = GETINSTANCE(CLineColManager)->CreateLine(Vector2(0.f, 0.f), Vector2(0.f, m_rayDistance), LAYER::PLAYER);
	m_downLandCheck = GETINSTANCE(CLineColManager)->CreateLine(Vector2(0.f, 0.f), Vector2(0.f, m_rayDistance), LAYER::PLAYER);


	tColliEvent eventCol = {};
	eventCol.func = (DELEGATECol)&CZero::DownHitStay;
	eventCol.instance = this;
	m_downColLeft->SetOnTriggerStayEvent(eventCol);
	/*m_downColRight->SetOnTriggerStayEvent(eventCol);
	eventCol = {};
	eventCol.func = (DELEGATECol)&CZero::DownHitEnter;
	eventCol.instance = this;
	m_downColLeft->SetOnTriggerEnterEvent(eventCol);
	m_downColRight->SetOnTriggerEnterEvent(eventCol);*/


	//mm_pTexuture = GETINSTANCE(CResourceManager)->LoadTexture(L"ZZ", L"\\texture\\charactor\\atlas_zero3.bmp");

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\zero\\attack.anim");
	GetAnimator()->Play(L"ATTACK", true);
}

CZero::CZero(const CRockmanObj& _other)
	:m_downColLeft(nullptr)
{
}

CZero::~CZero()
{
}


void CZero::tick()
{
	CRockmanObj::tick();
	float fRayDist = 75.f;

	Vector2 pos = this->GetPos();
	if (IS_INPUT_PRESSED(KEY::LEFT))
	{
		this->SetFilpX(false);
		pos.x -= 100 * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::RIGHT))
	{
		this->SetFilpX(true);
		pos.x += 100 * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::UP))
	{
		pos.y -= 100 * DELTATIME;
	}
	if (IS_INPUT_PRESSED(KEY::DOWN))
	{
		pos.y += 100 * DELTATIME;
	}




	this->SetPos(pos);

	/*pos.x = GetPos().x - 25.f;
	m_downColRight->TranslateSetPos(pos);*/

	//pos.x = GetPos().x + 25.f;
	m_downColLeft->TranslateSetPos(pos);

	//GETINSTANCE(CCamera)->SetLook(Vector2(pos.x / 2.f, pos.y / 2.f));
}

void CZero::render(HDC _dc)
{
	CRockmanObj::render(_dc);
	Vector2 pos = GETINSTANCE(CCamera)->GetRenderPos(GetPos());
	//GETINSTANCE(CCamera)->SetLook(pos);
	/*Rectangle(_dc, pos.x - 80.f, pos.y - 80.f, pos.x + 80.f, pos.y + 80.f);
	CRockmanObj::render(_dc);*/
	//Rectangle(_dc, pos.x - 2, pos.y - 2 , pos.x + 2, pos.y + 2);
	// 

	pos = this->GetPos();


	pos = GETINSTANCE(CCamera)->GetRenderPos(pos);

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = 1;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * 1);
	tBlend.SourceConstantAlpha = 255 * 1;

	//AlphaBlend
	//(
	//	_dc,
	//	pos.x - mm_pTexuture->Width() / 2,
	//	pos.y - mm_pTexuture->Height() / 2,
	//	mm_pTexuture->Width(),
	//	mm_pTexuture->Height(),
	//	mm_pTexuture->GetDC(),
	//	0,
	//	0,
	//	mm_pTexuture->Width(),
	//	mm_pTexuture->Height(),
	//	tBlend
	//);

	//BitBlt
	//(
	//	_dc,
	//	pos.x - mm_pTexuture->Width() / 2,
	//	pos.y - mm_pTexuture->Height() / 2,
	//	mm_pTexuture->Width(),
	//	mm_pTexuture->Height(),
	//	mm_pTexuture->GetDC(),
	//	0,
	//	0,
	//	SRCCOPY
	//);
}


