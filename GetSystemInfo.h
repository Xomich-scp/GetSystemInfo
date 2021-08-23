#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <vector>
#include "DataReader.h"


/*
*   ������� ��������� 
*/
class MyGetOSVer
{
protected:
    std::string OSName = "N/A";
    std::string OSBuild = "N/A";
    std::string OSArch = "N/A";
    std::string OSProduct = "N/A";
    std::string ExtraInfo = "N/A";
public:

    virtual void GetOS() = 0;
    virtual void PrintData() {
        std::cout << "OS Name    : " << OSName << std::endl;
        std::cout << "OS Build   : " << OSBuild << std::endl;
        std::cout << "OS Edition : " << OSProduct << std::endl;
        std::cout << "OS Arch    : " << OSArch << std::endl;
        std::cout << "OS ExtraInf: " << ExtraInfo << std::endl;
    };
};





/*
*   ����������� ���������� � ������� ���������� GetVersionEx().
*   ��� ���������� ������ ������ ������� �������������� ���� ���������. ������ ��������� ���� � MSDN.
*/
class DeprecatedWay : public MyGetOSVer
{
protected:
    //��������������� ����� ��� ���������� ������ �� ������� ������.
    DataReader* MyDataReader;
    OSVERSIONINFOEX osvi;
    virtual void GetMaj_Min();
public:
    virtual void GetOS();
    DeprecatedWay()
    {
        MyDataReader = new DataReader();
    }
    ;
    DeprecatedWay(DataReader* reader) :MyDataReader(reader)
    {

    };
    ~DeprecatedWay()
    {

    };
};

/*
*   ������ ��������� ������. ������������ ���������� ������� systeminfo.
*   
*/
class CMD_Way : public MyGetOSVer
{
public:
    virtual void GetOS();
    virtual void PrintData();
};

/*
*   �������� ������ ������ � �������.
*   
*/
class Registry_Way : public MyGetOSVer
{
private:
    DataReader* MyDataReader;
    LONG GetDWORDRegKey(HKEY hKey, const std::wstring& strValueName, DWORD& nValue, DWORD nDefaultValue);
    LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue);


public:
    Registry_Way()
    {
        MyDataReader = new DataReader();
    }
    ;
    Registry_Way(DataReader* reader) :MyDataReader(reader)
    {

    };
    virtual void GetOS();
};


/*
*   ����������� ���������� � ������� ���������� GetVersionEx(). 
*   � ������ ��������  GetVersionEx ������������ ��� ��������� �������������� ���������� � ������� (���������/����������, ����� �����).
*   ��� ���������� ������ ������� ������� ��������� ������ ��������� ���������� kernel32. ��� ������ � ������� � �������� ���������� ����� ������ ��
*/
class GFV_Info : public DeprecatedWay
{
private:
    void GetMaj_Min();
    
};




