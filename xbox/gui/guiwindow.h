#ifndef H_CGUIWINDOW
#define H_CGUIWINDOW

#include "guicontrol.h"

#include <vector>

class CGUIWindow
{
public:
	CGUIWindow(int iWindowID, int iDefaultControlID);
	~CGUIWindow();

	int GetWindowID() {return m_iWindowID;};
	
	virtual bool Load();
	virtual void Cleanup();
	virtual bool OnKey(int iKey);
	virtual bool OnMessage(CGUIMessage message);
	virtual void Render();

	CGUIControl* GetControl(int iControlID);
	CGUIControl* GetFocusedControl();

protected:
	int m_iWindowID;
	int m_iDefaultCOntrolID;
	std::vector <CGUIControl*> m_vecControls;
};

#endif //H_CGUIWINDOW
