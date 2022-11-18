#include "pch.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CTexture.h"
#include "CResource.h"
#include "CSound.h"


CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
    for (; iter != m_mapTex.end(); ++iter)
    {
        delete iter->second;
    }

    map<wstring, CSound*>::iterator siter = m_mapSounds.begin();
    for (; siter != m_mapSounds.end(); ++siter)
    {
        delete siter->second;
    }


}


CTexture* CResourceManager::FindTexture(const wstring& _strKey)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
    if (iter == m_mapTex.end())
    {
        return nullptr;
    }

    return iter->second;
}

CTexture* CResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CResource* pTexture = FindTexture(_strKey);

    if (nullptr != pTexture)
        return (CTexture*)pTexture;

    // PathMgr �� �̿��ؼ� ���� Texture�� ��θ� �����.
    wstring strFilePath = GETINSTANCE(CPathManager)->GetContentPath();
    strFilePath += _strRelativePath;

    // �ؽ��� ���� �� �ε�
    pTexture = new CTexture;
    pTexture->Load(strFilePath);
    pTexture->SetKey(_strKey);
    pTexture->SetRelativePath(_strRelativePath);

    // Map �� ����
    m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));
    return (CTexture*)pTexture;
}

CTexture* CResourceManager::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
    CTexture* pTexture = FindTexture(_strKey);

    if (nullptr != pTexture)
        return (CTexture*)pTexture;

    // �ؽ��� ���� �� �ε�
    pTexture = new CTexture;
    pTexture->Create(_iWidth, _iHeight);
    pTexture->SetKey(_strKey);

    // Map �� ����
    m_mapTex.insert(make_pair(_strKey, pTexture));
    return pTexture;
}

CTexture* CResourceManager::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight, UINT _fillColor)
{
    CTexture* pTexture = FindTexture(_strKey);

    if (nullptr != pTexture)
        return (CTexture*)pTexture;

    // �ؽ��� ���� �� �ε�
    pTexture = new CTexture;
    pTexture->Create(_iWidth, _iHeight, _fillColor);
    pTexture->SetKey(_strKey);

    // Map �� ����
    m_mapTex.insert(make_pair(_strKey, pTexture));
    return pTexture;
}

CSound* CResourceManager::FindSound(const wstring& _strKey)
{
    map<wstring, CSound*>::iterator iter = m_mapSounds.find(_strKey);
    if (iter == m_mapSounds.end())
    {
        return nullptr;
    }

    return iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
    CResource* pSound = FindSound(_strKey);

    if (nullptr != pSound)
        return (CSound*)pSound;

    // PathMgr �� �̿��ؼ� ���� Texture�� ��θ� �����.
    wstring strFilePath = GETINSTANCE(CPathManager)->GetContentPath();
    strFilePath += _strRelativePath;

    // �ؽ��� ���� �� �ε�
    pSound = new CSound();
    pSound->Load(strFilePath);
    pSound->SetKey(_strKey);
    pSound->SetRelativePath(_strRelativePath);

    // Map �� ����
    m_mapSounds.insert(make_pair(_strKey, (CSound*)pSound));

    return (CSound*)pSound;
}
