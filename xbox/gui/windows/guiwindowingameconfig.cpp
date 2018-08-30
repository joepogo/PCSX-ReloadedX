#include "guiwindowingameconfig.h"
#include "..\controls\guicontrolimage.h"

// Control(s)
#define CONTROL_BACKGROUND_IMAGE	01

CGUIWindowInGameConfig::CGUIWindowInGameConfig(int iWindowID, int iDefaultControlID) 
: CGUIWindow(iWindowID, iDefaultControlID)
{
	// TODO
}

CGUIWindowInGameConfig::~CGUIWindowInGameConfig()
{
	// TODO
}

bool CGUIWindowInGameConfig::Load()
{
	CGUIControl* pNewControl = NULL;

	// Determines render order

	pNewControl = new CGUIControlImage(CONTROL_BACKGROUND_IMAGE, GetWindowID(), 0, 0, 640, 480, "psxbg.jpg");
	m_vecControls.push_back(pNewControl);

	// Work in progress
	// Need all game configs listed

	return CGUIWindow::Load();
}