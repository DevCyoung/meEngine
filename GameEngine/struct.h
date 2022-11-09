//속력 스칼라
//속도 벡터 
//어차피 오브젝트 class 가 벡터를 가질때 private멤버로 씀

class CGameObject;

struct Vector2
{
	float x;
	float y;

public:
	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}
	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{}

	Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vector2(UINT _x, UINT _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vector2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

	Vector2 operator -()
	{
		return Vector2(-x, -y);
	}


public:

	void Normalize() //정규화
	{
		float fDist = sqrtf(x * x + y * y);
		x /= fDist;
		y /= fDist;
	}

	Vector2 operator + (Vector2 _vOther)
	{
		return Vector2(x + _vOther.x, y + _vOther.y);
	}

	Vector2& operator += (Vector2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
		return *this;
	}

	Vector2 operator - (Vector2 _vOther)
	{
		return Vector2(x - _vOther.x, y - _vOther.y);
	}
	Vector2& operator -= (Vector2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
		return *this;
	}

	Vector2 operator / (float f)
	{
		return Vector2(x / f, y / f);
	}

	Vector2& operator /= (float f)
	{
		x /= f;
		y /= f;
		return *this;
	}

	Vector2 operator * (float f)
	{
		return Vector2(x * f, y * f);
	}

	Vector2& operator *= (float f)
	{
		x *= f;
		y *= f;
		return *this;
	}
};

struct tEvent
{
	EVENT_TYPE	eType;
	DWORD_PTR	wParam;
	DWORD_PTR	lParam;
};


//WndPc와같이 이벤트처리해주세요할때 여러가지 정보를 넣어주기위해 여러가지만들어둠

struct tAnimEvent
{
	//내가추가함
	DELEGATE        func;
	CEntity*	instance;
};

struct tBoxEvent
{
	//내가추가함
	DELEGATE        func;
	CEntity* instance;
};

struct tFixedEvent
{
	DELEGATE        func;
	CEntity*		instance;
};

struct tColliEvent
{
	//내가추가함
	DELEGATECOL        func;
	CEntity*		instance;
};

struct tColInfo
{
	Vector2 vLeftTop;
	Vector2 vOffset;
	Vector2 vScale;
};

//1프레임
struct tAnimFrm
{
	Vector2 vLeftTop;		//이미지 내에서 프레임의 좌상단 위치
	Vector2 vSize;			//프레임 사이즈
	Vector2	vOffset;		// 추가 이동
	float fDuration;		//shcnf 시간 해당 프레임을 몇초동안 노출시킬것인가?
	tAnimEvent action;
	tColInfo colInfo;
};


union UNIONCOLOR32
{
	struct
	{
		UCHAR A;
		UCHAR B;
		UCHAR G;
		UCHAR R;
	};
	DWORD COLOR;
};
struct tTexAnim
{
	Vector2 vLeftTop;
	Vector2 vSize;
	Vector2 vDestSize;
	float   fDuration;
	float	fDestDuration;
};
