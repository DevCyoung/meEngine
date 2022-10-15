#include "pch.h"
#include "CRigidbody.h"
#include "CTimeManager.h"
#include "CGameObject.h"

CRigidbody::CRigidbody(CGameObject* _pOwner)
	: CComponent(_pOwner)
	, m_fMass(1.f)
	, m_fFriction(100.f)
	, m_fFrictionScale(1.f)
	, m_fVelocityLimit(10000.f)
	, m_fGravityVLimit(10000.f)
	, m_fGravityAccel(0.f)
	, m_bGravityUse(false)
	, m_bGround(false)
{
}

CRigidbody::CRigidbody(const CRigidbody& _other)
	: CComponent(_other)
	, m_vForce(_other.m_vForce)
	, m_vVelocity(_other.m_vVelocity)
	, m_fMass(_other.m_fMass)
	, m_fFriction(_other.m_fFriction)
	, m_fFrictionScale(_other.m_fFrictionScale)
	, m_fVelocityLimit(_other.m_fVelocityLimit)
	, m_fGravityVLimit(_other.m_fGravityVLimit)
	, m_fGravityAccel(_other.m_fGravityAccel)
	, m_bGravityUse(_other.m_bGravityUse)
	, m_bGround(false)
{
}

CRigidbody::~CRigidbody()
{

}

void CRigidbody::tick()
{

}

void CRigidbody::final_tick()
{
	// F = M x A
	// ���ӵ� ���ϱ�
	Vector2 vAccel = m_vForce / m_fMass;

	// ���ӵ��� �̿��ؼ� �ӵ��� ������Ŵ
	m_vVelocity += vAccel * DELTATIME;

	// �߷��� ����ϴ� ����, ���� �־�� ������ ����
	// �߷��� ���� ������ ������ �ٷ� ����
	if (m_bGravityUse && m_bGround || !m_bGravityUse)
	{
		// ���� ���ӵ�
		Vector2 vFriction = -m_vVelocity;
		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DELTATIME);
		}

		// �ӵ� ���ҷ�(�����¿� ����) �� ���� �ӵ��� �Ѿ� �� ���, ���� ���η� �����.
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			m_vVelocity = Vector2(0.f, 0.f);
		}
		else
		{
			// ���� �ӵ� �ݴ�������� ������ ���� �ӵ� ����
			m_vVelocity += vFriction;
		}
	}

	// �߷� ���� + ���� ���� ==> �߷�
	if (m_bGravityUse && !m_bGround)
	{
		Vector2 vGravityAccel = Vector2(0.f, m_fGravityAccel);
		m_vVelocity += vGravityAccel * DELTATIME;
	}


	// �ӵ� ���� ����(��, ��)
	// �߷��� ����ϴ� ���, �¿� �̵��� �߷¹���(�Ʒ�) �� �ӵ������� ���� �����Ѵ�.
	if (m_bGravityUse)
	{
		if (m_fVelocityLimit < fabsf(m_vVelocity.x))
		{
			m_vVelocity.x = (m_vVelocity.x / fabsf(m_vVelocity.x)) * m_fVelocityLimit;
		}

		if (m_fGravityVLimit < fabsf(m_vVelocity.y))
		{
			m_vVelocity.y = (m_vVelocity.y / fabsf(m_vVelocity.y)) * m_fGravityVLimit;
		}
	}

	// �߷��� ������� ������, ��� �������ε� �ӵ� ������ �Ǵ�.
	else
	{
		if (m_fVelocityLimit < m_vVelocity.Length())
		{
			// ���� �ӵ��� �Ѱ��� ���
			m_vVelocity.Normalize();
			m_vVelocity *= m_fVelocityLimit;
		}
	}

	// ������Ʈ�� ��ġ
	Vector2 vPos = GetOwner()->GetPos();

	// �ӵ�(�ӷ� + ����) �� �°� ��ü�� �̵���Ŵ
	vPos.x += m_vVelocity.x * DELTATIME;
	vPos.y += m_vVelocity.y * DELTATIME;

	GetOwner()->SetPos(vPos);

	m_vForce = Vector2(0.f, 0.f);
}

void CRigidbody::render(HDC _dc)
{

}

void CRigidbody::SetGround(bool _bGround)
{
	m_bGround = _bGround;

	if (m_bGround)
	{
		m_vVelocity.y = 0.f;
	}
}