#include <windows.h>
#include <psapi.h>
#include <iostream>

#include "util/scan.h"
#include "sdk/SDK.h"

MODULEINFO g_base = { 0 };

DWORD WINAPI start_routine(HINSTANCE hinstDLL);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)start_routine, hinstDLL, 0, nullptr));
    }
    return TRUE;
}

void set_values()
{
    scan::set_data((unsigned long long)g_base.lpBaseOfDll, (unsigned long long)g_base.SizeOfImage);

    unsigned long long temp_address = 0;
    {
        char signature[] = "\x48\x8D\x05\x00\x00\x00\x00\xEB\x13";
        char mask[] = "xxx????xx";
        temp_address = scan::search(signature, mask);
        auto offset = *reinterpret_cast<uint32_t*>(temp_address + 3);
        temp_address = temp_address + 7 + offset;
        SDK::UnrealEngine::NamePoolData = (SDK::UnrealEngine::FNamePool*)temp_address;
    }
    {
        char signature[] = "\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x0C\xC8\x48\x8D\x04\xD1\xEB";
        char mask[] = "xxx????xxxxxxxxx";
        temp_address = scan::search(signature, mask);
        auto offset = *reinterpret_cast<uint32_t*>(temp_address + 3);
        temp_address = temp_address - 9 + offset;
        SDK::UnrealEngine::GUObjectArray = (SDK::UnrealEngine::FUObjectArray*)temp_address;
    }
}

DWORD WINAPI start_routine(HINSTANCE hinstDLL)
{
    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);

    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &g_base, sizeof(MODULEINFO));

    SDK::Initialize(((uintptr_t)g_base.lpBaseOfDll) + 0x96EB690, ((uintptr_t)g_base.lpBaseOfDll) + 0x99BC540, ((uintptr_t)g_base.lpBaseOfDll) + 0x99BA1C8);

    while (!GetAsyncKeyState(VK_DELETE));

    fclose(stream);
    FreeConsole();

    FreeLibraryAndExitThread(hinstDLL, 0);

    return 0;
}
