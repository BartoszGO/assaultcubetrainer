
#include <iostream>
#include "memproc.h"
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <WinUser.h>
#include "vecutils.h"
#include "Process.h"




int main()
{
    const wchar_t* procName = L"ac_client.exe";
    Process process(procName, procName);
    std::cout << "Hello World!\n";
}

