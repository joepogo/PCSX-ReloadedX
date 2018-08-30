#include "guifont.h"
#include "xboxgui.h"
#include "utils\stringutils.h"

using namespace std;

CGUIFont::CGUIFont(std::string strFontName, std::string strFilename)
{
	m_pd3dDevice = NULL;
	m_pFont = NULL; 
	m_pBackBuffer = NULL;

	m_sFontName = strFontName;
	m_sFontFile = strFilename;

	m_bResoucesAlocated = false;
}

CGUIFont::~CGUIFont()
{
}

bool CGUIFont::Load()
{
	m_pd3dDevice = g_XBoxGUI.GetD3DDevice();

	AlocateResources();

	return true;
}

void CGUIFont::AlocateResources()
{
	if(m_bResoucesAlocated)
		return;

	if(!m_pd3dDevice)
		return;
#if 1
	// Convert to wide string
	std::string strTmp = m_sFontFile;	
	std::wstring wsTmp = std::wstring(strTmp.begin(), strTmp.end());
	LPCWSTR swResult = wsTmp.c_str();
#endif

#if 0 //FIXME: WTF :/
	LPCWSTR swResult;
	CStringUtils::StringtoWString(strText, swResult);
#endif

	// Initialise Fonts
    m_pd3dDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
	DWORD dwFontCacheSize = 16 * 1024;
	XFONT_OpenTrueTypeFont(swResult, dwFontCacheSize, &m_pFont );

	m_bResoucesAlocated = true;
}

void CGUIFont::Render(int iPosX, int iPosY, unsigned int iSize, D3DCOLOR Color, string strText)
{
	if(!m_bResoucesAlocated)
		return;
#if 1
	// Convert to wide string
	std::string strTmp = strText;	
	std::wstring wsTmp = std::wstring(strTmp.begin(), strTmp.end());
	LPCWSTR swResult = wsTmp.c_str();
#endif

#if 0 //FIXME: WTF :/
	LPCWSTR swResult;
	CStringUtils::StringtoWString(strText, swResult);
#endif

    // Display our text
    m_pFont->SetTextColor(Color);
	m_pFont->SetTextHeight(iSize);
	m_pFont->TextOut(m_pBackBuffer, swResult, -1, iPosX, iPosY);
}

void CGUIFont::FreeResources()
{
	m_pFont->Release();
    m_pBackBuffer->Release();

	m_bResoucesAlocated = false;
}