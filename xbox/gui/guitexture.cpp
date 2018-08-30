#include "guitexture.h"
#include "xboxgui.h"
#include "guitexturemanager.h"

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_TEX1)

CGUITexture::CGUITexture(std::string strFileName)
{
	m_pd3dDevice = NULL;
	m_pVertexBuffer = NULL;
	
	m_strFilename = strFileName;
	m_bResoucesAlocated = false;
}

CGUITexture::~CGUITexture()
{
}

void CGUITexture::AlocateResources()
{
	if(m_bResoucesAlocated)
		return;

	m_pd3dDevice = g_XBoxGUI.GetD3DDevice();

	if(!m_pd3dDevice)
		return;

	g_XBoxGUI.m_GUITextureManager.LoadTexture(m_strFilename);

	// Create the vertex buffer from our device
	m_pd3dDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_DEFAULT, &m_pVertexBuffer);

	m_bResoucesAlocated = true;
}

void CGUITexture::Render(int iPosX, int iPosY, int iWidth, int iHeight)
{
	VOID* pVertices;

	CUSTOMVERTEX cvVertices[] =
    {
        { (FLOAT)iPosX, (FLOAT)iPosY, 0.5f, 1.0f, 0, 0, },
        { (FLOAT)iPosX+iWidth, (FLOAT)iPosY, 0.5f, 1.0f, 1, 0, },
        { (FLOAT)iPosX, (FLOAT)iHeight+iPosY, 0.5f, 1.0f, 0, 1, },
		{ (FLOAT)iPosX+(FLOAT)iWidth, (FLOAT)iPosY+iHeight, 0.5f, 1.0f, 1, 1, },
	};

    // Get a pointer to the vertex buffer vertices and lock the vertex buffer
    m_pVertexBuffer->Lock(0, sizeof(cvVertices), (BYTE**)&pVertices, 0);

    // Copy our stored vertices values into the vertex buffer
    memcpy(pVertices, cvVertices, sizeof(cvVertices));

    // Unlock the vertex buffer
    m_pVertexBuffer->Unlock();

    m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, sizeof(CUSTOMVERTEX));
    m_pd3dDevice->SetVertexShader(CUSTOMFVF);

	// Set our texture
	m_pd3dDevice->SetTexture(0, g_XBoxGUI.m_GUITextureManager.GetTexture(m_strFilename));

	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void CGUITexture::FreeResources()
{
	m_bResoucesAlocated = false;
    m_pVertexBuffer->Release();
}