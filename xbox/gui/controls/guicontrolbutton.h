#ifndef H_CGUICONTROLBUTTON
#define H_CGUICONTROLBUTTON

#include "..\guicontrol.h"
#include "..\gui_stdafx.h"

#include "guicontrollabel.h"

#include <string>

class CGUIControlButton : public CGUIControl
{
public:
	CGUIControlButton(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strFont, std::string strText, DWORD dwColor, DWORD dwSelctedColor, unsigned int iSize);
	CGUIControlButton(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strFont, std::string strText, DWORD dwColor, DWORD dwSelctedColor, unsigned int iSize, int iLinkedWindo);

	~CGUIControlButton();

	virtual bool Load();
	virtual void Cleanup();
	virtual void Render();
	virtual bool OnKey(int iKey);

	void OnClick();

private:
	CGUIControlLabel m_label;
	DWORD m_dwColor;
	DWORD m_dwSelectedColor;
	int m_iLinkedWindow;
};

#endif //H_CGUICONTROLBUTTON