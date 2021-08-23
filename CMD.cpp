#include "GetSystemInfo.h"

void CMD_Way::GetOS()
{
	system("chcp > 0.tmp");
	system("chcp 65001");
	system("systeminfo | findstr /B /C:\"OS Name\" /C:\"OS Version\" /C:\"System Type\"");
	
	std::ifstream file("0.tmp");

	if (!file)
	{
		std::cout << "Programm datafile corrupted. Missing old code page number" << std::endl;
		exit(-1);
	}

	std::string line = "";
	getline(file, line);
	line = "chcp " + line.substr(line.rfind(" "),std::string::npos);
	system(line.c_str());
	file.close();
	remove("0.tmp");
	return;
}

void CMD_Way::PrintData()
{
	return;
}