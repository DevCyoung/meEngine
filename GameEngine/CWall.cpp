#include "pch.h"
#include "CWall.h"
#include "CCollider.h"
CWall::CWall()
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(50.f, 50.f));
}

CWall::CWall(const CWall& _other)
{
}

CWall::~CWall()
{
}


void CWall::ResizeCollider(Vector2 leftTop, Vector2 bottom)
{
	//중심점구하기

	Vector2 pos		= {};
	Vector2 scale	= {};
	Vector2 l		= {};
	Vector2 b		= {};


	scale.x = abs(bottom.x - leftTop.x);
	scale.y = abs(bottom.y - leftTop.y);

	l.x = min(leftTop.x, bottom.x);
	l.y = min(leftTop.y, bottom.y);
	b.x = max(leftTop.x, bottom.x);
	b.y = max(leftTop.y, bottom.y);

	leftTop = l;

	pos.x = leftTop.x + scale.x / 2;
	pos.y = leftTop.y + scale.y / 2;

	GetCollider()->SetScale(scale);
	SetPos(pos);
}


void CWall::OnTriggerEnter(CCollider* _pOhter)
{

}

void CWall::OnTriggerStay(CCollider* _pOhter)
{
}

void CWall::OnTriggerExit(CCollider* _pOhter)
{
}

