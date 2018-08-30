#include "guiwindowmanager.h"
#include "guiwindowkeys.h"

#include "windows\guiwindowhome.h"
#include "windows\guiwindowingameconfig.h"

CGUIWindowManager::CGUIWindowManager()
{
	m_pActiveWindow = NULL;
}

CGUIWindowManager::~CGUIWindowManager()
{
}

bool CGUIWindowManager::InitWindows()
{
	// Create our windows
	CGUIWindow* pNewWindow = NULL;

	pNewWindow = new CGUIWindowHome(WINDOW_HOME, 02);
	m_vecWindows.push_back(pNewWindow);

	pNewWindow = new CGUIWindowInGameConfig(WINDOW_INGAME_CONFIG, 02);
	m_vecWindows.push_back(pNewWindow);

	// Now load them
	for(int i = 0; i < (int)m_vecWindows.size(); i++)
	{
		CGUIWindow* pWindow = NULL;
		pWindow = m_vecWindows[i];

		if(!pWindow->Load())
			return false;
	}

	return true;
}

void CGUIWindowManager::CleanupWindows()
{
	CGUIWindow* pWindow = NULL;

	for(int i = 0; i < (int)m_vecWindows.size(); i++)
	{
		pWindow = m_vecWindows[i];

		pWindow->Cleanup();

		delete pWindow;
		pWindow = NULL;
	}

	m_vecWindows.clear();
}

bool CGUIWindowManager::ActivateWindow(int iWindowID)
{
	for(int i = 0; i < (int)m_vecWindows.size(); i++)
	{
		CGUIWindow* pWindow = NULL;
		pWindow = m_vecWindows[i];

		if(pWindow->GetWindowID() == iWindowID)
		{
			m_pActiveWindow = pWindow;
			return true;
		}
	}
	return false;
}

bool CGUIWindowManager::OnKey(int iKey)
{
	if(m_pActiveWindow)
		return m_pActiveWindow->OnKey(iKey);

	return false;
}

bool CGUIWindowManager::OnMessage(CGUIMessage message)
{
	if(m_pActiveWindow)
		return m_pActiveWindow->OnMessage(message);

	return false;
}

void CGUIWindowManager::Render()
{
	if(m_pActiveWindow)
		m_pActiveWindow->Render();
}