#include "guiwindowhome.h"
#include "..\utils\stringutils.h"
#include "..\..\..\libpcsxcore\system.h"
#include "..\..\xbox.h"

#include "..\controls\guicontrollist.h"
#include "..\controls\guicontrollabel.h"
#include "..\controls\guicontrolimage.h"

using namespace std;

#define PATH "D:\\psxcds\\" // TODO: Get from config

// Control(s)
#define CONTROL_BACKGROUND_IMAGE	01
#define CONTROL_PSXCDIMAGE_LIST		02
#define CONTROL_HEADER_LABEL		03
#define CONTROL_SUB_HEADER_LABEL	04


CGUIWindowHome::CGUIWindowHome(int iWindowID, int iDefaultControlID) 
: CGUIWindow(iWindowID, iDefaultControlID)
{
}

CGUIWindowHome::~CGUIWindowHome()
{
}

bool CGUIWindowHome::Load()
{
	CGUIControl* pNewControl = NULL;

	// Determines render order

	pNewControl = new CGUIControlImage(CONTROL_BACKGROUND_IMAGE, GetWindowID(), 0, 0, 640, 480, "psxbg.jpg");
	m_vecControls.push_back(pNewControl);

	// TODO: 10% tv safe zone to compensate for overscan
	// TODO: Scale coordinates with resolution (HD modes)
	pNewControl = new CGUIControlList(CONTROL_PSXCDIMAGE_LIST, GetWindowID(), 64, 128, 250, 420);
	m_vecControls.push_back(pNewControl);

	pNewControl = new CGUIControlLabel(CONTROL_HEADER_LABEL, GetWindowID(), 430, 40, 100, 50, "PCSX-ReloadedX - Pre-Beta v1.2", "font01", D3DCOLOR_XRGB(255,255,0), 40);
	m_vecControls.push_back(pNewControl);

	pNewControl = new CGUIControlLabel(CONTROL_SUB_HEADER_LABEL, GetWindowID(), 470, 80, 100, 50, "Images in the D:\\PSXCDS\\*.cue,*.iso folder", "font01", D3DCOLOR_XRGB(255,255,0), 25);
	m_vecControls.push_back(pNewControl);

	// Populate the list with images
	if(!GetPSXImages())
		SysMessage("Unable to load CD Images.\n");
	
	return CGUIWindow::Load();
}

bool CGUIWindowHome::OnMessage(CGUIMessage message)
{
	switch(message.GetMessage())
	{
		case GUI_MSG_CLICKED:
		{
			if(message.GetSenderID() == CONTROL_PSXCDIMAGE_LIST) // A PSX CD image has been clicked
			{
				CGUIControlList* pCtrlPSXCDList = (CGUIControlList*)GetControl(CONTROL_PSXCDIMAGE_LIST);

				CGUIListItem* pItem = pCtrlPSXCDList->GetSelectedItem();

				if(pItem)
				{
					string strPath = PATH + pItem->GetName();
					RunCommand(ID_FILE_RUN_ISO, strPath.c_str());

					return true;
				}
			}
		}
		break;
	}

	return CGUIWindow::OnMessage(message);
}

bool CGUIWindowHome::GetPSXImages()
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;

	string strPath = PATH;
	string strRoot = strPath;

	memset(&wfd, 0, sizeof(wfd));
	CStringUtils::AddSlashAtEnd(strRoot);

	string strSearchMask = strRoot;
	strSearchMask += "*.*";

	hFind = FindFirstFile(strSearchMask.c_str(), &wfd);

	if (INVALID_HANDLE_VALUE == hFind) 
		return false;

	CGUIControlList* pControlPSXCDImages = NULL;
	pControlPSXCDImages = (CGUIControlList*)GetControl(CONTROL_PSXCDIMAGE_LIST);

	if(!pControlPSXCDImages)
		return false;

	int iID = 0;

	// Get all the files in the directory with some info about them
	do
	{
		if (wfd.cFileName[0] != 0)
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// TODO: Get sub-directories working

/*				iID++;
				CGUIListItem* pNewItem = new CGUIListItem(wfd.cFileName, iID, true);
				pNewItem->IsFolder = true;
				pControlPSXCDImages->AddItem(pNewItem);

*/			}
			else
			{
				size_t len = strlen(wfd.cFileName);

				// Force the extensions to lower case
				for(int i = len -4; wfd.cFileName[i]; i++)
					wfd.cFileName[i] = tolower(wfd.cFileName[i]);

				if (len >= 4 && !strcmp(wfd.cFileName + len - 4, ".cue") 
							 || !strcmp(wfd.cFileName + len - 4, ".iso")) // TODO: Check for other image extensions
				{
					iID++;

					CGUIListItem* pNewItem = new CGUIListItem(wfd.cFileName, iID); //Released in CGUIListItem::Cleanup()	
					pControlPSXCDImages->AddItem(pNewItem);

					if(iID == 1)
						pNewItem->Selected(true);
				}
			}
		}
	}
	while (FindNextFile(hFind, &wfd) != 0);

	FindClose(hFind);

	return true;
}