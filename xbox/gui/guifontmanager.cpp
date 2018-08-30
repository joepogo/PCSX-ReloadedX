#include "guifontmanager.h"

CGUIFontManager::CGUIFontManager()
{
}

CGUIFontManager::~CGUIFontManager()
{
}

bool CGUIFontManager::InitFonts()
{
	CGUIFont* pNewFont = NULL;

	// Create the font(s)
	pNewFont = new CGUIFont("font01", "D:\\gui\\font01.ttf");
	m_vecFonts.push_back(pNewFont);

	// Now load them
	for(int i = 0; i < (int)m_vecFonts.size(); i++)
	{
		CGUIFont* pFont = NULL;
		pFont = m_vecFonts[i];

		pFont->Load();
	}

	return true;
}

void CGUIFontManager::CleanupFonts()
{
	for(int i = 0; i < (int)m_vecFonts.size(); i++)
	{
		CGUIFont* pFont = NULL;
		pFont = m_vecFonts[i];

		pFont->FreeResources();

		delete pFont;
	}
	
	m_vecFonts.clear();
}

CGUIFont* CGUIFontManager::GetFont(std::string strFontName)
{
	for(int i = 0; i < (int)m_vecFonts.size(); i++)
	{
		CGUIFont* pFont = NULL;
		pFont = m_vecFonts[i];
		
		if(pFont->GetFontName() == strFontName)
			return pFont;
	}

	return NULL;
}