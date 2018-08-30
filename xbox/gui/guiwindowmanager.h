#ifndef H_CGUIWINDOWMANAGER
#define H_CGUIWINDOWMANAGER

#include "guiwindow.h"
#include <vector>

class CGUIWindowManager
{
public:
	CGUIWindowManager();
	~CGUIWindowManager();

	bool InitWindows();
	void CleanupWindows();

	bool ActivateWindow(int iWindowID);
	bool OnKey(int iKey);
	bool OnMessage(CGUIMessage message);
	void Render();

private:
	std::vector <CGUIWindow*>m_vecWindows;
	CGUIWindow* m_pActiveWindow;
};

#endif //H_CGUIWINDOWMANAGER