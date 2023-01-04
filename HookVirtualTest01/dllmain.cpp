#include "pch.h"
#include <iostream>
#include <psapi.h>
#include <Windows.h>

// ms detours
#include "detours.h"

// for signature scanning
#include "sigscan.h"

// the reversed classes so we can manipulate the hooked data class members
#include "reversed_classes.h"

/* hook tick function to find instance addresses */
typedef void(*tTickFunc)(Actor* pInstance);
tTickFunc oTickFunc;
void hTickFunc(Actor* pInstance)
{
    // print Instance Address

    std::cout << "" << std::endl;
    std::cout << "----- Detour TICK START -----" << std::endl;
    std::cout << "Detour: Instance Address: " << std::hex << pInstance << std::dec << std::endl;

    // because we reversed the actor class we can access the members now!
    std::cout << "Instance Health: " << pInstance->Health << std::endl;
    std::cout << "Instance SpecialID: " << pInstance->SpecialID << std::endl;

    //
    // cast to player and enemy to print the extra data of child classes!
    //
    Player* pMyPlayer = dynamic_cast<Player*>(pInstance);

    if(pMyPlayer != nullptr)
        std::cout << "Instance PlayerID: " << (int)pMyPlayer->PlayerID << std::endl;

    Enemy* pMyEnemy = dynamic_cast<Enemy*>(pInstance);
    if (pMyEnemy != nullptr)
        std::cout << "Instance EnemyID: " << (int)pMyEnemy->EnemyID << std::endl;

    std::cout << "----- Detour TICK END -----" << std::endl;
    std::cout << "" << std::endl;

    // call original
    oTickFunc(pInstance);
}


bool perform_hook = false;

void CreateHook()
{
    /* find the class tick function to hook */
    DWORD_PTR TickFuncAddress = FindPattern("TestAppVirtualToHook.exe", "\x48\x89\x4C\x24\x00\x55\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8D\x6C\x24\x00\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\x85\x00\x00\x00\x00\x48\x83\xC0\x10\x48\x8B\xD0", "xxxx?xxxxx????xxxx?xxx????x????xxx????xxxxxxx");

    // set address to our function
    oTickFunc = (tTickFunc)TickFuncAddress;

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    // assign original function and detour it then!
    DetourAttach(&(PVOID&)oTickFunc, hTickFunc);
    DetourTransactionCommit();
}

void DetachHooks()
{
    /* in case of detaching remove hooks */
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            if (!perform_hook)
            {
                std::cout << "DLL_PROCESS_ATTACH" << std::endl;
                CreateHook();
                perform_hook = true;
            }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            DetachHooks();
            break;
    }

    return TRUE;
}

