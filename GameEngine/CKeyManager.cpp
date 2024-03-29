#include "pch.h"
#include "CKeyManager.h"
#include "CEngine.h"
#include "CTimeManager.h"
//async keys
int g_arrVK[(UINT)KEY::END] =
{
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	VK_LMENU,
	VK_LCONTROL,
	VK_LSHIFT,
	VK_TAB,
	VK_LBUTTON,
	VK_RBUTTON,
	'A',
	'S',
	'D',
	'W',
	'Z',
	'X',
	'C',
	'Q',
	'E',
	'R',
	'O',
	'P',
	'F',
	'I',
	'U',
	'Y',
	'T',
	'N',
	'M',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
};

CKeyManager::CKeyManager()
{
}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::init()
{
	for (int i = 0; i < (int)KEY::END; i++)
	{
		m_vecKey.push_back(tKeyInfo{ (KEY)i, KEY_STATE::NONE, FALSE, 0.f });
	}
}

void CKeyManager::tick()
{
	size_t len = m_vecKey.size();

	//현재 프로세스포커스
	if (GetFocus())
	{
		for (size_t i = 0; i < len; i++)
		{
			int vk_key = g_arrVK[(UINT)m_vecKey[i].key];

			//누르고있다
			if (GetAsyncKeyState(vk_key) & 0x8000)
			{
				//지금이제막 눌렸다. 이전틱에서 눌린적이없다.
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP; //딱 한프레임만 발생하는 이벤트이다
					m_vecKey[i].bPrev = true;
				}
				else //이전번tick에 눌려있었고 지금도 누르고있다
				{
					m_vecKey[i].state = KEY_STATE::PRESSED;
				}
				m_vecKey[i].fTime += DELTATIME;
			}
			else
			{
				//이전에도 안눌려있었고 지금도 안눌려있었다.
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				else
				{
					m_vecKey[i].state = KEY_STATE::RELEASED;
					m_vecKey[i].bPrev = false;
				}
				m_vecKey[i].fTime = 0.f;
			}
		}

		// Mouse 위치 갱신
		POINT ptMousePos = {};
		GetCursorPos(&ptMousePos);
		ScreenToClient(GETINSTANCE(CEngine)->GetMainWnd(), &ptMousePos);
		m_vMousePos = ptMousePos;

	}
	else // Window가 focus 상태가 아니다.
	{
		for (size_t i = 0; i < len; i++)
		{
			//웅크리기등등
			//모든키를 NONE으로
			if (KEY_STATE::TAP == m_vecKey[i].state || KEY_STATE::PRESSED == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::RELEASED;
			}
			else if (m_vecKey[i].state == KEY_STATE::RELEASED)
			{
				m_vecKey[i].state = KEY_STATE::NONE;
			}
			m_vecKey[i].fTime = 0.f;
		}
	}
}

float CKeyManager::GetKeyClmapTime(KEY _key, float end)
{

	if (m_vecKey[(UINT)_key].fTime < end)
		return m_vecKey[(UINT)_key].fTime;
	return end;

}
float CKeyManager::GetKeyClmapTime(KEY _key, float end, float clmap)
{
	if (m_vecKey[(UINT)_key].fTime >= end)
		return clmap;
	return m_vecKey[(UINT)_key].fTime;
}

float CKeyManager::GetKeyClmapAceel(KEY _key, float aceel, float limit)
{
	float result = m_vecKey[(UINT)_key].fTime * aceel;
	if (limit < result)
		return limit;
	return result;
}