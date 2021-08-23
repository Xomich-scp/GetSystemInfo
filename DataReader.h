#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <tchar.h>
#include <vector>

#pragma once
class DataReader
{
public:
    std::string DesktopFileName = "DesktopNames.csv";
    std::string ServerFileName = "ServerNames.csv";
    std::string OldProductName = "OldProduct.csv";
    std::string NewProductName = "NewProduct.csv";
    std::string CPUDataFilename = "CPUData.csv";
    std::string Delimeter = ";";

    DataReader()
    {

    }
    DataReader(std::string desktop, std::string server, 
                std::string oldname, std::string newname, 
                std::string cpuname, std::string delim):
                DesktopFileName(desktop), ServerFileName(server),
                OldProductName(oldname), NewProductName(newname),
                CPUDataFilename(cpuname), Delimeter(delim)
    {

    }
    void ReadData(std::string& filename, std::vector<DWORD>& tokens, std::string& OSparam);
    bool ParseValue(std::string* line, DWORD& value);

    
};