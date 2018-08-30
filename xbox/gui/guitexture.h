#ifndef H_CGUITEXTURE
#define H_CGUITEXTURE

#include "gui_stdafx.h"
#include <string>

struct CUSTOMVERTEX
{
    FLOAT x, y, z , RHW;    // from the D3DFVF_XYZRHW flag
    FLOAT tx, ty;			// from the D3DFVF_TEX1 flag
};

class CGUITexture
{
public:
	CGUITexture(std::string strFileName);
	~CGUITexture();

	void AlocateResources();
	void Render(int iPosX, int iPosY, int iWidth, int iHeight);
	void FreeResources();

private:
	std::string m_strFilename;

	LPDIRECT3DDEVICE8			m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER8		m_pVertexBuffer;

	bool m_bResoucesAlocated;
};

#endif //H_CGUITEXTURE