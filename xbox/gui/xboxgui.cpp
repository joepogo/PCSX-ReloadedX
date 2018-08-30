#include "xboxgui.h"
#include "xboxguiexport.h"
#include "guiwindowkeys.h"
#include "..\..\libpcsxcore\system.h"
#include "..\input\sysxboxinput.h"

CXBoxGUI g_XBoxGUI;

CXBoxGUI::CXBoxGUI()
{
	m_bGUIActive = false;
	m_bGUIStatesCaptured = false;
	m_bInGameStatesCaptured = false;
	m_surfPreview = NULL;
	m_iStartWindow = WINDOW_HOME;
}

CXBoxGUI::~CXBoxGUI()
{
}

bool CXBoxGUI::Initialize()
{
	if(!m_pD3DDevice)
	{
		SysMessage("Can't start the GUI, no D3D device.\n");
		return false;
	}

	if(!m_bGUIStatesCaptured)
	{
		m_bGUIStatesCaptured = true;
		m_pD3DDevice->CreateStateBlock(D3DSBT_ALL, &m_dwGUIRenderStates);
	}
	else
	{
		m_pD3DDevice->GetBackBuffer(-1, D3DBACKBUFFER_TYPE_MONO, &m_surfPreview);

		m_pD3DDevice->CreateStateBlock(D3DSBT_ALL, &m_dwInGameRenderStates);
		m_bInGameStatesCaptured = true;
	}

	m_GUITextureManager.Initialize();
	m_GUIFontManager.InitFonts();
	m_GUIWindowManager.InitWindows();

	m_GUIWindowManager.ActivateWindow(m_iStartWindow);
	
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pD3DDevice->ApplyStateBlock(m_dwGUIRenderStates);

	m_bGUIActive = true;

	return true;
}

void CXBoxGUI::Run()
{
	int iKey;

	if(GetGUIXBoxInput(&iKey))
		m_GUIWindowManager.OnKey(iKey);

	Render();
}

void CXBoxGUI::Render()
{
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	m_pD3DDevice->BeginScene();
			
	m_GUIWindowManager.Render();

	m_pD3DDevice->EndScene();
	m_pD3DDevice->BlockUntilVerticalBlank();     
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

bool CXBoxGUI::Close()
{
	m_GUIFontManager.CleanupFonts();
	m_GUIWindowManager.CleanupWindows();
	m_GUITextureManager.ReleaseAllTextures();

	if(m_bInGameStatesCaptured)
		m_pD3DDevice->ApplyStateBlock(m_dwInGameRenderStates);

	// Release the preview surface if we have one
	if(m_surfPreview)
	{
		m_surfPreview->Release();
		m_surfPreview = NULL;
	}

	m_bGUIActive = false;

	return true;
}

D3DSurface* CXBoxGUI::GetPreviewSurface() //TODO: Pass by reference and return a bool
{
	// Check if we have an in-game capture yet
	if(m_bInGameStatesCaptured)
		return m_surfPreview;

	return NULL;
}

void CXBoxGUI::SetStartWindow(int iStartWindow)
{
	// Validity is checked in CWindowManager
	m_iStartWindow = iStartWindow;
}

//==================================================================================

int InitializeXBoxGUI()
{
	return g_XBoxGUI.Initialize();
}

void RunXBoxGUI()
{
	g_XBoxGUI.Run();
}

int CloseXBoxGUI()
{
	return g_XBoxGUI.Close();
}

void SetGUID3DDevice(LPDIRECT3DDEVICE8 pD3DDevice)
{
	g_XBoxGUI.SetD3DDevice(pD3DDevice);
}

int IsXBoxGUIActive()
{
	return g_XBoxGUI.IsGUIActive();
}

void SetXBoxGUIStartWindow(int iStartWindow)
{
	g_XBoxGUI.SetStartWindow(iStartWindow);
}