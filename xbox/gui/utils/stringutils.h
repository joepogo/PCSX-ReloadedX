#ifndef H_CSTRINGUTILS
#define H_CSTRINGUTILS

#include <string>
#include <xtl.h>

class CStringUtils
{
public:
	static void AddSlashAtEnd(std::string& strFolder);
	static bool HasSlashAtEnd(const std::string& strFile);
	static void CStringUtils::StringtoWString(std::string strText, LPCWSTR &strResult);
};

#endif //H_CSTRINGUTILS