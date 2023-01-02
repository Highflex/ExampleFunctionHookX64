#pragma once
#include <iostream>
#include <psapi.h>
#include <Windows.h>

/* works for 64 bit */
DWORD64 FindPattern(const char* szModule, const char* pattern, const char* mask)
{
    MODULEINFO mInfo = { 0 };
    HMODULE hModule = GetModuleHandleA(szModule);

    if (!hModule)
        return 0;

    GetModuleInformation(GetCurrentProcess(), hModule, &mInfo, sizeof(MODULEINFO));

    uintptr_t begin = (uintptr_t)mInfo.lpBaseOfDll;
    DWORD64 size = mInfo.SizeOfImage;
    size_t patternLen = strlen(mask);

    for (DWORD64 i = 0; i < size; i++)
    {
        bool found = true;
        for (size_t j = 0; j < patternLen; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)(begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (DWORD64)(begin + i);
        }
    }
    return 0;
}