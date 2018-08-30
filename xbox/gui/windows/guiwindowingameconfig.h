#ifndef H_CGUIWINDOW_INGAME_CONFIG
#define H_CGUIWINDOW_INGAME_CONFIG

#include "..\guiwindow.h"

class CGUIWindowInGameConfig : public CGUIWindow
{
public:
	CGUIWindowInGameConfig(int iWindowID, int iDefaultControlID);
	virtual ~CGUIWindowInGameConfig();

	virtual bool Load();
private:
};

#endif //H_CGUIWINDOW_INGAME_CONFIG
