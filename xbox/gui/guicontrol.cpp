#include "guicontrol.h"

CGUIControl::CGUIControl(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight)
{
	m_iID = iControlID;
	m_iParentID = iWindowID;
	m_iPosX = iPosX;
	m_iPosY = iPosY;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_bHasFocus = false;
}

CGUIControl::~CGUIControl()
{
}

bool CGUIControl::Load()
{
	return true;
}

void CGUIControl::Cleanup()
{
}

void CGUIControl::Render()
{
}

bool CGUIControl::OnKey(int iKey)
{
	// Not processed in the parents
	return false;
}

bool CGUIControl::OnMessage(CGUIMessage message)
{
	// Not processed in the parents
	return false;
}