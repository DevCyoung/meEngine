#pragma once

class CTexture;

struct tCamEffect
{
	CAMERA_EFFECT	m_eCurEffect;
	float			m_fAccTime;
	float			m_fMaxTime;
};


class CCamera
{
	SINGLETON(CCamera);

private:
	Vector2				m_vLook;
	Vector2				m_vDiff;
	CTexture* m_pBlindTex;

	list<tCamEffect>	m_CamEffectList;
	float				m_fRatio;

	Vector2				m_vOffset;
	float				m_fAccTime;		// Camera Shake ���� �ð�
	float				m_fMaxTime;		// Cemar Shake �ִ� �ð�
	float				m_fRange;		// ��鸲 ����
	float				m_fShakeSpeed;	// ��鸮�� �ӵ�
	float				m_fShakeDir;	// ���� ����
	bool				m_bCamShake;

public:
	void tick();
	void render(HDC _dc);

public:
	void SetLook(Vector2 _vLook) { m_vLook = _vLook; }
	Vector2 GetLook() { return m_vLook; }
	void FadeOut(float _fTerm);
	void FadeIn(float _fTerm);
	void CameraShake(float _fRange, float _fSpeed, float _fTerm);

public:
	Vector2 GetRenderPos(Vector2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vector2 GetRealPos(Vector2 _vRenderPos) { return _vRenderPos + m_vDiff; }

private:
	void CameraEffect();
	void CameraShake();
};

