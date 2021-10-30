#include "headers el pepe/allincludes.h"
#include "imguiconfig.h"

DWORD WINAPI MainActivity(HMODULE hModule) {
    

    //AllocConsole();
    //FILE* f;
    //freopen_s(&f, "CONOUT$", "w", stdout);
    
    DWORD procID = getPID2(L"ac_client.exe");
    createwindowandconfigimgui();
    
    //FreeConsole();
    //fclose(f);
    FreeLibraryAndExitThread(hModule, 0);
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainActivity, hModule, 0, nullptr);
        
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

