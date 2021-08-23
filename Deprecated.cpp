#include "GetSystemInfo.h" 
#pragma warning(disable : 4996)
#pragma comment(lib, "User32.lib")


void DeprecatedWay::GetMaj_Min()
{
    GetVersionEx((OSVERSIONINFO*)&osvi);
}
void DeprecatedWay::GetOS()
{

    
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetMaj_Min();
    
    if (osvi.dwMajorVersion < 5)
    {
        std::cout << "Not designed for Windows older than Win 2000\n";
        return;
    }

    this->OSBuild = "build("+std::to_string(osvi.dwBuildNumber)+")";

    SYSTEM_INFO si;
    GetNativeSystemInfo(&si);

    std::vector<DWORD> tokensOS = { osvi.dwMajorVersion , osvi.dwMinorVersion };

    //Get OS Name
    switch (osvi.wProductType)
    {
    case VER_NT_WORKSTATION:
    {
        //OS is desktop
        MyDataReader->ReadData(MyDataReader->DesktopFileName, tokensOS, this->OSName);
        break;
    }
        
    default:
    {
        //OS is server
        if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
        {
            if (GetSystemMetrics(SM_SERVERR2))
            {
                tokensOS.push_back(1);
            }
            else
            {
                tokensOS.push_back(osvi.wSuiteMask);
            }
        }

        MyDataReader->ReadData(MyDataReader->ServerFileName, tokensOS, this->OSName);
        break;
    }
        break;
    }

    //Get Product Name
    switch (osvi.dwMajorVersion)
    {
    case 5:
    {
        switch (osvi.dwMinorVersion)
        {
        case 0:
        {
            if ((osvi.wSuiteMask & VER_SUITE_DATACENTER) || (osvi.wSuiteMask & VER_SUITE_ENTERPRISE))
                tokensOS.push_back(osvi.wSuiteMask);
            break;
        }
        case 1:
        {
            if (osvi.wSuiteMask & VER_SUITE_PERSONAL) tokensOS.push_back(osvi.wSuiteMask);
            break;
        }
        case 2:
        {
            if (osvi.wProductType == VER_NT_WORKSTATION) break;
            switch (si.wProcessorArchitecture)
            {
            case PROCESSOR_ARCHITECTURE_IA64:
            {
                if ((osvi.wSuiteMask & VER_SUITE_DATACENTER) || (osvi.wSuiteMask & VER_SUITE_ENTERPRISE))
                    tokensOS.push_back(osvi.wSuiteMask);
                break;
            }
            case PROCESSOR_ARCHITECTURE_AMD64:
            {
                if ((osvi.wSuiteMask & VER_SUITE_DATACENTER) || (osvi.wSuiteMask & VER_SUITE_ENTERPRISE))
                    tokensOS.push_back(osvi.wSuiteMask);
                break;
            }
            default:
            {
                if( (osvi.wSuiteMask & VER_SUITE_BLADE) || 
                    (osvi.wSuiteMask & VER_SUITE_DATACENTER) || 
                    (osvi.wSuiteMask & VER_SUITE_ENTERPRISE) )
                    tokensOS.push_back(osvi.wSuiteMask);
            }
                break;
            }
        }
        default:
            break;
        }
        MyDataReader->ReadData(MyDataReader->OldProductName, tokensOS, OSProduct);

    }
    default:
    {
        tokensOS.clear();
        PDWORD pdwReturnedProductType = new (DWORD);
        GetProductInfo(osvi.dwMajorVersion, osvi.dwMinorVersion, NULL, NULL, pdwReturnedProductType);
        tokensOS.push_back(*pdwReturnedProductType);
        MyDataReader->ReadData(MyDataReader->NewProductName, tokensOS, OSProduct);
    }
        break;
    }
    
    
    
    tokensOS.clear();
    tokensOS.push_back(si.wProcessorArchitecture);

    MyDataReader->ReadData(MyDataReader->CPUDataFilename, tokensOS, OSArch);

    std::wstring temp_wstr = osvi.szCSDVersion;
    if (!temp_wstr.empty())
    ExtraInfo = std::string(temp_wstr.begin(), temp_wstr.end());
    return;
}
