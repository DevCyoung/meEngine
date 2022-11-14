#include "pch.h"
#include "CMonsterHitBox.h"
#include "CHitBox.h"
#include "CRenderHelper.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CEngine.h"
#include "CSound.h"
#include "CResourceManager.h"
#include "CTimeManager.h"
CMonsterHitBox::CMonsterHitBox()
{
	//SetTag(LAYER::MONSTERATTACK);
}

CMonsterHitBox::~CMonsterHitBox()
{
}


void CMonsterHitBox::tick()
{

	if (_pOwnerAnim == nullptr)
		return;

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



		if (_pOwner->GetFlipX() == false)
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
	}

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

void CMonsterHitBox::render(HDC _dc)
{
	if (_isOn == false)
	{
		return;
	}
	CRockmanObj::render(_dc);
}


void CMonsterHitBox::OnTriggerExit(CCollider* _pOther)
{
}

void CMonsterHitBox::OnTriggerEnter(CCollider* _pOther)
{
}

