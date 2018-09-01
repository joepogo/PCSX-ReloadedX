#include "guicontrolbutton.h"
#include "..\guiwindowkeys.h"
#include "..\xboxgui.h"
#include "..\..\input\sysxboxinput.h"

CGUIControlButton::CGUIControlButton(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strFont, std::string strText, DWORD dwColor, DWORD dwSelctedColor, unsigned int iSize) 
: CGUIControl(iControlID, iWindowID, iPosX, iPosY, iWidth, iHeight)
, m_label(iControlID, iWindowID, iPosX, iPosY, iWidth, iHeight, strFont, strText, dwColor, iSize)
{
	m_dwColor = dwColor;
	m_dwSelectedColor = dwSelctedColor;
	m_iLinkedWindow = WINDOW_INVALID;
}

CGUIControlButton::CGUIControlButton(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strFont, std::string strText, DWORD dwColor, DWORD dwSelctedColor, unsigned int iSize, int iLinkedWindow) 
: CGUIControl(iControlID, iWindowID, iPosX, iPosY, iWidth, iHeight)
, m_label(iControlID, iWindowID, iPosX, iPosY, iWidth, iHeight, strFont, strText, dwColor, iSize)
{
	m_dwColor = dwColor;
	m_dwSelectedColor = dwSelctedColor;
	m_iLinkedWindow = iLinkedWindow;
}

CGUIControlButton::~CGUIControlButton()
{
}

bool CGUIControlButton::Load()
{
	m_label.Load();

	return CGUIControl::Load();
}

void CGUIControlButton::Cleanup()
{
	m_label.Cleanup();

	CGUIControl::Cleanup();
}

void CGUIControlButton::Render()
{
	if(m_bHasFocus)
		m_label.Render(m_dwSelectedColor);
	else
		m_label.Render(m_dwColor);

	CGUIControl::Render();
}

bool CGUIControlButton::OnKey(int iKey)
{
	if(iKey == K_XBOX_A)
		OnClick();

	if(iKey == K_XBOX_A)
	{
		CGUIMessage msg(GUI_MSG_CLICKED, GetParentID(), GetID());
		g_XBoxGUI.m_GUIWindowManager.OnMessage(msg);
	}

	return CGUIControl::OnKey(iKey);
}

void CGUIControlButton::OnClick()
{
	if(m_iLinkedWindow != WINDOW_INVALID)
		g_XBoxGUI.m_GUIWindowManager.ActivateWindow(m_iLinkedWindow);
}