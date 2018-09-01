#include "guicontrolimage.h"
#include "..\xboxgui.h"

using namespace std;

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_TEX1)

CGUIControlImage::CGUIControlImage(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strFileName) 
: CGUIControl(iControlID, iWindowID, iPosX, iPosY, iWidth, iHeight)
{
	m_pd3dDevice = NULL;
	m_pVertexBuffer = NULL;
	
	m_strFilename = strFileName;
}

CGUIControlImage::~CGUIControlImage()
{
}

bool CGUIControlImage::Load()
{
	if(m_bResoucesAlocated)
		return true;

	m_pd3dDevice = g_XBoxGUI.GetD3DDevice();

	if(!m_pd3dDevice)
		return false;

	g_XBoxGUI.m_GUITextureManager.LoadTexture(m_strFilename);

	// Create the vertex buffer from our device
	m_pd3dDevice->CreateVertexBuffer(4 * sizeof(CUSTOM_IMAGE_VERTEX), 0, CUSTOMFVF, D3DPOOL_DEFAULT, &m_pVertexBuffer);

	m_bResoucesAlocated = true;

	return CGUIControl::Load();
}

void CGUIControlImage::Cleanup()
{
	m_bResoucesAlocated = false;
    m_pVertexBuffer->Release();
}

void CGUIControlImage::Render()
{
	VOID* pVertices;

	CUSTOM_IMAGE_VERTEX cvVertices[] =
    {
        { (FLOAT)m_iPosX, (FLOAT)m_iPosY, 0.5f, 1.0f, 0, 0, },
        { (FLOAT)m_iPosX+m_iWidth, (FLOAT)m_iPosY, 0.5f, 1.0f, 1, 0, },
        { (FLOAT)m_iPosX, (FLOAT)m_iHeight+m_iPosY, 0.5f, 1.0f, 0, 1, },
		{ (FLOAT)m_iPosX+(FLOAT)m_iWidth, (FLOAT)m_iPosY+m_iHeight, 0.5f, 1.0f, 1, 1, },
	};

    // Get a pointer to the vertex buffer vertices and lock the vertex buffer
    m_pVertexBuffer->Lock(0, sizeof(cvVertices), (BYTE**)&pVertices, 0);

    // Copy our stored vertices values into the vertex buffer
    memcpy(pVertices, cvVertices, sizeof(cvVertices));

    // Unlock the vertex buffer
    m_pVertexBuffer->Unlock();

    m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, sizeof(CUSTOM_IMAGE_VERTEX));
    m_pd3dDevice->SetVertexShader(CUSTOMFVF);

	// Set our texture
	m_pd3dDevice->SetTexture(0, g_XBoxGUI.m_GUITextureManager.GetTexture(m_strFilename));

	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	m_pd3dDevice->SetTexture(0, 0);
}