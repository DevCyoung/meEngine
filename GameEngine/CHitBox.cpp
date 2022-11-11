#include "pch.h"
#include "CHitBox.h"
#include "CRenderHelper.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CEngine.h"
#include "CSound.h"
#include "CResourceManager.h"
#include "CTimeManager.h"
CHitBox::CHitBox()
	: _pOwner(nullptr)
	, _pOwnerAnim(nullptr)
	, _tartget(LAYER::END)
	, _isOn(true)
	, _prevIdx(-1)
	, _prevAnim(nullptr)
{
	//default;
	CreateCollider();

}


CHitBox::~CHitBox()
{
}


void CHitBox::tick()
{


	tColInfo colInfo = _pOwnerAnim->GetCurAnimation()->GetCurFrame().colInfo;
	CCollider* collider = GetCollider();
	if (colInfo.vScale.x > 3.f && colInfo.vScale.y > 3.f)
	{	
		_isOn = true;
		collider->GetScale();

		Vector2 vLPos;
		Vector2 vPos = _pOwner->GetPos();

		vLPos.x = vPos.x - ((colInfo.vOffset.x * WINDOWX_PER_X - colInfo.vScale.x * WINDOWX_PER_X)) / 2;
		vLPos.y = vPos.y - ((colInfo.vOffset.y * WINDOWX_PER_Y - colInfo.vScale.y * WINDOWX_PER_Y)) / 2;



		if (_pOwner->GetFilpX() == false)
		{
			vLPos.x = vPos.x - (colInfo.vScale.x / 2 + colInfo.vOffset.x) * WINDOWX_PER_X;
			vLPos.y = vPos.y - (colInfo.vScale.y / 2 + colInfo.vOffset.y) * WINDOWX_PER_Y;
		}
		else
		{
			vLPos.x = vPos.x + (colInfo.vOffset.x - colInfo.vScale.x / 2) * WINDOWX_PER_X;
			vLPos.y = vPos.y - (colInfo.vOffset.y + colInfo.vScale.y / 2) * WINDOWX_PER_Y;
		}


		Vector2 pos = {};
		pos.x = vLPos.x + colInfo.vScale.x * WINDOWX_PER_X / 2;
		pos.y = vLPos.y + colInfo.vScale.y * WINDOWX_PER_X / 2;

		SetPos(pos);
		collider->SetScale(colInfo.vScale * WINDOWX_PER_X);

	}
	else
	{
		_isOn = false;
		GETINSTANCE(CTimeManager)->SetDelayTime(1.f);
	}
	//tColInfo colInfo = frame.colInfo;
	

	//if (IsDead() == true)
	//{
	//	return;
	//}

	//CRenderHelper::StretchRenderCollider(_dc, frame, vPos, pOwnerObj->GetFilpX());

	if (_prevAnim != _pOwnerAnim->GetCurAnimation())
	{
		SetPos(Vector2(-10000.f, +10000.f));

	}
	_prevAnim = _pOwnerAnim->GetCurAnimation();


	if (_prevIdx != _pOwnerAnim->GetCurAnimation()->GetCurFrameIdx())
	{
		SetPos(Vector2(-10000.f, +10000.f));
	}
	_prevIdx = _pOwnerAnim->GetCurAnimation()->GetCurFrameIdx();

	CRockmanObj::tick();
}


void CHitBox::render(HDC _dc)
{
	//if (IsDead() == false)
	//{
	//	return;
	//}
	if (_isOn == false)
	{
		return;
	}
	CRockmanObj::render(_dc);
}


void CHitBox::SetHitBox(bool b)
{
	SetDead(b);
}

void CHitBox::SetHitScale(tAnimFrm frm)
{

}

void CHitBox::OnTriggerExit(CCollider* _pOther)
{

}

void CHitBox::OnTriggerEnter(CCollider* _pOther)
{
	if (_isOn == false)
	{
		return;
	}
		
	if (_pOther->GetOwner()->GetLayer() != _tartget)
	{
		return;
	}
	
	
	_pOwner->AttackEvent(_prevAnim->GetCurFrame(), _pOther);
}


void CHitBox::SetTartgetLayer(LAYER layer)
{
	_tartget = layer;
}

void CHitBox::SetOwner(CRockmanObj* owner)
{
	_pOwner = owner;

	_pOwnerAnim = _pOwner->GetAnimator();
	assert(_pOwnerAnim);
}
