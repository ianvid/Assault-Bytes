#include "headers el pepe/allincludes.h"
#include "imguiconfig.h"

void sayhi() {
    typedef void(*consoleoutput)(char* input);
    consoleoutput consoleoutput1 = (consoleoutput)(modulebase + 0X6B060);
    char a[300] = "Welcome to Assault Bytes you motherf***";
    consoleoutput1(a);
}

/*class Entity //this class was made for test purposes. credits to ReClass
{
public:
    char pad_0000[248]; //0x0000
    int32_t Health; //0x00F8
    char pad_00FC[72]; //0x00FC
}; //Size: 0x0144

class Base
{
public:
    char pad_0000[4]; //0x0000
    class Entity* EntityArray[32]; //0x0004
    char pad_0084[320]; //0x0084
}; //Size: 0x01C4

Base* base = *(Base**)(modulebase2 + 0x10f4f8);

for (int i = 0; i < *players - 1; i++) {
    printf("bot - %d -  health is %d\n", i, base->EntityArray[i]->Health);
    Sleep(50);
}*/
DWORD WINAPI MainActivity(HMODULE hModule) {
    
    DWORD modulebase2 = (DWORD)GetModuleHandle(L"ac_client.exe");
    AllocConsole(); FILE* f; freopen_s(&f, "CONOUT$", "w", stdout);

    
    sayhi();
    createwindowandconfigimgui();

    system("pause");
    
    FreeConsole(); fclose(f);
 

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

