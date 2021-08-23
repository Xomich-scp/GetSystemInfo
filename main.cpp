
#include "main.h"

/*
*   Для использоавния другого метода достаточно сменить тип создаваемого дочернего класса.
*   Доступные типы:
*   DeprecatedWay
*   CMD_Way
*   Registry_Way
*   GFV_Info
*/

int main()
{
    
    


    MyGetOSVer* INTOs = new GFV_Info();

    INTOs->GetOS();
    INTOs->PrintData();

}


/*
* наиболее полное название ОС (версия windows, битность, номер билда. Например: "Operating System: Windows 7 x64 (Build 7601), Service Pack 1" )
*
OS Name:                   Майкрософт Windows 10 Корпоративная LTSC
OS Version:                10.0.17763 N/A Build 17763
*/
