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
	PlayerControll();

	//Ȥ�ö� left right ray�� �浹�ߴٸ�
	//�о��
	if (m_ray.GetCollideCnt(RAY_TYPE::RIGHT_UP))
	{
		Vector2 p1 = m_ray.GetLineCol(RAY_TYPE::RIGHT_UP)->GetP1();
		Vector2 pos = Vector2(p1.x - m_ray.GetHdist() + 10, GetPos().y);
		SetPos(pos);
	}
	else if(m_ray.GetCollideCnt(RAY_TYPE::RIGHT_DOWN))
	{
		Vector2 p1 = m_ray.GetLineCol(RAY_TYPE::RIGHT_UP)->GetP1();
		Vector2 pos = Vector2(p1.x - m_ray.GetHdist() + 10, GetPos().y);
		SetPos(pos);
	}


	if (m_ray.GetCollideCnt(RAY_TYPE::LEFT_UP) || m_ray.GetCollideCnt(RAY_TYPE::LEFT_DOWN))
	{

	}
}

void CZero::PlayerControll()
{
	//����1
	//�߷��̾�������...
	//�÷��̾��� Down ray�� �ϳ��� �浹���϶�
	//�߷��� 0�����Ѵ�.

	Vector2 pos = this->GetPos();

	if (m_ray.GetCollideCnt(RAY_TYPE::DOWN_LEFT) || m_ray.GetCollideCnt(RAY_TYPE::DOWN_RIGHT) || m_ray.GetCollideCnt(RAY_TYPE::DOWN))
	{
		this->GetRigidbody()->SetGravity(false);
	}




	if (IS_INPUT_PRESSED(KEY::LEFT))
	{
		this->SetFilpX(false);
		Vector2 velocity = this->GetRigidbody()->GetVelocity();
		this->GetRigidbody()->SetVelocity(Vector2(-200.f, velocity.y));
		//pos.x -= 200 * DELTATIME;
	}

	if (IS_INPUT_RELEASE(KEY::LEFT))
	{
		this->GetRigidbody()->SetVelocity(Vector2(0.f, 0));
	}

	if (IS_INPUT_PRESSED(KEY::RIGHT))
	{
		this->SetFilpX(true);
		Vector2 velocity = this->GetRigidbody()->GetVelocity();
		this->GetRigidbody()->SetVelocity(Vector2(+200.f, velocity.y));
		//pos.x += 200 * DELTATIME;
	}

	if (IS_INPUT_RELEASE(KEY::RIGHT))
	{
		this->GetRigidbody()->SetVelocity(Vector2(0.f, 0));
	}



	if (IS_INPUT_PRESSED(KEY::C))
	{
		this->GetRigidbody()->AddForce(Vector2(0.f, -1600.f));
	}

	if (IS_INPUT_PRESSED(KEY::DOWN))
	{
		//pos.y += 200 * DELTATIME;
	}


	SetPos(pos);
}