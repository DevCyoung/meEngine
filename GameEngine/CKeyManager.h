#pragma once

enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,

	SPACE,
	ENTER,
	ESE,
	LALT,
	LCTRL,
	LSHIFT,
	TAB,

	LBTN,
	RBTN,

	A,
	S,
	D,
	W,
	Z,
	X,
	C,
	Q,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	END,
};

enum class KEY_STATE
{
	TAP,		//Ű����������
	PRESSED,		//�������ִ�
	RELEASED,	//Ű�� ������
	NONE,
};

//�ش� Ű���� ���������ΰ�
struct tKeyInfo
{
	KEY			key;
	KEY_STATE	state;
	BOOL		bPrev;	//�ش�Ű�� ������ ƽ���� �����־���
};

class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	vector<tKeyInfo>	m_vecKey;
	Vector2				m_vMousePos;

public:
	void init();
	void tick();

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKey[(UINT)_key].state; }
	Vector2 GetMousePos() { return m_vMousePos; }
};