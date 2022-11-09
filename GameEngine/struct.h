//�ӷ� ��Į��
//�ӵ� ���� 
//������ ������Ʈ class �� ���͸� ������ private����� ��

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

	void Normalize() //����ȭ
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


//WndPc�Ͱ��� �̺�Ʈó�����ּ����Ҷ� �������� ������ �־��ֱ����� ��������������

struct tAnimEvent
{
	//�����߰���
	DELEGATE        func;
	CEntity*	instance;
};

struct tBoxEvent
{
	//�����߰���
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
	//�����߰���
	DELEGATECOL        func;
	CEntity*		instance;
};

struct tColInfo
{
	Vector2 vLeftTop;
	Vector2 vOffset;
	Vector2 vScale;
};

//1������
struct tAnimFrm
{
	Vector2 vLeftTop;		//�̹��� ������ �������� �»�� ��ġ
	Vector2 vSize;			//������ ������
	Vector2	vOffset;		// �߰� �̵�
	float fDuration;		//shcnf �ð� �ش� �������� ���ʵ��� �����ų���ΰ�?
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
