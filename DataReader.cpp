

#include "DataReader.h"

/*
*   Вспомогательный класс для чтения данных из внешних файлов.
*   Содержит два метода - парсер строки и считыватель данных.
*   Структура внешних файлов: [набор токенов через разделитель];[искомая строка]
*   Пример строки:  5;2;0x02000;Windows Storage Server 2003
*   Нужная строка найдена, если совпали все токены, поданные на вход.
*/
bool  DataReader::ParseValue(std::string* line, DWORD& value)
{
    try
    {
        value = std::stoi(line->substr(0, line->find(Delimeter)), nullptr, 0);
    }
    catch (const std::invalid_argument& ia)
    {
        return FALSE;
    }
    line->erase(0, line->find(Delimeter) + 1);
    return TRUE;

}
void  DataReader::ReadData(std::string& filename, std::vector<DWORD>& tokens, std::string& OSparam)
{
    if (tokens.empty())
    {
        std::cout<<"Error, no tokens\n";
        return;
    }
    std::ifstream file(filename);

    if (!file)
    {
        std::cout << "Programm datafile corrupted." << filename << std::endl;
        exit(-1);
    }

    std::string line = "";

    DWORD get_token;
    while (getline(file, line))
    {

        for (auto it = tokens.begin(); ; ++it)
        {
            if (!ParseValue(&line, get_token))
            {
                OSparam = line;
                return;
            }
            if (get_token == *it) continue;
            else break;

        }

    }

}