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
#include "CRaycast.h"

#include  "CRigidbody.h"

//���⼭ �浹������ ������ �մϴ�.
void CZero::fixed_tick()
{
	CRockmanObj::fixed_tick();

	PlayerControll();

}

void CZero::PlayerControll()
{
}