#include "guicontrollabel.h"
#include "..\xboxgui.h"

using namespace std;

CGUIControlLabel::CGUIControlLabel(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strText, std::string strFont, DWORD dwColor, unsigned int iSize) 
: CGUIControl(iControlID, iWindowID, iPosX, iPosY, iWidth, iHeight)
{
	m_strText = strText;
	m_strFont = strFont;
	m_dwColor = dwColor;
	m_pFont = NULL;
	m_iSize = iSize;
}

CGUIControlLabel::~CGUIControlLabel()
{
}

bool CGUIControlLabel::Load()
{
	m_pFont = g_XBoxGUI.m_GUIFontManager.GetFont(m_strFont);

	if(!m_pFont)
		return false;

	return CGUIControl::Load();
}

void CGUIControlLabel::Cleanup()
{
	CGUIControl::Cleanup();
}

void CGUIControlLabel::Render()
{
	if(m_pFont)
		m_pFont->Render(m_iPosX, m_iPosY, m_iSize, m_dwColor, m_strText);

	CGUIControl::Render();
}