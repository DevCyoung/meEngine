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

//
//#define _EDITOR_MODE
//
////960 720
////320 240
//
//#define LEVEL_EDITOR 1
//#define LEVEL_GAME   2
//
//#ifdef  _EDITOR_MODE
//#define LEVEL_MODE LEVEL_EDITOR
//#define windowSizeX 1280
//#define windowSizeY 1000
//#else
//#define LEVEL_MODE LEVEL_GAME
//#define windowSizeX 320
//#define windowSizeY 240
//#endif

class CEntity;
class CLineCollider;
typedef void(CEntity::* DELEGATE)(void);
typedef void(CEntity::* DELEGATECOL)(CLineCollider* _other);



enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	BLACK,
	YELLOW,
	ORANGE,	
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
	MONSTER,
	DEFAUT,
	PLAYER,		//플레이어
	PLAYER_PROJECTILE,	//플레이어가 쏜 미사일
	MONSTER_PROJECTTILE,
	PLATFORM,
	WALL,
	MOUSE,
	UI=15,						//가중나중에 그려져야함
	END = 16,
};

enum class LINELAYER
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	MOUSE,
	LEFTWALL,
	UPWALL,
	RIGHTWALL,
	DOWNWALL,

	PLAYER,
	MONSTER,
	END = 16,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,	//wParam : Object Adress lParam : Layer Type
	DELETE_OBJECT,  //Wparam : Object Adress
	DELETE_LINECOL,
	LEVEL_CHANGE,	//Wparam : LEVEL_TYPE(Next Level Type)
	ANIMATION,
};

enum class CAMERA_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

//에디터모드
enum class EDITOR_MODE
{
	TILE,
	ANIMATION,
	OBJECT,
	LINECOLLIDER,
	BOXCOLLIDER,
	NONE
};

enum class LINECOL_MODE
{
	ADD,
	REMOVE,
	NONE,
};

enum class MOUSE_MODE
{
	NONE,
	ONEDOWN,
	TWODOWN,
};

enum class WALLDIR
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	NONE,
};

enum class COLLIDE_DIR
{
	NONE,
	LEFT,
	UP,
	RIGHT,
	DOWN,
	END,
};

enum class COL_STATE_DIR
{
	LEFT	= 0x00000001,
	UP		= 0x00000002,
	RIGHT	= 0x00000004,
	DOWN	= 0x00000008,
	LRD		= LEFT | RIGHT | DOWN,
	NONE	= 0x00000000,
};

enum class RAY_TYPE
{
	LEFT_UP     ,
	LEFT_DOWN   ,
	UP_LEFT     ,
	UP_RIGHT    ,
	RIGHT_UP    ,
	RIGHT_DOWN  ,
	DOWN_LEFT   ,
	DOWN_RIGHT  ,
	DOWN		, //걸어다니기
	END         ,
};

enum class RAY_FLAG
{
	DOWN_LEFT  = 0X00000001,
	DOWN_RIGHT = 0X00000002,
	UP_LEFT    = 0X00000004,
	UP_RIGHT   = 0X00000008,
	LEFT_UP    = 0X00000010,
	LEFT_DOWN  = 0X00000020,
	RIGHT_UP   = 0X00000040,
	RIGHT_DOWN = 0X00000080,
};