#ifndef H_CGUIWINDOW_HOME
#define H_CGUIWINDOW_HOME

#include "..\guiwindow.h"

class CGUIWindowHome : public CGUIWindow
{
public:
	CGUIWindowHome(int iWindowID, int iDefaultControlID);
	virtual ~CGUIWindowHome();

	virtual bool Load();
	virtual bool OnMessage(CGUIMessage message);

private:
	bool GetPSXImages();
};

#endif //H_CGUIWINDOW_HOME
