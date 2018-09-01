#ifndef H_CGUICONTROLLABEL
#define H_CGUICONTROLLABEL

#include "..\guicontrol.h"
#include "..\guifont.h"
#include <string>

class CGUIControlLabel : public CGUIControl
{
public:
	CGUIControlLabel(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strFont, std::string strText, DWORD dwColor, unsigned int iSize = 32);
	~CGUIControlLabel();
	
	virtual bool Load();
	virtual void Cleanup();
	virtual void Render();

	void Render(DWORD dwColor);

private:
	std::string m_strText;
	std::string m_strFont;
	DWORD m_dwColor;
	CGUIFont* m_pFont;
	unsigned int m_iSize;
};

#endif //H_CGUICONTROLLABEL