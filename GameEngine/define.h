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

#define INPUT_RELEASE_TIME(Key)		CKeyManager::GetInstance()->GetKeyReleaseTime(Key)

#define INPUT_END_TIME(Key, End)		CKeyManager::GetInstance()->GetKeyClmapTime(Key, End)
#define INPUT_CLP_TIME(Key, End, Cmp)	CKeyManager::GetInstance()->GetKeyClmapTime(Key, End, Cmp)
#define INPUT_ACELL(Key, Acell, Limit)	CKeyManager::GetInstance()->GetKeyClmapAceel(Key, Acell, Limit)

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
class CRockmanObj;

typedef void(CEntity::* DELEGATE)(void);
typedef void(CEntity::* DELEGATERockman)(CRockmanObj* _other);
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
	CYBERSPACE,
	CYBERSPACE2,
	CYBERSPACE3,
	CYBERSPACE4,
	CYBERSPACEBOSS,
	END, //갯수지정용도
};


enum class LAYER
{
	BACKGROUND,	//배경
	TILE,\
	MONSTER,
	DEFAUT,
	OBJECT,
	MONSTERATTACK,
	PLAYER,						//플레이어
	PLAYERATTACK,
	CAMERAWALL,			//플레이어가 쏜 미사일
	CAMERA,
	EVENT,
	WALL,						//Camera
	LINE,
	MOUSE,
	EDITOR,
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
	ATLAS,
	COLLIDE,
	TILE,
	ANIMATION,
	OBJECT,
	LINECOLLIDER,
	CAMERAWALL,
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

enum class MONSTER_STATE
{
	TYPE1,
	TYPE2,
	TYPE3,
	TYPE4,
	END,
};

enum class MONSETER_TYPE
{
	MIRU,
	TRY,
	GOSM,
	BOSS,
	NONE,
};

enum class EVENTBOX_TYPE
{
	NEXTAREA,
	BOSSDOOR1,
	BOSSDOOR2,
};

enum class PLAYER_STATE
{
	IDLE = 0x00000000,
	WALK = 0x00000001,
	FALLING = 0x00000002,
	DASH = 0x00000004,
	JUMP = 0x00000008,
	WALLSLIDE = 0x00000010,
	LANDATTACK1 = 0x00000020,
	LANDATTACK2 = 0x00000040,
	LANDATTACK3 = 0x00000080,
	FALLINGATTACK = 0x00000100,
	WALLSLIDEATTACK = 0x00000200,
	LADDERATTACK = 0x00000400,
	LAND = 0x00000800,
	DAMAGED = 0x00001000,
	TRJUMP = 0x00020000,
	SPECIALATTACK = 0x00040000,
	ENTER = 0x00080000,
	RETURN = 0x00100000,
	VICTORYRETURN = 0x00200000,
	RETURNREADY = 0x00400000,
	BLINK = 0x00800000,
	NONE = 0x01000000,
};


enum class COLIDE_EIDT_MODE
{
	LINE = 0,
	WALL,
	NEXTAREAEBOX,
	BOSSDOOR1BOX,
	BOSSDOOR2BOX,
	CAMERAWALL,	
	END,
};

enum class DAMAGED_STATE
{
	NONE,
	IDLE,
	DAMAGED,
	ULTIMAGE,
};

enum class EFFECT_TYPE
{
	TIN,
	VERTICALSLICE,
	SLOPSLICE,
	DASHSDUST,
	LANDDASH,
	LANDDASHPOWER,
	WALLSLIDEDUST,
	WALLHIT,
	BOOMRED,
	BOOMWHITE,
	CYBERTARGET,
	END,
};