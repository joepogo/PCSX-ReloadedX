#ifndef H_CGUIFONTMANAGER
#define H_CGUIFONTMANAGER

#include "guifont.h"
#include <vector>

class CGUIFontManager
{
public:
	CGUIFontManager();
	~CGUIFontManager();

	bool InitFonts();
	void CleanupFonts();

	CGUIFont* GetFont(std::string strFontName);

private:
	std::vector <CGUIFont*>m_vecFonts;
};

#endif //H_CGUIFONTMANAGER