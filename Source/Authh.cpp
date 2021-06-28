#include "stdafx.h"
using std::string;

#define URL L"https://evilcum.com/OpenAuth/Authenticator/Key"
int menuauthlevel;
wstring s2ws(const std::string& str) {
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;
	return converterX.from_bytes(str);
}

void get_auth_status(std::string license) {

	char hwid[4096];
	// total physical memory
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	sprintf_s(hwid, "%I64i", statex.ullTotalPhys / 1024);

	// volume information
	TCHAR volumename[MAX_PATH + 1] = { 0 };
	TCHAR filesystemname[MAX_PATH + 1] = { 0 };
	DWORD serialnumber = 0, maxcomponentlen = 0, filesystemflags = 0;
	GetVolumeInformation(_T("C:\\"), volumename, ARRAYSIZE(volumename), &serialnumber, &maxcomponentlen, &filesystemflags, filesystemname, ARRAYSIZE(filesystemname));
	sprintf_s(hwid, "%s%li%ws%li", hwid, serialnumber, filesystemname, maxcomponentlen);

	// computer name
	TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	GetComputerName(computerName, &size);
	sprintf_s(hwid, "%s%ws", hwid, computerName);

	net::requests m_request(L"galaxy-five", false);
	::std::wstring answer = m_request.Post(false, URL, "key=%s&hwid=%s", license.c_str(), hwid);
	
	if (answer == L"premium") {
		return true;
		menuauthlevel = 2;
	}
	else if (answer == L"free") {
		return true;
		menuauthlevel = 1;
	}
	else {
		return false;
	}
}
