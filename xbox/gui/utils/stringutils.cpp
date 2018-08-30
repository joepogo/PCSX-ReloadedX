#include "stringutils.h"

void CStringUtils::AddSlashAtEnd(std::string& strFolder)
{
  if (!HasSlashAtEnd(strFolder))
  {
      strFolder += '\\';
  }
}

bool CStringUtils::HasSlashAtEnd(const std::string& strFile)
{
  if (strFile.size() == 0) return false;
  char kar = strFile.c_str()[strFile.size() - 1];

  if (kar == '/' || kar == '\\')
    return true;

  return false;
}

// Converts string to wide
void CStringUtils::StringtoWString(std::string strText, LPCWSTR &strResult)
{
	wchar_t* wtext = new wchar_t[strText.size()+1];
	mbstowcs(wtext, strText.c_str(), strlen(strText.c_str())+1);
	strResult = wtext;

	delete wtext;
}