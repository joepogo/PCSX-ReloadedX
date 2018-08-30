#ifndef H_XBOXGUI
#define H_XBOXGUI

#include "gui_stdafx.h"
#include "guifontmanager.h"
#include "guiwindowmanager.h"
#include "guitexturemanager.h"

class CXBoxGUI
{
public:
	CXBoxGUI();
	~CXBoxGUI();

	bool Initialize();
	void Run();
	void Render();
	bool Close();

	bool IsGUIActive() { return m_bGUIActive; };

	void SetD3DDevice(LPDIRECT3DDEVICE8 pD3DDevice) { m_pD3DDevice = pD3DDevice; };
	LPDIRECT3DDEVICE8 GetD3DDevice() { return m_pD3DDevice; };

	D3DSurface* GetPreviewSurface();

	void SetStartWindow(int iStartWindow);

	CGUIFontManager		m_GUIFontManager;
	CGUIWindowManager	m_GUIWindowManager;
	CGUITextureManager  m_GUITextureManager;

private:
	LPDIRECT3DDEVICE8 m_pD3DDevice;
	bool m_bGUIActive;

	DWORD m_dwGUIRenderStates;
	DWORD m_dwInGameRenderStates;
	bool m_bGUIStatesCaptured;
	bool m_bInGameStatesCaptured;

	LPDIRECT3DSURFACE8 m_surfPreview;
	int m_iStartWindow;
};

extern CXBoxGUI g_XBoxGUI;

#endif //H_XBOXGUI