#include "guicontrolimage.h"
#include "..\xboxgui.h"

using namespace std;

CGUIControlImage::CGUIControlImage(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strFileName) 
: CGUIControl(iControlID, iWindowID, iPosX, iPosY, iWidth, iHeight), m_Image(strFileName)
{
}

CGUIControlImage::~CGUIControlImage()
{
}

bool CGUIControlImage::Load()
{
	m_Image.AlocateResources();

	return true;
}

void CGUIControlImage::Cleanup()
{
	m_Image.FreeResources();
}

void CGUIControlImage::Render()
{
	m_Image.Render(m_iPosX, m_iPosY, m_iWidth, m_iHeight);
}