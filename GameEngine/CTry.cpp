#include "pch.h"
#include "CTry.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeManager.h"
#include "CCamera.h"
#include "CRenderHelper.h"
#include "CTexture.h"

CTry::CTry()
	:m_state(TRYSTATE::WAIT)
	, m_delay{}
	,m_attackDir {}
	, m_dashFrameIdx(0)
	, m_dashFrameDelay(0.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(60.f, 60.f));

	CreateAnimator();
	GetAnimator()->LoadAnimation(L"animation\\monster\\try\\idle.anim");
	GetAnimator()->Play(L"IDLE", true);

	m_sponType = MONSETER_TYPE::TRY;
	m_hp = 1;

	m_startLen = 300.f;
}

CTry::CTry(const CTry& _other)
	: CRockmanMonster(_other)
	, m_state(TRYSTATE::WAIT)
	, m_delay{}
	, m_attackDir{}
{

}

CTry::~CTry()
{

}

void CTry::tick()
{
	CRockmanMonster::tick();

	if (m_isStart == false)
	{
		return;		
	}
	DashFrame();
	Vector2 pos = GetPos();
	if (m_state == TRYSTATE::WAIT)
	{
		m_delay[(UINT)TRYSTATE::WAIT] += DELTATIME;

		if (m_delay[(UINT)TRYSTATE::WAIT] >= 1.f)
		{
			m_attackDir = m_vecDir;
			m_delay[(UINT)TRYSTATE::ATTACK] = 0.f;
			m_state = TRYSTATE::ATTACK;
		}
	}

	if (m_state == TRYSTATE::ATTACK)
	{
		m_delay[(UINT)TRYSTATE::ATTACK] += DELTATIME;

		if (m_delay[(UINT)TRYSTATE::ATTACK] >= 0.7f)
		{
			m_attackDir = Vector2(0.f, 0.f);
			m_delay[(UINT)TRYSTATE::WAIT] = 0.f;
			m_state = TRYSTATE::WAIT;
		}
		else
		{
			pos += m_attackDir * 500.f * DELTATIME;			
		}

	}
	SetPos(pos);

	
}

void CTry::fixed_tick()
{
	CRockmanMonster::fixed_tick();
}

void CTry::render(HDC _dc)
{
	CRockmanMonster::render(_dc);
	CTexture* tex = GetAnimator()->GetCurAnimation()->GetAtlas();
	for (size_t i = 0; i < m_arrDashFrame.size(); i++)
	{
		float dist = (m_arrDashFrame[i].pos - GetPos()).Length();
		if (dist <= 20.f)
			continue;
		Vector2 renPos = GETINSTANCE(CCamera)->GetRenderPos(m_arrDashFrame[i].pos);
		//CRenderHelper::StretchRender(tex->GetDC(), m_arrDashFrame[i].frame, _dc, renPos, m_zero->GetFilpX(), 0.50f);
		UINT color = 0xffffffff;

		/*switch (m_zero->m_zeroMode)
		{
		case ZEROMODE::REDZERO:
		{
			color = REDZEROCOLOR;
		}
		break;
		case ZEROMODE::BLACKZERO:
		{
			color = BLACKZEROCOLOR;
		}
		break;
		case ZEROMODE::VIRUSZERO:
		{
			color = VIRUSZEROCOLOR;
		}
		break;
		}*/

		CRenderHelper::StretchRenderReplaceColor(tex->GetDC(), m_arrDashFrame[i].frame, _dc, renPos, GetFlipX(), 0.5f, BACKGROUNDCOLOR, color, true, m_renderPer);
	}
}


void CTry::DashFrame()
{
	//대쉬상태일떄
	m_dashFrameDelay += DELTATIME;
	if (m_state == TRYSTATE::ATTACK)
	{
		if (m_dashFrameDelay > 0.03f)
		{
			m_dashFrameIdx = m_dashFrameIdx % 15;
			m_dashFrameDelay = 0.f;
			tDashFrame frame;
			frame.frame = GetAnimator()->GetCurAnimation()->GetCurFrame();
			frame.pos = GetPos();
			frame.duration = 0.f;
			m_arrDashFrame.push_back(frame);
		}
	}

	for (size_t i = 0; i < m_arrDashFrame.size(); i++)
	{
		m_arrDashFrame[i].duration += DELTATIME;
	}

	for (int i = 0; i < m_arrDashFrame.size(); )
	{
		if (m_arrDashFrame[i].duration >= 0.23f)
		{
			m_arrDashFrame.erase(m_arrDashFrame.begin() + i);
		}
		else
		{
			i++;
		}
	}

}