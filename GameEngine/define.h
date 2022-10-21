#pragma

// SINGLETON
#define SINGLETON(type)	public : static type* GetInstance() {static type manager; return &manager; }\
						private : type(); ~type();
#define GETINSTANCE(type)	type::GetInstance()

//KEY MANAGER
#define GET_INPUT_STATE(Key)		CKeyManager::GetInstance()->GetKeyState(Key)
#define IS_INPUT_TAB(Key)			GET_INPUT_STATE(Key) ==  KEY_STATE::TAP
#define IS_INPUT_PRESSED(Key)		GET_INPUT_STATE(Key) ==  KEY_STATE::PRESSED
#define IS_INPUT_RELEASE(Key)		GET_INPUT_STATE(Key) ==  KEY_STATE::RELEASED

//TIME MANAGER
#define DELTATIME GETINSTANCE(CTimeManager)->GetDeltaTime()

#define CLONE(type) virtual type* Clone() { return new type(*this); }
#define CLONE_DEACTIVATE(type) virtual type* Clone() { assert(nullptr); return nullptr; }

#define TILE_SIZE 64
#define RAD	0.0174532925


//#define windowSizeX 720
//#define windowSizeY 460


//#define _EDITOR_MODE

//960 720
//320 240

#define LEVEL_EDITOR 1
#define LEVEL_GAME   2

#ifdef  _EDITOR_MODE
#define LEVEL_MODE LEVEL_EDITOR
#define windowSizeX 1280
#define windowSizeY 1000
#else
#define LEVEL_MODE LEVEL_GAME
#define windowSizeX 320
#define windowSizeY 240
#endif`

class CEntity;
class CLineCollider;
typedef void(CEntity::* DELEGATE)(void);
typedef void(CEntity::* DELEGATECol)(CLineCollider* _other);

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};

enum class LEVEL_TYPE
{
	TITLE,
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	COLLISION,
	EDITOR,
	END, //갯수지정용도
};


enum class LAYER
{
	BACKGROUND,	//배경
	TILE,\
	PLAYER,		//플레이어
	DEFAUT,
	MONSTER,
	PLAYER_PROJECTILE,	//플레이어가 쏜 미사일
	MONSTER_PROJECTTILE,
	PLATFORM,

	UI=15,						//가중나중에 그려져야함
	END = 16,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,	//wParam : Object Adress lParam : Layer Type
	DELETE_OBJECT,  //Wparam : Object Adress
	LEVEL_CHANGE,	//Wparam : LEVEL_TYPE(Next Level Type)
	ANIMATION,
};

enum class CAMERA_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};