#include "GetSystemInfo.h"

#include <cassert>
#pragma comment(lib, "Version.lib")
#pragma warning(disable : 4996)
#pragma comment(lib, "User32.lib")
void GFV_Info::GetMaj_Min()
{
	
	DWORD dummy;
	const auto cbInfo =
		::GetFileVersionInfoSizeW( L"kernel32.dll", &dummy);
	std::vector<char> buffer(cbInfo);

	::GetFileVersionInfoA("kernel32.dll", dummy,
		buffer.size(), &buffer[0]);
	void* p = nullptr;
	UINT size = 0;
	::VerQueryValueW(buffer.data(), L"\\", &p, &size);
	assert(size >= sizeof(VS_FIXEDFILEINFO));
	assert(p != nullptr);
	auto pFixed = static_cast<const VS_FIXEDFILEINFO*>(p);

	GetVersionEx((OSVERSIONINFO*)&osvi);
	osvi.dwMajorVersion = HIWORD(pFixed->dwFileVersionMS);
	osvi.dwMinorVersion = LOWORD(pFixed->dwFileVersionMS);
	osvi.dwBuildNumber = HIWORD(pFixed->dwFileVersionLS);

return;
}

