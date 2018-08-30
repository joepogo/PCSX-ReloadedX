#ifndef H_CGUICONTROLLIST
#define H_CGUICONTROLLIST

#include "..\guicontrol.h"
#include <string>
#include <vector>

class CGUIListItem
{
public:
	CGUIListItem(std::string strName, int iID, bool bIsDirectory = false);
	~CGUIListItem();

	bool IsSelected() {return m_bSelected;};
	void Selected (bool bSelected) {m_bSelected = bSelected;};
	std::string GetName() {return m_strName;};
	int GetID(){return m_iID;};

private:
	int m_iID;
	std::string m_strName;
	bool m_bSelected;
	bool m_bIsDirectory;
};

class CGUIControlList : public CGUIControl
{
public:
	CGUIControlList(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight);
	~CGUIControlList();

	virtual void Render();
	virtual bool OnKey(int iKey);

	bool AddItem(CGUIListItem* pItem);
	CGUIListItem* GetSelectedItem();
	int GetSelectedID();
	void SetSlectedID(int iID);
	int GetSize();
	virtual void Cleanup();

private:
	std::vector <CGUIListItem*>m_vecItems;
};

#endif //H_CGUICONTROLLIST