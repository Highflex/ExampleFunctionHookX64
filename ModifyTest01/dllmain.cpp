// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <TlHelp32.h>
#include <tchar.h> // _tcscmp

#include "sigscan.h"

bool perform_hook = false;
HANDLE RemoteProcess;

// find process ID by process name
int GetProcessIDByName(const wchar_t* procname) 
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe;
    int pid = 0;
    BOOL hResult;

    // snapshot of all processes in the system
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) return 0;

    // initializing size: needed for using Process32First
    pe.dwSize = sizeof(PROCESSENTRY32);

    // info about first process encountered in a system snapshot
    hResult = Process32First(hSnapshot, &pe);

    // retrieve information about the processes
    // and exit if unsuccessful
    while (hResult) 
    {
        // if we find the process: return process ID
        if (wcscmp(procname, pe.szExeFile) == 0)
        {
            pid = pe.th32ProcessID;
            break;
        }
        hResult = Process32Next(hSnapshot, &pe);
    }

    // closes an open handle (CreateToolhelp32Snapshot)
    CloseHandle(hSnapshot);
    return pid;
}

/* attempt finding the location to patch and apply changes to target */
void ApplyPatches()
{
    RemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcessIDByName(L"TestAppToModify.exe"));
    std::cout << "Cur Process Handle : " << RemoteProcess << std::endl;

    DWORD_PTR ScannedModAddress = 0;
    unsigned char patch_byte = 0x74; 
    unsigned char cur_byte = 0x00;

    // find address to modify using signature scanning!
    ScannedModAddress = FindPattern("TestAppToModify.exe", "\x40\x55\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8D\x6C\x24\x00\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xB9\x00\x00\x00\x00", "xxxxxx????xxxx?xxx????x????x????") + 0x2D;
    std::cout << "Mod Address Sig Scan: " << std::hex << ScannedModAddress << std::endl;

    if (ReadProcessMemory(RemoteProcess, (LPVOID)(ScannedModAddress), &cur_byte, sizeof(cur_byte), 0))
        std::cout << "Instruction before Patch: " << (int)cur_byte << std::endl;
    else 
        std::cout << "ReadProcessMemory failed with Error Code : " << GetLastError() << std::endl;

    // change the instruction from jne to je ( 75 -> 74 )
    if (WriteProcessMemory(RemoteProcess, (LPVOID)(ScannedModAddress), &patch_byte, sizeof(cur_byte), 0))
        std::cout << "Application Patched\n" << std::endl;
    else
        std::cout << "WriteProcessMemory failed with Error Code : " << GetLastError() << std::endl;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    int Status = 0;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!perform_hook)
        {
            ApplyPatches();
            perform_hook = true;
        }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

