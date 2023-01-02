#include "pch.h"
#include <iostream>
#include <psapi.h>
#include <Windows.h>

/* use official microsoft detours, do not forget to include in project!*/
#include <detours.h>

// simple sig scan utils
#include "sigscan.h"

//Globals
HINSTANCE DllHandle;

// the function address holders
DWORD64 FunctionAddress = 0;
DWORD64 Function2Address = 0;

// Hooks
typedef float(WINAPI* tFunction)(float a);
tFunction oFunction;
float WINAPI hFunction(float a)
{
    std::cout << "calling DETOURED before function, argument is: " << a << std::endl;		// we can access arguments passed to original function

    // call original
    oFunction = (tFunction)FunctionAddress;
    return oFunction(7.66f); // modify input
}

typedef DWORD64(WINAPI* tFunction2)();
tFunction2 oFunction2; //Set it at address to detour in
DWORD64 WINAPI hFunction2()
{
    std::cout << "calling DETOURED before function2" << std::endl;		//we can access arguments passed to original function

    // call original
    oFunction2 = (tFunction2)Function2Address;
    return oFunction2();
}

DWORD WINAPI ApplicationCore(HINSTANCE hModule)
{
    if (!AllocConsole())
        MessageBox(NULL, L"The console window was not created", NULL, MB_ICONEXCLAMATION);
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    std::cout << "------------------------" << std::endl;
    std::cout << "Preparing Hook Injection!" << std::endl;
    std::cout << "------------------------" << std::endl;

    /* keep dll running */
    while (true) {
        Sleep(50);
    }

	return 0;
}

//
bool perform_hook = false;

// DLL
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!perform_hook)
        {
            std::cout << "DLL_PROCESS_ATTACH" << std::endl;

            // address of function
            //FunctionAddress = (DWORD64)GetModuleHandle(L"TestAppToHook.exe") + 0x123A0;
            //Function2Address = (DWORD64)GetModuleHandle(L"TestAppToHook.exe") + 0x12340;

            // signatures generated using SigMaker for IDA 7 and hovering over function.
            FunctionAddress = FindPattern("TestAppToHook.exe", "\xF3\x0F\x11\x44\x24\x00", "xxxxx?");
            Function2Address = FindPattern("TestAppToHook.exe", "\x40\x55\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8D\x6C\x24\x00\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00", "xxxxxx????xxxx?xxx????x????xxx????");

            /*
            std::cout << "Function Address Org: " << std::hex << FunctionAddress << std::endl;
            std::cout << "Function Address Sig Scan: " << std::hex << ScannedFunctionAddress << std::endl;
            std::cout << "Function Address 2 Org: " << std::hex << Function2Address << std::endl;
            std::cout << "Function Address 2 Sig Scan: " << std::hex << ScannedFunction2Address << std::endl;
            */
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());

            // assign original function and detour it then!
            DetourAttach(&(PVOID&)FunctionAddress, hFunction);
            DetourAttach(&(PVOID&)Function2Address, hFunction2);
            DetourTransactionCommit();

            DllHandle = hModule;
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ApplicationCore, NULL, 0, NULL);

            perform_hook = true;
        }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        /* in case of detaching remove hooks */
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)FunctionAddress, hFunction);
        DetourDetach(&(PVOID&)Function2Address, hFunction2);
        fflush(stdout);
        break;
    }
    return TRUE;
}