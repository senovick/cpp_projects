#include <windows.h>
#include <iostream>


int main()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    std::cout << "Number of processors: " << sysInfo.dwNumberOfProcessors << std::endl;

    return 0;
}