#ifndef H_CGUIFONT
#define H_CGUIFONT

#include "gui_stdafx.h"

#define XFONT_TRUETYPE
#include <xfont.h>
#include <stdio.h>
#include <string>

class CGUIFont
{
public:
	CGUIFont(std::string strFontName, std::string strFilename);
	~CGUIFont();

	bool Load();
	std::string GetFontName(){ return m_sFontName; };
	void AlocateResources();
	void Render(int iPosX, int iPosY, unsigned int iSize, D3DCOLOR Color, std::string strText);
	void FreeResources();

private:
	XFONT*              m_pFont; 
	LPDIRECT3DDEVICE8	m_pd3dDevice;
	LPDIRECT3DSURFACE8  m_pBackBuffer;

	std::string			m_sFontFile;
	std::string			m_sFontName;
	bool				m_bResoucesAlocated;
};

#endif //H_CGUIFONT