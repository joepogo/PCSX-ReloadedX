#include "guiwindow.h"
#include "guifontmanager.h"

CGUIWindow::CGUIWindow(int iWindowID, int iDefaultControlID)
{
	m_iWindowID = iWindowID;
	m_iDefaultCOntrolID = iDefaultControlID;
}

CGUIWindow::~CGUIWindow()
{
}

bool CGUIWindow::Load()
{
	for(int i = 0; i < (int)m_vecControls.size(); i++)
	{
		CGUIControl* pControl = NULL;
		pControl = m_vecControls[i];

		pControl->Load();

		if(m_iDefaultCOntrolID == pControl->GetID())
			pControl->SetFocus(true);
	}

	return true;
}

void CGUIWindow::Cleanup()
{
	for(int i = 0; i < (int)m_vecControls.size(); i++)
	{
		CGUIControl* pControl = NULL;
		pControl = m_vecControls[i];

		pControl->Cleanup();

		delete pControl;
	}

	m_vecControls.clear();
}

bool CGUIWindow::OnKey(int iKey)
{
	CGUIControl* pControl = GetFocusedControl();
	
	if(pControl)
		 return pControl->OnKey(iKey);

	return false;
}

bool CGUIWindow::OnMessage(CGUIMessage message)
{
	bool handled = false;

	for(int i = 0; i < (int)m_vecControls.size(); i++)
	{
		CGUIControl* pControl = NULL;
		pControl = m_vecControls[i];

		if(pControl->OnMessage(message))
			handled = true;
	}

	return handled;
}

void CGUIWindow::Render()
{
	for(int i = 0; i < (int)m_vecControls.size(); i++)
	{
		CGUIControl* pControl = NULL;
		pControl = m_vecControls[i];

		pControl->Render();
	}
}

CGUIControl* CGUIWindow::GetControl(int iControlID)
{
	for(int i = 0; i < (int)m_vecControls.size(); i++)
	{
		CGUIControl* pControl = NULL;
		pControl = m_vecControls[i];

		if(pControl->GetID() == iControlID)
			return pControl;
	}

	return NULL;
}

CGUIControl* CGUIWindow::GetFocusedControl()
{
	for(int i = 0; i < (int)m_vecControls.size(); i++)
	{
		CGUIControl* pControl = NULL;
		pControl = m_vecControls[i];

		if(pControl->HasFocus())
			return pControl;
	}

	return NULL;
}