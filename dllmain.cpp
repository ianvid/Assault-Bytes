#include "headers el pepe/allincludes.h"
#include "imguiconfig.h"

void sayhi() {
    typedef void(*consoleoutput)(char* input);
    consoleoutput consoleoutput1 = (consoleoutput)(modulebase + 0X6B060);
    char a[300] = "Welcome to Assault Bytes you motherf***";
    consoleoutput1(a);
}


DWORD WINAPI MainActivity(HMODULE hModule) {
    
    DWORD modulebase2 = (DWORD)GetModuleHandle(L"ac_client.exe");
    bool console = false;

    if (console) {
        AllocConsole();
        FILE* f;
        freopen_s(&f, "CONOUT$", "w", stdout);
    }


    sayhi();
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

