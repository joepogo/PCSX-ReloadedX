#include "guiwindowglobalconfig.h"
#include "..\guiwindowkeys.h"
#include "..\xboxgui.h"

#include "..\controls\guicontrolimage.h"
#include "..\controls\guicontrollabel.h"

// Control(s)
#define CONTROL_BACKGROUND_IMAGE	01
#define CONTROL_WIP_LABEL			02

CGUIWindowGlobalConfig::CGUIWindowGlobalConfig(int iWindowID, int iDefaultControlID) 
: CGUIWindow(iWindowID, iDefaultControlID)
{
}

CGUIWindowGlobalConfig::~CGUIWindowGlobalConfig()
{
}

bool CGUIWindowGlobalConfig::Load()
{
	CGUIControl* pNewControl = NULL;

	// Determines render order

	pNewControl = new CGUIControlImage(CONTROL_BACKGROUND_IMAGE, GetWindowID(), 0, 0, 640, 480, "psxbg.jpg");
	m_vecControls.push_back(pNewControl);

	pNewControl = new CGUIControlLabel(CONTROL_WIP_LABEL, GetWindowID(), 480, 380, 100, 50, "font01", "Under Construction", D3DCOLOR_XRGB(255,255,0), 40);
	m_vecControls.push_back(pNewControl);	

	// TODO
	
	return CGUIWindow::Load();
}

bool CGUIWindowGlobalConfig::OnKey(int iKey)
{
	// Just return for now (under construction) // WIP
	g_XBoxGUI.m_GUIWindowManager.ActivateWindow(WINDOW_HOME);

	return CGUIWindow::OnKey(iKey);
}