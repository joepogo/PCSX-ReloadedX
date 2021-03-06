#include "guitexturemanager.h"
#include "xboxgui.h"

#include "utils\StringUtils.h"

using namespace std;

CGUITextureManager::CGUITextureManager()
{
	m_pd3dDevice = NULL;
}

CGUITextureManager::~CGUITextureManager()
{
}

bool CGUITextureManager::Initialize()
{
	m_pd3dDevice = g_XBoxGUI.GetD3DDevice();

	if(!m_pd3dDevice)
		return false;

	return true;
}

void CGUITextureManager::LoadTexture(string strFileName)
{
	// Checked if the texture is already loaded first
	for(int i = 0; i < (int)m_vecTextures.size(); i++)
	{
		CTexture* pGUITexture = NULL;
		pGUITexture = m_vecTextures[i];

		if(pGUITexture->GetTextureName() == strFileName)
			return;
	}

	LPDIRECT3DTEXTURE8 pD3DTexture = NULL;

	string strPath = "D:\\gui\\" + strFileName;
	D3DXCreateTextureFromFile(m_pd3dDevice, strPath.c_str(), &pD3DTexture);

	CTexture* pGUITexture = new CTexture(strFileName, pD3DTexture);
	m_vecTextures.push_back(pGUITexture);
}

LPDIRECT3DTEXTURE8 CGUITextureManager::GetTexture(std::string strFileName)
{
	for(int i = 0; i < (int)m_vecTextures.size(); i++)
	{
		CTexture* pGUITexture = NULL;
		pGUITexture = m_vecTextures[i];

		if(pGUITexture->GetTextureName() == strFileName)
			return pGUITexture->GetTexture();
	}

	return NULL;
}

void CGUITextureManager::ReleaseAllTextures()
{
	for(int i = 0; i < (int)m_vecTextures.size(); i++)
	{
		CTexture* pGUITexture = NULL;
		pGUITexture = m_vecTextures[i];

		pGUITexture->ReleaseTexture();

		delete pGUITexture;
	}
	
	m_vecTextures.clear();
}