#ifndef H_CGUICONTROL
#define H_CGUICONTROL

#include "guimessage.h"

#define NAVIGATION_NULL 99

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

	void SetMovement(int iUp, int iDown, int iLeft, int iRight);
	void SetUp(int iUp){m_iControlUp = iUp;};
	void SetDown(int iDown){m_iControlDown = iDown;};
	void SetLeft(int iLeft){m_iControlLeft = iLeft;};
	void SetRight(int iRight){m_iControlRight = iRight;};

protected:
	void OnUp();
	void OnDown();
	void OnLeft();
	void OnRight();

	int m_iID;
	int m_iParentID;
	int m_iPosX;
	int m_iPosY;
	int m_iWidth;
	int m_iHeight;
	bool m_bHasFocus;
	bool m_bResoucesAlocated;
	int m_iControlUp;
	int m_iControlDown;
	int m_iControlLeft;
	int m_iControlRight;
};

#endif //H_CGUICONTROL
