#include "GetSystemInfo.h"

#pragma comment(lib, "Advapi32.lib")


void Registry_Way::GetOS()
{
    HKEY hKey;
    LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey);
    if (lRes != ERROR_SUCCESS)
    {
        std::cout << "Error while opening registry.\t" << lRes << std::endl;
        return;
    }
    
    std::wstring getVal;
    GetStringRegKey(hKey, L"CurrentBuild", getVal, L"N/A");
    OSBuild = std::string(getVal.begin(),getVal.end());
    GetStringRegKey(hKey, L"ProductName", getVal, L"N/A");
    OSProduct = std::string(getVal.begin(), getVal.end());
    GetStringRegKey(hKey, L"CSDVersion", getVal, L"N/A");
    ExtraInfo = std::string(getVal.begin(), getVal.end());



    DWORD getVer;
    std::vector<DWORD> tokensOS;

    if (GetDWORDRegKey(hKey, L"CurrentMajorVersionNumber", getVer, -1) == ERROR_SUCCESS)
    {
        tokensOS.push_back(getVer);
    }

    if (GetDWORDRegKey(hKey, L"CurrentMinorVersionNumber", getVer, -1) == ERROR_SUCCESS)
    {
        tokensOS.push_back(getVer);
    }


    
    if ((!tokensOS.empty()) &&(GetStringRegKey(hKey, L"InstallationType", getVal, L"Error") == ERROR_SUCCESS))
    {
        if (getVal == L"Client")
        {
            MyDataReader->ReadData(MyDataReader->DesktopFileName, tokensOS, OSName);
        }
        else
        {

            if (*tokensOS.begin() == 5 && *(tokensOS.begin() + 1) == 2)
            {
                if (GetSystemMetrics(SM_SERVERR2))
                {
                    tokensOS.push_back(1);
                }
                else
                {
                    /*
                        Here we need OSVERSIONINFOEX.wSuiteMask to determine version of Win Server 2003.
                        The only way is call deprecated GetVersion(). So, I just left it blank.
                    */
                }
            }

            MyDataReader->ReadData(MyDataReader->ServerFileName, tokensOS, this->OSName);
        }
    }
    SYSTEM_INFO si;
    GetNativeSystemInfo(&si);
    tokensOS.clear();
    tokensOS.push_back(si.wProcessorArchitecture);

    MyDataReader->ReadData(MyDataReader->CPUDataFilename, tokensOS, OSArch);


}



LONG Registry_Way::GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue)
{
    strValue = strDefaultValue;
    WCHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;
    nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
    
    if (ERROR_SUCCESS == nError)
    {
        strValue = szBuffer;
    }
    return nError;
}

LONG Registry_Way::GetDWORDRegKey(HKEY hKey, const std::wstring& strValueName, DWORD& nValue, DWORD nDefaultValue)
{
    nValue = nDefaultValue;
    DWORD dwBufferSize(sizeof(DWORD));
    DWORD nResult(0);
    LONG nError = ::RegQueryValueExW(hKey,
        strValueName.c_str(),
        0,
        NULL,
        reinterpret_cast<LPBYTE>(&nResult),
        &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        nValue = nResult;
    }
    return nError;
}
