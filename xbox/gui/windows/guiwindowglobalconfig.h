#ifndef H_CGUIWINDOW_GLOBALCONFIG
#define H_CGUIWINDOW_GLOBALCONFIG

#include "..\guiwindow.h"

class CGUIWindowGlobalConfig : public CGUIWindow
{
public:
	CGUIWindowGlobalConfig(int iWindowID, int iDefaultControlID);
	virtual ~CGUIWindowGlobalConfig();

	virtual bool Load();
	virtual bool OnKey(int iKey);

private:
};

#endif //H_CGUIWINDOW_GLOBALCONFIG
