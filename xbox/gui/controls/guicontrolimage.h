#ifndef H_CGUICONTROLIMAGE
#define H_CGUICONTROLIMAGE

#include "..\guicontrol.h"

#include "..\gui_stdafx.h"
#include <string>

struct CUSTOM_IMAGE_VERTEX
{
    FLOAT x, y, z , RHW;
    FLOAT tx, ty;
};

class CGUIControlImage : public CGUIControl
{
public:
	CGUIControlImage(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strFileName);
	~CGUIControlImage();

	virtual bool Load();
	virtual void Cleanup();
	virtual void Render();

private:
	std::string m_strFilename;

	LPDIRECT3DDEVICE8			m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER8		m_pVertexBuffer;
};

#endif //H_CGUICONTROLIMAGE