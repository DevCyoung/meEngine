#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CGameObject.h"

CAnimator::CAnimator(CGameObject* _pOwner)
	: CComponent(_pOwner)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
	, m_bReverse(false)
	, m_bisPlay(true)
{

}

CAnimator::CAnimator(const CAnimator& _other)
	: CComponent(_other)
	, m_pCurAnim(_other.m_pCurAnim)
	, m_bRepeat(_other.m_bRepeat)
	, m_bReverse(false)
	, m_bisPlay(true)
{
	map<wstring, CAnimation*>::const_iterator iter = _other.m_mapAnim.begin();
	for (; iter != _other.m_mapAnim.end(); ++iter)
	{
		CAnimation* pAnim = iter->second->Clone();
		pAnim->Reset();
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}

	// ���� �ִϸ��̼��� ���
	if (nullptr != m_pCurAnim)
	{
		Play(_other.m_pCurAnim->GetName(), m_bRepeat);
	}


}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{		
		delete iter->second;
	}
}

void CAnimator::tick()
{	
}

void CAnimator::final_tick()
{
	if (nullptr == m_pCurAnim)
		return;

	if (m_bisPlay == false)
		return;

	if (m_pCurAnim->IsFinish() && m_bRepeat)
	{
		m_pCurAnim->Reset();
	}

	

	m_pCurAnim->tick();
}

void CAnimator::render(HDC _dc)
{
	if (nullptr == m_pCurAnim)
		return;

	m_pCurAnim->render(_dc);
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
		return;
	}

	m_pCurAnim = pAnim;
	m_pCurAnim->Reset();
	m_bRepeat = _bRepeat;
}

void CAnimator::TrigerPlay(const wstring& _strName, bool _bRepeat)
{
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
		return;
	}

	if (m_pCurAnim == pAnim)
		return;
	
	m_pCurAnim = pAnim;
	m_pCurAnim->Reset();
	m_bRepeat = _bRepeat;
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vector2 _vLeftTop, Vector2 _vSize, Vector2 _vOffset, int _iMaxFrmCount, float _fDuration)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(!pAnim);

	pAnim = new CAnimation(this);
	pAnim->init(_strName, _pAtlas, _vLeftTop, _vSize, _vOffset, _iMaxFrmCount, _fDuration);
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

CAnimation* CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation(this);

	pAnim->Load(_strRelativePath);
	

	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));

	return pAnim;
}

void CAnimator::SetAnimFrameFunc(const wstring& _animName, int _iFrameNum,  CGameObject* _obj, DELEGATE _delegate)
{
	CAnimation* anim = this->FindAnimation(_animName);
	assert(anim);
	anim->SetFrameEvent(_iFrameNum, _obj, _delegate);
}

void CAnimator::SetAllAtlas(CTexture* atlas)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		iter->second->m_pAtlas = atlas;		
	}
}
