#include "guicontrollist.h"
#include "..\xboxgui.h"
#include "..\..\input\sysxboxinput.h"

using namespace std;

#define LINE_SPACING 30

CGUIListItem::CGUIListItem(std::string strName, int iID, bool bIsDirectory)
{
	m_strName = strName;
	m_iID = iID;
	m_bSelected = false;
	m_bIsDirectory = bIsDirectory;
}

CGUIListItem::~CGUIListItem()
{
}

CGUIControlList::CGUIControlList(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight)
: CGUIControl(iControlID, iWindowID, iPosX, iPosY, iWidth, iHeight)
{
}

CGUIControlList::~CGUIControlList()
{
}

void CGUIControlList::Render()
{
	int iYPos = m_iPosY;

	for(int i = 0; i < (int)m_vecItems.size(); i++)
	{
		CGUIListItem* pListItem = NULL;
		pListItem = m_vecItems[i];

		CGUIFont* pFont = g_XBoxGUI.m_GUIFontManager.GetFont("font01");

		if(pFont)
		{
			if(pListItem->IsSelected() && HasFocus())
				pFont->Render(m_iPosX, iYPos, 32, D3DCOLOR_XRGB(255,0,0), pListItem->GetName());
			else
				pFont->Render(m_iPosX, iYPos, 32, D3DCOLOR_XRGB(0,255,0), pListItem->GetName());
		}

		iYPos += LINE_SPACING;
	}

	CGUIControl::Render();
}

bool CGUIControlList::OnKey(int iKey)
{
	if(iKey == K_XBOX_DPAD_DOWN)
	{
			int iID = GetSelectedID();

			if(GetSize() > iID)
			{
				iID++;

				SetSlectedID(iID);

				return true;
			}
	}

	if(iKey == K_XBOX_DPAD_UP)
	{
			int iID = GetSelectedID();

			if(iID > 1)
			{
				iID--;

				SetSlectedID(iID);

				return true;
			}
	}

	if(iKey == K_XBOX_A)
	{
		CGUIMessage msg(GUI_MSG_CLICKED, GetParentID(), GetID());
		g_XBoxGUI.m_GUIWindowManager.OnMessage(msg);
	}

	return CGUIControl::OnKey(iKey);
}

bool CGUIControlList::AddItem(CGUIListItem* pItem)
{
	m_vecItems.push_back(pItem);

	return true;
}

CGUIListItem* CGUIControlList::GetSelectedItem()
{
	for(int i = 0; i < (int)m_vecItems.size(); i++)
	{
		CGUIListItem* pListItem = NULL;
		pListItem = m_vecItems[i];

		if(pListItem->IsSelected())
			return pListItem;
	}
	
	return NULL;
}

int CGUIControlList::GetSelectedID()
{
	for(int i = 0; i < (int)m_vecItems.size(); i++)
	{
		CGUIListItem* pListItem = NULL;
		pListItem = m_vecItems[i];

		if(pListItem->IsSelected())
			return pListItem->GetID();
	}
	
	return 99;
}

void CGUIControlList::SetSlectedID(int iID)
{
	// De-select the current item
	CGUIListItem* pItem = GetSelectedItem();

	if(pItem)
		pItem->Selected(false);

	// Select the new item
	for(int i = 0; i < (int)m_vecItems.size(); i++)
	{
		CGUIListItem* pListItem = NULL;
		pListItem = m_vecItems[i];

		if(pListItem->GetID() == iID)
			pListItem->Selected(true);
	}
	
	return;
}

int CGUIControlList::GetSize()
{
	return m_vecItems.size();
}

void CGUIControlList::Cleanup()
{
	for(int i = 0; i < (int)m_vecItems.size(); i++)
	{
		CGUIListItem* pListItem = NULL;
		pListItem = m_vecItems[i];

		if(pListItem)
			delete pListItem;
	}

	m_vecItems.clear();

	CGUIControl::Cleanup();
}