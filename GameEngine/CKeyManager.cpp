#include "pch.h"
#include "CKeyManager.h"
#include "CEngine.h"
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
		m_vecKey.push_back(tKeyInfo{ (KEY)i, KEY_STATE::NONE, FALSE });
	}
}

void CKeyManager::tick()
{
	size_t len = m_vecKey.size();

	//���� ���μ�����Ŀ��
	if (GetFocus())
	{
		for (size_t i = 0; i < len; i++)
		{
			int vk_key = g_arrVK[(UINT)m_vecKey[i].key];
			//�������ִ�
			if (GetAsyncKeyState(vk_key) & 0x8000)
			{
				//���������� ���ȴ�. ����ƽ���� �������̾���.
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP; //�� �������Ӹ� �߻��ϴ� �̺�Ʈ�̴�
					m_vecKey[i].bPrev = true;
				}
				else //������tick�� �����־��� ���ݵ� �������ִ�
				{
					m_vecKey[i].state = KEY_STATE::PRESSED;
				}
			}
			else
			{
				//�������� �ȴ����־��� ���ݵ� �ȴ����־���.
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				else
				{
					m_vecKey[i].state = KEY_STATE::RELEASED;
					m_vecKey[i].bPrev = false;
				}
			}
		}

		// Mouse ��ġ ����
		POINT ptMousePos = {};
		GetCursorPos(&ptMousePos);
		ScreenToClient(GETINSTANCE(CEngine)->GetMainWnd(), &ptMousePos);
		m_vMousePos = ptMousePos;

	}
	else // Window�� focus ���°� �ƴϴ�.
	{
		for (size_t i = 0; i < len; i++)
		{
			//��ũ������
			//���Ű�� NONE����
			if (KEY_STATE::TAP == m_vecKey[i].state || KEY_STATE::PRESSED == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::RELEASED;
			}
			else if (m_vecKey[i].state == KEY_STATE::RELEASED)
			{
				m_vecKey[i].state = KEY_STATE::NONE;
			}
		}
	}
}
