#include "pch.h"
#include "CTextureAnim.h"
#include "CTexture.h"
#include "CRenderHelper.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSound.h"

CTextureAnim::CTextureAnim()
	:m_texture(nullptr)
	, m_state(eTextAnimState::START)
	, m_removeDuration(0.f)
{
	m_texture = GETINSTANCE(CResourceManager)->LoadTexture(L"READY", L"ui\\ready.bmp");

}

CTextureAnim::~CTextureAnim()
{
}


void CTextureAnim::tick()
{
	if (m_state == eTextAnimState::START)
	{
		for (size_t i = 0; i < m_vecTexAnim.size(); i++)
		{
			m_vecTexAnim[i].fDuration += DELTATIME;
		}
	}
	//하나삭제
	if (m_state == eTextAnimState::REMOVE)
	{

		m_removeDuration += DELTATIME;
		if (m_vecTexAnim.size() == 0)
			return;
		m_vecTexAnim.erase(m_vecTexAnim.end() - 1);
	/*	if (m_removeDuration >= 0.00000012f)
		{
		
			m_removeDuration = 0.f;
		}*/

	}
}

void CTextureAnim::render(HDC _dc)
{
	Vector2 pos = GetPos();
	pos = GETINSTANCE(CCamera)->GetLook();
	pos = GETINSTANCE(CCamera)->GetRenderPos(pos);
	for (size_t i = 0; i < m_vecTexAnim.size(); i++)
	{

		if (m_vecTexAnim[i].fDestDuration <= m_vecTexAnim[i].fDuration)
		{
			CRenderHelper::StretchRenderOnePer(_dc, m_texture, m_vecTexAnim[i], pos);
		}
	}
}
#include <algorithm>
#include <random>
void CTextureAnim::AutoSplitRandom(UINT size)
{
	float dutarion = 0.f;

	UINT width = m_texture->Width();
	UINT height = m_texture->Height();
	tTexAnim texAnim = {};



	for (size_t y = 0; y < height / size; y++)
	{
		for (size_t x = 0; x < width / size; x++)
		{
			texAnim.vLeftTop.x = x * size;
			texAnim.vLeftTop.y = y * size;
			texAnim.vDestSize.x = size;
			texAnim.vDestSize.y = size;
			texAnim.vSize.x = size;
			texAnim.vSize.y = size;
			texAnim.fDestDuration = dutarion;
			dutarion += 0.0055f;
			m_vecTexAnim.push_back(texAnim);


		}
		dutarion = 0.025f;
	}

	std::shuffle(std::begin(m_vecTexAnim), std::end(m_vecTexAnim), std::default_random_engine());
}

void CTextureAnim::Enter()
{
	m_state = eTextAnimState::START;
	m_vecTexAnim.clear();
	GETINSTANCE(CResourceManager)->LoadSound(L"ready", L"sound\\ready.wav")->Play();
	AutoSplitRandom(15);
}

void CTextureAnim::Remove()
{
	m_removeDuration = 0.f;
	m_state = eTextAnimState::REMOVE;
}

