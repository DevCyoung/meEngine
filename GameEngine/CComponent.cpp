#include "pch.h"
#include "CComponent.h"

CComponent::CComponent(CGameObject* _obj)
	:m_pOwner(_obj)
{
}

CComponent::~CComponent()
{
}
