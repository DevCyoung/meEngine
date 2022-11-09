#include "pch.h"
#include "CAnimation.h"

#include "CGameObject.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CCamera.h"


#include "CTimeManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CEventManager.h"
#include "CAnimEnvManager.h"


#include "CEngine.h"
#include "CRenderHelper.h"
#include "CCollisionManager.h"

CAnimation::CAnimation(CAnimator* _pAnimator)
	: m_pAnimator(_pAnimator)
	, m_pAtlas(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::init(const wstring& _strName, CTexture* _pAtlas, Vector2 _vLeftTop, Vector2 _vSize, Vector2 _vOffset, int _iMaxFrmCount, float _fDuration)
{
	SetName(_strName);	// Animation 이름
	m_pAtlas = _pAtlas;	// Animation 의 아틀라스 이미지

	for (int i = 0; i < _iMaxFrmCount; ++i)
	{
		tAnimFrm frm = {};

		frm.vLeftTop = Vector2(_vLeftTop.x + (float)i * _vSize.x, _vLeftTop.y);
		frm.vSize = _vSize;
		frm.vOffset = _vOffset;
		frm.fDuration = _fDuration;
		m_vecFrm.push_back(frm);
	}
}


void CAnimation::tick()
{
	if (m_bFinish)
		return;

	m_fAccTime += DELTATIME;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{

		//만약 현재프레임이 이벤트를 등록했다면
		//이벤트를 신청한다.		
		if (nullptr != m_vecFrm[m_iCurFrm].action.instance)
		{
			tAnimEvent env = {};
			env.func = m_vecFrm[m_iCurFrm].action.func;
			env.instance = m_vecFrm[m_iCurFrm].action.instance;
			GETINSTANCE(CEventManager)->AddEvent(env);
		}

		if (m_pAnimator->GetReverse() == true)
		{

		}

		++m_iCurFrm;
		m_fAccTime = 0.f;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = (int)m_vecFrm.size() - 1;
			m_bFinish = true;
		}
	}
}

void CAnimation::render(HDC _dc)
{
	CGameObject* pOwnerObj = m_pAnimator->GetOwner();
	Vector2 vPos = GETINSTANCE(CCamera)->GetRenderPos(pOwnerObj->GetPos());

	tAnimFrm frame = m_vecFrm[m_iCurFrm];

	Vector2 camleft;
	Vector2 cambottom;
	Vector2 rp = pOwnerObj->GetPos();
	camleft.x = GETINSTANCE(CCamera)->GetLook().x - GETINSTANCE(CEngine)->GetWndScreenSize().x / 2; //left
	camleft.y = GETINSTANCE(CCamera)->GetLook().y - GETINSTANCE(CEngine)->GetWndScreenSize().y / 2;
	cambottom.x = camleft.x + GETINSTANCE(CEngine)->GetWndScreenSize().x;
	cambottom.y = camleft.y + GETINSTANCE(CEngine)->GetWndScreenSize().y;

	//if (camleft.x   > vPos.x + frame.vSize.x || camleft.y   > vPos.y + frame.vSize.y  ||
	//	cambottom.x < vPos.x - frame.vSize.x || cambottom.y < vPos.y - frame.vSize.y )
	//	return;

	if (camleft.x   > rp.x + frame.vSize.x * WINDOWX_PER_X / 2 ||
		camleft.y   > rp.y + frame.vSize.y * WINDOWX_PER_X / 2 ||
		cambottom.x < rp.x - frame.vSize.x * WINDOWX_PER_X / 2 ||
		cambottom.y < rp.y - frame.vSize.y * WINDOWX_PER_X / 2)
		return;



	CRenderHelper::StretchRender
	(
		m_pAtlas->GetDC(),
		frame.vLeftTop.x,
		frame.vLeftTop.y,
		frame.vSize.x,
		frame.vSize.y,
		_dc,
		vPos.x,
		vPos.y,
		frame.vOffset.x,
		frame.vOffset.y,
		pOwnerObj->GetFilpX(),
		pOwnerObj->GetFilpY()
	);

	if (GETINSTANCE(CCollisionManager)->GetDrawCollide() == true)
	{
		CRenderHelper::StretchRenderCollider(_dc, frame, vPos, pOwnerObj->GetFilpX());
	}
}



void CAnimation::ColorSwap(vector<UNIONCOLOR32> sourceColors, vector<UNIONCOLOR32> destColors)
{
	CRenderHelper::ColorSwap(m_pAtlas->GetDC(), m_pAtlas->Width(), m_pAtlas->Height(), sourceColors, destColors);
}

