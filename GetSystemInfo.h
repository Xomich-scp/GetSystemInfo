#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <vector>
#include "DataReader.h"


/*
*   Базовый интерфейс 
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
*   Определение информации с помощью устаревшей GetVersionEx().
*   Для корректной работы данной функции отредактирован файл манифеста. Пример манифеста взят с MSDN.
*/
class DeprecatedWay : public MyGetOSVer
{
protected:
    //Вспомогательный класс для считывания данных из внешних файлов.
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
*   Запуск командной строки. Используется встроенная функция systeminfo.
*   
*/
class CMD_Way : public MyGetOSVer
{
public:
    virtual void GetOS();
    virtual void PrintData();
};

/*
*   Просмотр нужных данных в реестре.
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
*   Определение информации с помощью устаревшей GetVersionEx(). 
*   В данном варианте  GetVersionEx используется для получения дополнительной информации о системе (Серверная/десктопная, номер билда).
*   Для определния версии системы системы смотрятся данные системной библиотеки kernel32. Она всегда в системе и содержит актуальный номер версии ОС
*/
class GFV_Info : public DeprecatedWay
{
private:
    void GetMaj_Min();
    
};




