#ifndef H_CGUICONTROLIMAGE
#define H_CGUICONTROLIMAGE

#include "..\guicontrol.h"
#include "..\guitexture.h"

#include <string>

class CGUIControlImage : public CGUIControl
{
public:
	CGUIControlImage(int iControlID, int iWindowID, int iPosX, int iPosY, int iWidth, int iHeight, std::string strFileName);
	~CGUIControlImage();

	virtual bool Load();
	virtual void Cleanup();
	virtual void Render();

private:
	CGUITexture m_Image;
};

#endif //H_CGUICONTROLIMAGE