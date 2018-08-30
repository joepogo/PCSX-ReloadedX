#ifndef H_CGUICONTROL
#define H_CGUICONTROL

#include "guimessage.h"

class CGUIControl
{
public:
	CGUIControl(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight);
	~CGUIControl();

	virtual bool Load();
	virtual void Cleanup();
	virtual void Render();
	virtual bool OnKey(int iKey);
	virtual bool OnMessage(CGUIMessage message);

	int GetID() { return m_iID; };
	int GetParentID() { return m_iParentID; };
	void SetFocus(bool bFocus) { m_bHasFocus = bFocus; };
	bool HasFocus() { return m_bHasFocus; };

protected:
	int m_iID;
	int m_iParentID;
	int m_iPosX;
	int m_iPosY;
	int m_iWidth;
	int m_iHeight;
	bool m_bHasFocus;
};

#endif //H_CGUICONTROL
