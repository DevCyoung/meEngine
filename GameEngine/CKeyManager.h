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
	E,
	R,
	O,
	P,
	F,
	I,
	U,
	Y,
	T,
	N,
	M,
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
	TAP,		//키가눌린순간
	PRESSED,		//누르고있는
	RELEASED,	//키를 땟을때
	NONE,
};

//해당 키들이 무슨상태인가
struct tKeyInfo
{
	KEY			key;
	KEY_STATE	state;
	BOOL		bPrev;	//해당키가 이전에 틱에서 눌려있었나
	FLOAT		fTime;
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
	KEY_STATE	GetKeyState(KEY _key) { return m_vecKey[(UINT)_key].state; }
	float		GetKeyReleaseTime(KEY _key) { return m_vecKey[(UINT)_key].fTime; }
	//end 이상이면 end리턴
	float		GetKeyClmapTime(KEY _key, float end);
	//end 이상이면 cmlap리턴
	float		GetKeyClmapTime(KEY _key, float end, float clmap);
	//aceel
	float		GetKeyClmapAceel(KEY _key, float aceel, float limit);
	Vector2		GetMousePos() { return m_vMousePos; }
};