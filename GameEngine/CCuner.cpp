#include "pch.h"
#include "CCuner.h"
#include "CAnimator.h"
#include "CCollider.h"

CCuner::CCuner()
{
	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\cuner\\idle.anim");

	CreateCollider();
	GetCollider()->SetScale(Vector2(70.f, 180.f));

	CreateRockmanRrigidbody();

	GetAnimator()->Play(L"IDLE", true);
	m_hp = 15;
}

CCuner::CCuner(const CCuner& _other)
{
}

CCuner::~CCuner()
{
}
